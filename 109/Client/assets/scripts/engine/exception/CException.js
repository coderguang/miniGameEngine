

if(typeof ECSGEErrorCode=="undefined"){
	var ECSGEErrorCode={};
	ECSGEErrorCode.ExceptionCodeSystemBase = 10000 ;
	ECSGEErrorCode.ExceptionCodeRMIBase = 20000 ;
	ECSGEErrorCode.ExceptionCodeUserBase = 30000;
}

if(typeof ECSGEErrorCodeSystem=="undefined"){
	var ECSGEErrorCodeSystem={};
	ECSGEErrorCodeSystem.ExceptionCodeUnknow = 10000;
	ECSGEErrorCodeSystem.ExceptionCodeOutOffMemery = 10001;
	ECSGEErrorCodeSystem.ExceptionCodeReadOnly = 10002;  // searilize exception
	ECSGEErrorCodeSystem.ExceptionCodeDatetime = 10003;//datetime exception
	ECSGEErrorCodeSystem.ExceptionCodeMsgTypeNotRegist = 10004;//mq msg type not regist
	ECSGEErrorCodeSystem.ExceptionCodeSerialize = 10005; //serialize error
	ECSGEErrorCodeSystem.ExceptionCodeStd = 10006; //std::exception
	ECSGEErrorCodeSystem.ExceptionCodeCsg = 10007; //logic exception,code by config
}

class CException extends Error{
	_code;
	_msg;
	constructor(code,msg){
		super();
		this._code=code;
		this._msg=msg;
	}
	what(){
		return this._msg;
	}
	code(){
		return this._code;
	}
	setCode(v){
		this._code=v;
	}
	setMessage(v){
		this._msg=v;
	}
}

export {ECSGEErrorCode,ECSGEErrorCodeSystem}
export {CException}