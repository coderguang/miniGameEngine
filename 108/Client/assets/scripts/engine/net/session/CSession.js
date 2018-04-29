
import {CSerializeStream} from '../../serializeStream/CSerializeStream'
import {CsgProtocol} from '../protocol/CsgProtocol'
import {CException} from '../../exception/CException'

if(typeof ESessionStatus == "undefined"){
	var ESessionStatus={};
	ESessionStatus.ESessionStatusWaitConnecting=1;
	ESessionStatus.ESessionStatusConnected=2;
	ESessionStatus.ESessionStatusDisConnected=3;
}


if(typeof ESessionDisconnectReason=="undefined"){
	var ESessionDisconnectReason={};
	ESessionDisconnectReason.ESessionDisconnectByClient=1; //客户端主动断开
	ESessionDisconnectReason.ESessionDisconnectOutOfRecvBuff=2;//数据超出缓冲区大小
	ESessionDisconnectReason.ESessionDisconnectReadErrorSync=3; //socket 错误
	ESessionDisconnectReason.ESessionDisconnectReadErrorAsync=4;
	ESessionDisconnectReason.ESessionDisconnectShutDownServer=5;
	ESessionDisconnectReason.ESessionDisconnectConnectError=6;
}


class CSession{
	//props
	_url;
	_port;
	_status;
	_ws;
	_buffer;
	_protocol;
	_callBackId;
	_callBackMap;
	static _instance;
	constructor(){
		this._buffer=new CSerializeStream();
		this._protocol=new CsgProtocol();
		this._callBackId=0;
		this._callBackMap=new Map();
	}
	static getInstance(){
		if(false === this._instance instanceof this){
			this._instance=new this;
		}
		return this._instance;
	}

	init(url,port){
		this._url=url;
		this._port=port;
		this._status=ESessionStatus.ESessionStatusWaitConnecting;
	}

	onOpen(){
		console.log("session connected,url="+this._url+",port="+this._port);

		this._status=ESessionStatus.ESessionStatusConnected;
	}


	onMessage(evt){
		console.log("session onmessage,evt="+evt.data+",length="+evt.data.byteLength);
		this._buffer.append(evt.data,evt.data.byteLength);
		this._protocol.handleRecvData(this,evt.data,evt.data.byteLength);
	}


	onClose(evt){
		console.log("session close,evt="+evt);
		
		this._status=ESessionStatus.ESessionStatusDisConnected;
	}

	onError(evt){
		console.log("session error,evt="+evt);
	}

	startConnect(){
		let remote_url="wss://"+this._url+":"+this._port;
		let session=this;
		this._ws=new WebSocket(remote_url);
		this._ws.binaryType='arraybuffer';
		this._ws.onopen=function(){
			session.onOpen();
		}
		this._ws.onmessage=function(evt){
			session.onMessage(evt);
		}
		this._ws.onclose=function(evt){
			session.onClose(evt);
		}
		this._ws.onerror=function(evt){
			session.onError(evt);
		}
	}



	sendData(buf){
		if(this._status!=ESessionStatus.ESessionStatusConnected){
			console.log("websocket not connected,can't send data,failed!");
			return ;
		}
		this._ws.send(buf);
	}


	//rpc function
	getCallBackId(){
		if(this._callBackId<100000){
			this._callBackId=this._callBackId+1;
		}else{
			this._callBackId=1;
		}
		return this._callBackId;
	}

	addCallBackObject(messageId,objcetBind){
		if(!this._callBackMap[messageId]==null){
			console.log("session.addCallBackObject,duplicate messageId="+messageId);
			throw new CException(ECSGEErrorCode.ExceptionCodeRMIBase,"duplicate messageId id");
			return ;
		}
		this._callBackMap[messageId]=objcetBind;
	}
	getCallBackObject(messageId){
		if(this._callBackMap[messageId]==null){
			console.log("session,getCallBackObject no this backObject,messageId="+messageI);
			return false;
		}
		let backObject=this._callBackMap[messageId];
		this._callBackMap.delete(messageId);
		return backObject;
	}

}

export {CSession}




