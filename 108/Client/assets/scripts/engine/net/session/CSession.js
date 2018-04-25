
import {CSerializeStream} from '../../serializeStream/CSerializeStream'
import {CsgProtocol} from '../protocol/CsgProtocol'

if(typeof ESessionStatus == "undefined"){
	var ESessionStatus={};
	ESessionStatus.ESessionStatusWaitConnecting=1;
	ESessionStatus.ESessionStatusConnected=2;
	ESessionStatus.ESessionStatusDisConnected=3;
}



class CSession{
	//props
	_url;
	_port;
	_status;
	_ws;
	_buffer;
	_protocol;
	static _instance;
	constructor(){
		this._buffer=new CSerializeStream();
		this._protocol=new CsgProtocol();
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
		let remote_url="ws://"+this._url+":"+this._port;
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
}

export {CSession}




