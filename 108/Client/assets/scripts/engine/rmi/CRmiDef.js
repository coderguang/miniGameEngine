

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
		this.messageId=0;
		this.rpcId=0;
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

if(typeof ERMIDispatchResult=="undefined"){
	var ERMIDispatchResult={};
	ERMIDispatchResult.ERMIDispatchResultOk = 1 ;
	ERMIDispatchResult.ERMIDispatchResultTimeout = 2 ;
	ERMIDispatchResult.ERMIDispatchResultException = 3 ;
	ERMIDispatchResult.ERMIDispatchObjectNotExist = 4 ;
}

class SProtocolHead{
	msgSize=0;

	constructor(){
		this.msgSize=0;
	}

	_csg_write(__os){
		__os.writeSizeIntWithoutBitMark(this.msgSize);
	}
	_csg_read(__is){
		this.msgSize=__is.readSizeIntWithoutBitMark();		
	}
}

class SRMIReturn{
	messageId=0;
	dispathStatus=ERMIDispatchResult.ERMIDispatchResultOk;
	constructor(){

	}
	_csg_read(__is){
		this.messageId=__is.readInt();
		this.dispathStatus=__is.readByte();
	}
	_csg_write(__os){
		__os.writeInt(this.messageId);
		__os.writeByte(this.dispathStatus);
	}

}

export {SRMICall,SRMIReturn}
export {ERMIMessageType,ERMIDispatchResult}
export {_csg_wirte_rmi_type}
export {SProtocolHead,SIZE_OF_PROTOCOL_HEAD}