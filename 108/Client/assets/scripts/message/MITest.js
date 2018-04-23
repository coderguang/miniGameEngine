
import {SRMICall} from '../engine/rmi/CRmiDef'
import {CSerializeStream} from '../engine/serializeStream/CSerializeStream'
import {CRpcHelper} from '../engine/rmi/CRpcHelper'


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



}

export {MITest}