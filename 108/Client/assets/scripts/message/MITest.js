
import {SRMICall} from '../engine/rmi/CRmiDef'
import {CSerializeStream} from '../engine/serializeStream/CSerializeStream'
import {CRpcHelper} from '../engine/rmi/CRpcHelper'



class STestStruct{
	a;
	b;
	str;
	ib;
	constructor(){
		this._csg_init();
	}
	_csg_init(){
		this.a=0;
		this.b=false;
		this.str="";
		this.ib=new Array();
	}
	_csg_read(__is){
		this.a=__is.readInt();
		this.b=__is.readBoolean();
		this.str=__is.readString();
		this.ib=__is.readIntSeq();
	}
	_csg_write(__os){
		__os.writeInt(this.a);
		__os.writeBoolean(this.b);
		__os.writeString(this.str);
		__os.writeIntSeq(this.ib);
	}
	getType(){
		return 5;
	}
	clone(){
		return new STestStruct();
	}

}


class MITest{

	constructor(){
		
	}

	t1_async(session,cb){
		console.log("t1_async");
		let call=new SRMICall;
		call.rpcId=11;

		let __os=new CSerializeStream();
		let objectBind;
		CRpcHelper.prepareToCall(session,__os,call,cb,objectBind);
	
		__os.setUseBitMark(true);

		CRpcHelper.toCall(session,__os,	objectBind);		
	}

	t2_async(session,a,s,cb){
		console.log("t2_async");
		let call=new SRMICall;
		call.rpcId=12;

		let __os=new CSerializeStream();
		let objectBind;
		CRpcHelper.prepareToCall(session,__os,call,cb,objectBind);
	
		__os.setUseBitMark(true);
		__os.writeInt(a);
		__os.writeString(s);
		CRpcHelper.toCall(session,__os,	objectBind);		
	}

	t3_async(session,a,s,cb){
		console.log("t3_async");
		let call=new SRMICall;
		call.rpcId=13;

		let __os=new CSerializeStream();
		let objectBind;
		CRpcHelper.prepareToCall(session,__os,call,cb,objectBind);
	
		__os.setUseBitMark(true);
		__os.writeInt(a);
		__os.writeString(s);
		CRpcHelper.toCall(session,__os,	objectBind);		
	}

	t7_async(session,a,st,cb){		
		console.log("t7_async");
		let call=new SRMICall;
		call.rpcId=17;

		let __os=new CSerializeStream();
		let objectBind;
		CRpcHelper.prepareToCall(session,__os,call,cb,objectBind);
	
		__os.setUseBitMark(true);
		__os.writeInt(a);
		st._csg_write(__os);
		CRpcHelper.toCall(session,__os,	objectBind);		
	}



}

export {MITest,STestStruct}