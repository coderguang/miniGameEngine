
import {CSerializeStream} from '../../serializeStream/CSerializeStream'
import {SProtocolHead,SIZE_OF_PROTOCOL_HEAD,ERMIMessageType} from '../../rmi/CRmiDef'
import {CMsgManager} from '../../mq/CMsgManager'
import {CMsgBlock} from '../../mq/CMsgBlock'

class CsgProtocol{
	_recvBuffer;
	_sendBuffer;
	_receiveHead;
	_protocolHead;
	constructor(){
		this._receiveHead=false;
		this._sendBuffer=new CSerializeStream();
		this._recvBuffer=new CSerializeStream();
		this._protocolHead=new SProtocolHead();
	}

	handleRecvData(session,data,len){
		this._recvBuffer.append(data,len);
		this.handleReadData(session);
	}

	handleReadData(session){
		do{
			if(this._receiveHead){
				if(this._recvBuffer.getDataSize()<this._protocolHead.msgSize+SIZE_OF_PROTOCOL_HEAD){
					return 0;
				}
				if(-1===this.handlePacket(session)){

					return -1;
				}
				this._recvBuffer.popData(this._protocolHead.msgSize+SIZE_OF_PROTOCOL_HEAD);
				this._recvBuffer.reset();
				this._receiveHead=false;
			}else{
				if(this._recvBuffer.getDataSize()>=SIZE_OF_PROTOCOL_HEAD){
					this._recvBuffer.initReadView();
					this._protocolHead._csg_read(this._recvBuffer);
					this._receiveHead=true;
				}else{
					return 0;
				}
			}

		}while(true);
	}

	handlePacket(session){
		let is=new CSerializeStream();
		is.append(this._recvBuffer.getData(),this._protocolHead.msgSize+SIZE_OF_PROTOCOL_HEAD);
		//pop head data first
		is.popData(SIZE_OF_PROTOCOL_HEAD);
		is.initReadView();
		is.setUseBitMark(false);
		is.prepareToRead();

		let rmiType=is.readByte();
		console.log("rmi.type="+rmiType);
		switch(rmiType){
			case ERMIMessageType.ERMIMessageTypeMQ:
			{
				console.log("get mq from server");
				let msg=new CMsgBlock();
				msg._csg_read(is);

			}
			break;
			case ERMIMessageType.ERMIMessageTypeCall:
			{
				console.log("get call from server?");
			}
			break;
			case ERMIMessageType.ERMIMessageTypeCallRet:
			{
				console.log("call back from server")
			}
			break;
			default:
			{
				console.log("unknow rmiType,type="+rmiType);
			}

		}



	}

}

export {CsgProtocol}

