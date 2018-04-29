import {CMsgManager} from 'CMsgManager'

class SHandlerId{
	//props
	id;
	type;
	typeEx;
	typeEx2;

	constructor(){
		this._csg_init();	
	}

	_csg_init(){
		this.type=0;
		this.id=0;
		this.typeEx=0;
		this.typeEx2=0;
	}
	_csg_write(__os){
		__os.writeInt(this.id);
		__os.writeInt(this.type);
		__os.writeInt(this.typeEx);
		__os.writeInt(this.typeEx2);
	}
	_csg_read(__is){
		this.id=__is.readInt();
		this.type=__is.readInt();
		this.typeEx=__is.readInt();
		this.typeEx2=__is.readInt();
	}

}

class SMsgHead{
	//props

	command;
	fromId;

	constructor(){
		this._csg_init();
	}

	_csg_init(){
		this.command=0;
		this.fromId=new SHandlerId();
	}
	_csg_write(__os){
		__os.writeInt(this.command);
		this.fromId._csg_write(__os);
	}
	_csg_read(__is){
		this.command=__is.readInt();
		this.fromId._csg_read(__is);
	}

}


class CMsgBlock{
	_msgHead;
	_msgBase;

	constructor(){
		this._msgHead=new SMsgHead();
		this._msgHead._csg_init();

		if(typeof this._msgBase !== "undefined"){
			this._msgBase._csg_init();
		}
	}

	_csg_write(__os){
		__os.setUseBitMark(false);
		this._csg_writeHead(__os);
		__os.setUseBitMark(true);
		this._csg_writeBody(__os);
	}

	_csg_writeHead(__os){
		this._msgHead._csg_write(__os);
	}

	_csg_writeBody(__os){
		if(typeof this._msgBase !=="undefined"){
			__os.writeInt(this._msgBase.getType());
			this._msgBase._csg_write(__os);
		}else{
			__os.writeByte(0);
		}
	}	


	_csg_read(__is){
		__is.setUseBitMark(false)
		this._csg_readHead(__is);
		__is.setUseBitMark(true);
		this._csg_readBody(__is);
	}

	_csg_readHead(__is){
		this._msgHead._csg_read(__is);
	}

	_csg_readBody(__is){
		let type=__is.readInt();
		if(0!=type){
			this._msgBase=CMsgManager.getInstance().createMsg(type);
			if(this._msgBase !== "undefined"){
				this._msgBase._csg_read(__is);
			}else{
				console.log("read body no this type:"+type)
			}
		}
	}
}



export {SHandlerId,CMsgBlock}
















