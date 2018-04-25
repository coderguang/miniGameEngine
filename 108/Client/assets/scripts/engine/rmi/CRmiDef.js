

const SIZE_OF_PROTOCOL_HEAD=4;

if(typeof ERMIMessageType== "undefined"){
	var ERMIMessageType={};
	ERMIMessageType.ERMIMessageTypeMQ=1;
	ERMIMessageType.ERMIMessageTypeCall=2;
	ERMIMessageType.ERMIMessageTypeCallRet=3;
}

function _csg_wirte_rmi_type(__os,type){
	__os.writeByte(type);	
}


class SRMICall{
	//props
	messageId=0;
	rpcId=0;

	constructor(){

	}

	_csg_write(__os){
		__os.writeInt(this.messageId);
		__os.writeInt(this.rpcId);
	}

	_csg_read(__is){
		this.messageId=__is.readInt();
		this.rpcId=__is.readInt();
	}

}

class SProtocolHead{
	msgSize=0;

	_csg_write(__os){
		__os.writeSizeIntWithoutBitMark(this.msgSize);
	}
	_csg_read(__is){
		this.msgSize=__is.readSizeIntWithoutBitMark();		
	}
}


export {SRMICall}
export {ERMIMessageType}

export {_csg_wirte_rmi_type}

export {SProtocolHead,SIZE_OF_PROTOCOL_HEAD}