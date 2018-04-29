
import {CException,ECSGEErrorCode} from '../exception/CException'


class CRMIProxyCallBackObject{
	constructor(){

	}
}




class CRMIObjectBind{
	_callBack;

	constructor(){
		
	}

	bindProxyCallBackObject(callback_obj){
		if(typeof callback_obj == "undefined"){
			throw new CException(ECSGEErrorCode.ExceptionCodeRMIBase,"callback_obj is undefined");
			return false;
		}
		this._callBack=callback_obj;
		return true;
	}
}


export {CRMIObjectBind,CRMIProxyCallBackObject}
