

import {CException,ECSGEErrorCode} from '../exception/CException'

class CMsgManager{
	//prop
	_msgMap;
	static _instance;
	constructor(){
		this._msgMap=new Map();
	}
	regist(msgBlock){
		if(!this._msgMap[msgBlock.getType()]==null){
			console.log("CMsgManager::regist duplicate type="+msgBlock.getType());
			throw new CException(ECSGEErrorCode.ExceptionCodeRMIBase,"duplicate regist tyep");
			return false;
		}
		this._msgMap[msgBlock.getType()]=msgBlock;
		return true;
	}
	createMsg(type){
		if(this._msgMap[type]==null){
			console.log("CMsgManager::createMsg no this type"+type);
			return false;
		}
		return this._msgMap[type].clone();
	}
	static getInstance(){
		if(false === this._instance instanceof this){
			this._instance=new this;
		}
		return this._instance;
	}
}

export {CMsgManager}