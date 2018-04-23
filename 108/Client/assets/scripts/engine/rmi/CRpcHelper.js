

import {_csg_wirte_rmi_type,ERMIMessageType,SRMICall,SProtocolHead} from 'CRmiDef'
import {CSerializeStream} from '../engine/serializeStream/CSerializeStream'

class CRpcHelper{
	
	static prepareToCall(session,__os,call,backObject,objectBind){
		_csg_wirte_rmi_type(__os,ERMIMessageType.ERMIMessageTypeCall);
		call.messageId=0;
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