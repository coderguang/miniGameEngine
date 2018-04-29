

import {_csg_wirte_rmi_type,ERMIMessageType,SRMICall,SProtocolHead} from 'CRmiDef'
import {CSerializeStream} from '../serializeStream/CSerializeStream'
import {CRMIObjectBind} from 'CRmiObject'

class CRpcHelper{
	
	static prepareToCall(session,__os,call,backObject,objectBind){
		_csg_wirte_rmi_type(__os,ERMIMessageType.ERMIMessageTypeCall);
		if(typeof backObject !== "undefined "){
			objectBind=new CRMIObjectBind();
			objectBind.bindProxyCallBackObject(backObject);
			call.messageId=session.getCallBackId();
			session.addCallBackObject(call.messageId,objectBind);
		}
		call._csg_write(__os);
	}


	static toCall(session,__os,objectBind){

		__os.prepareToAppend();

		let tmpOs=new CSerializeStream();
		let flagBytes=__os.getFlagData().slice(0,__os.getFlagDataSize());
		tmpOs.writeByteSeq(flagBytes);
		tmpOs.append(__os.getData(),__os.getDataSize());

		let head=new SProtocolHead();
		head.msgSize=tmpOs.getDataSize();

		let sendOs=new CSerializeStream();
		head._csg_write(sendOs);
		sendOs.append(tmpOs.getData(),tmpOs.getDataSize());
		session.sendData(sendOs.getData());
	}

}


export {CRpcHelper}