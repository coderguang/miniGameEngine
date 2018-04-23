

import {CByteBuffer} from './CByteBuffer'

const SIZE_OF_BYTE=1; // Int8
const SIZE_OF_INT=4; //Int32
const SIZE_OF_SHORT=2; //Int16
//const SIZE_OF_LONG64=8; //js not support long type,but can support by Internet coder
const SIZE_OF_FLOAT=4;//Float32
const SIZE_OF_DOUBLE=8; //Float64 ?

const FLAG_BIT_INIT=0x80
const SIZE_BYTE_MAX=0xFE; //254
const UNSIGNED_BYTE_MAX=0xFF; //255

const MAX_DEFAULT_VALUE_NUM=100; // 100*8=800

class CSerializeStream extends CByteBuffer{
		
	//----props

	_useBitMark=false;
	_isUseFlagBitMark=false;
	_flagBytes=new Uint8Array(MAX_DEFAULT_VALUE_NUM); //最多800个默认值,还多的话我也是无语
	_flagByteWritePos=0;
	_flagBit=new Uint8Array(1);
	_flagBit=FLAG_BIT_INIT;
	_flagByte=new Uint8Array(1);
	_flagByte=0;
	_readIndex=0;
	_flagByteReadPos=0
	_flagByteSize=0; //flagByte real size
	_isLittleEndian=true;
	_readView;

	//functions

	constructor(){
		super();
	}

	getEndian(){
		return this._isLittleEndian;
	}

	// flagBit function
	markBitFlag(isDefault){
		if(this._useBitMark)
		{
			return ;
		}
		if(isDefault){
			this._flagByte|=this._flagBit;
			if(!this._isUseFlagBitMark)
			{
				this._isUseFlagBitMark=true;
			}
		}
		this._flagBit=this._flagBit>>1;
		if(0==this._flagBit){
			if(this._flagByteWritePos>=MAX_DEFAULT_VALUE_NUM){
				console.log("too many default params,error");
				return ;
			}
			this._flagBytes[this._flagByteWritePos]=this._flagByte;
			this._flagByteWritePos+=1;
			this._flagByteSize=this._flagByteWritePos+1;
			this._flagBit=FLAG_BIT_INIT;
			this._flagByte=0;
		}
	}

	readBitFlag(){
		if(this._useBitMark||this._flagByteSize<=this._flagByteReadPos){
			return false;
		}
		let result=this._flagByte&this._flagBit;
		this._flagBit=this._flagBit>>1;
		if(0==this._flagBit){
			this._flagBit=FLAG_BIT_INIT;
			this._flagByte=this._flagBytes[this._flagByteReadPos];
			this._flagByteReadPos+=1;
		}
		return !!result;  //change to boolean
	}

	prepareToAppend(){
		if(this._isUseFlagBitMark){
			if(0!=this._flagByte){
				this._flagBytes[this._flagByteWritePos]=this._flagByte;
				this._flagByteSize=this._flagByteWritePos+1;
				this._isUseFlagBitMark=false;
				this._flagByte=0;
			}
		}
		this._flagBit=FLAG_BIT_INIT;
	}

	prepareToRead(){
		this._readView=new DataView(this.getData(),this.getReadPoint());
		return ;
		this._flagByteSize=this.readSizeInt();
		if(this._flagByteSize>0){
			for(let i=0;i<this._flagByteSize;i++){
				let v=this.readByte();
				this._flagBytes[i]=v;
			}
			this._flagBit=FLAG_BIT_INIT;
			this._flagByteReadPos=0;
		}
		this._readView=new DataView(this.getData(),this.getReadPoint());
	}

	setUseBitMark(useBitMark){
		this._useBitMark=useBitMark;
	}
	getUseBitMark(){
		return this._useBitMark;
	}

	getFlagDataSize(){
		return this._flagByteSize;
	}

	getFlagData(){
		return this._flagBytes;
	}


	getReadPoint(){
		return this._readIndex;
	}
	addReadIndex(len){
		this._readIndex+=len;
	}


	//read write function
	writeSizeInt(size){
		this.writeSizeUInt(size);
	}
	readSizeInt(){
		return this.readSizeUint();
	}

	writeSizeUInt(size){
		if(0==size&&this._useBitMark){
			this.markBitFlag(true);
		}else{
			this.markBitFlag(false);
			if(size<0){
				console.log("CSerializeStream::writeSizeUInt size less than 0,error");
			}
			let originalUseBitMark=this._useBitMark;
			this._useBitMark=false;
			if(size>SIZE_BYTE_MAX){
				this.writeByte(UNSIGNED_BYTE_MAX);
				this.writeInt(size);
			}else{
				this.writeByte(size);
			}
			this._useBitMark=originalUseBitMark;
		}
	}

	readSizeUint(){
		let size=0;
		if(this._useBitMark&&this.readBitFlag()){
			size=0;
		}else{
			let originalUseBitMark=this._useBitMark;
			this._useBitMark=false;
			size=this.readByte();
			if(UNSIGNED_BYTE_MAX==size){
				size=this.readInt();
				if(size<0){
					console.log("CSerializeStream::readSizeUint size less than 0,error");
					size=0;
				}
			}
			this._useBitMark=originalUseBitMark;
		}
		return size;
	}

	writeByte(v){
		if(0==v&&this._useBitMark){
			this.markBitFlag(true);
		}else{
			this.markBitFlag(false);
			let data=new ArrayBuffer(SIZE_OF_BYTE);
			let view=new DataView(data);
			view.setUint8(0,v,this.getEndian());
			this.append(data,SIZE_OF_BYTE);
		}
	}

	readByte(){
		if(this._useBitMark&&this.readBitFlag()){
			return 0;
		}else{
			let v=this._readView.getUint8(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_BYTE);
			return v;
		}
	}

	writeByteSeq(v){
		let size=v.length;
		this.writeSizeInt(size);
		if(size>0){
			let data=new ArrayBuffer(size*SIZE_OF_BYTE);
			let view=new DataView(data);
			for(let i=0;i<size;i++){ //数组具体内容不使用	bitflag	
				view.setUint8(i*SIZE_OF_BYTE,v[i],this.getEndian());
			}
			this.append(data,size*SIZE_OF_BYTE);
		}
	}
	readByteSeq(){
		let size=this.readSizeInt();
		let v=new Uint8Array(size);
		for(let i=0;i<size;i++){
			v[i]=this._readView.getUint8(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_BYTE);
		}
		return v;
	}

	writeBoolean(v){
		this.writeByte(Number(v));
	}
	readBoolean(){
		return this.readByte()>0?true:false;
	}
	writeBooleanSeq(v){
		let size=v.length;
		let bv=new Uint8Array(size);
		for(let i=0;i<size;i++){
			bv[i]=Number(v[i]);
		}
		this.writeByteSeq(bv);
	}
	readBooleanSeq(){
		let bv=this.readByteSeq();
		let size=bv.length;
		for(let i=0;i<size;i++){
			bv[i]=!!(bv[i]==0?false:true);
		}
		return bv;
	}

	writeShort(v){
		if(0==v&&this._useBitMark){
			this.markBitFlag(true);
		}else{
			this.markBitFlag(false);
			let data=new ArrayBuffer(SIZE_OF_SHORT);
			let view=new DataView(data);
			view.setInt16(0,v,this.getEndian());
			this.append(data,SIZE_OF_SHORT);
		}
	}
	readShort(){
		if(this._useBitMark&&readBitFlag()){
			return 0;
		}else{
			let v=this._readView.getInt16(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_SHORT);
			return v;
		}
	}

	writeShortSeq(v){
		let size=v.length;
		this.writeSizeInt(size);
		if(size>0){
			let data=new ArrayBuffer(size*SIZE_OF_SHORT);
			let view=new DataView(data);
			for(let i=0;i<size;i++){
				view.setInt16(i*SIZE_OF_SHORT,v[i],this.getEndian());
			}
			this.append(data,size*SIZE_OF_SHORT);
		}

	}
	readShortSeq(){
		let size=this.readSizeInt();
		let v=new Int16Array(size);
		for(let i=0;i<size;i++){
			v[i]=this._readView.getInt16(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_SHORT);
		}
		return v;
	}


	writeFloat(v){
		if(0.0==v&&this._useBitMark){
			this.markBitFlag(true);
		}else{
			this.markBitFlag(false);
			let data=new ArrayBuffer(SIZE_OF_FLOAT);
			let view=new DataView(data);
			view.setFloat32(0,v,this.getEndian());
			this.append(data,SIZE_OF_FLOAT);
		}
	}
	readFloat(){
		if(this._useBitMark&&readBitFlag()){
			return 0.0;
		}else{
			let v=this._readView.getFloat32(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_FLOAT);
			return v;
		}
	}

	writeFloatSeq(v){
		let size=v.length;
		this.writeSizeInt(size);
		if(size>0){
			let data=new ArrayBuffer(size*SIZE_OF_FLOAT);
			let view=new DataView(data);
			for(let i=0;i<size;i++){
				view.setFloat32(i*SIZE_OF_FLOAT,v[i],this.getEndian());
			}
			this.append(data,size*SIZE_OF_FLOAT);
		}
	}
	readFloatSeq(){
		let size=this.readSizeInt();
		let v=new Float32Array(size);
		for(let i=0;i<size;i++){
			v[i]=this._readView.getFloat32(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_FLOAT);
		}
		return v;
	}


	writeDouble(v){
		if(0.0==v&&this._useBitMark){
			this.markBitFlag(true);
		}else{
			this.markBitFlag(false);
			let data=new ArrayBuffer(SIZE_OF_DOUBLE);
			let view=new DataView(data);
			view.setFloat64(0,v,this.getEndian());
			this.append(data,SIZE_OF_DOUBLE);
		}
	}

	readDouble(){
		if(this._useBitMark&&readBitFlag()){
			return 0;
		}else{
			let v=this._readView.getFloat64(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_DOUBLE);
			return v;
		}
	}
	writeDoubleSeq(v){
		let size=v.length;
		this.writeSizeInt(size);
		if(size>0){
			let data=new ArrayBuffer(size*SIZE_OF_DOUBLE);
			let view=new DataView(data);
			for(let i=0;i<size;i++){
				view.setFloat64(i*SIZE_OF_DOUBLE,v[i],this.getEndian());
			}
			this.append(data,size*SIZE_OF_DOUBLE);
		}
	}
	readDoubleSeq(){
		let size=this.readSizeInt();
		let v=new Float64Array(size);
		for(let i=0;i<size;i++){
			v[i]=this._readView.getFloat64(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_DOUBLE);
		}
		return v;
	}

	writeSizeIntWithoutBitMark(v){
		let data=new ArrayBuffer(SIZE_OF_INT);
		let view=new DataView(data);
		view.setInt32(0,v,this.getEndian());
		this.append(data,SIZE_OF_INT);
	}
	readSizeIntWithoutBitMark(){
		let v=this._readView.getInt32(this.getReadPoint(),this.getEndian());
		this.addReadIndex(SIZE_OF_INT);
		return v;
	}

	writeInt(v){
		if(0==v&&this._useBitMark){
			this.markBitFlag(true);
		}else{
			this.markBitFlag(false);
			let data=new ArrayBuffer(SIZE_OF_INT);
			let view=new DataView(data);
			view.setInt32(0,v,this.getEndian());
			this.append(data,SIZE_OF_INT);
		}
	}

	readInt(){
		if(this._useBitMark&&readBitFlag()){
			return 0;
		}else{
			let v=this._readView.getInt32(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_INT);
			return v;
		}
	}
	writeIntSeq(v){
		let size=v.length;
		this.writeSizeInt(size);
		if(size>0){
			let data=new ArrayBuffer(size*SIZE_OF_INT);
			let view=new DataView(data);
			for(let i=0;i<size;i++){
				view.setInt32(i*SIZE_OF_INT,v[i],this.getEndian());
			}
			this.append(data,size*SIZE_OF_INT);
		}
	}
	readIntSeq(){
		let size=this.readSizeInt();
		let v=new Int32Array(size);
		for(let i=0;i<size;i++){
			v[i]=this._readView.getInt32(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_INT);
		}
		return v;
	}

	writeString(v){
		let strlen=v.length;
		this.writeSizeInt(strlen);
		if(strlen>0){
			let data=new ArrayBuffer(strlen*SIZE_OF_BYTE);
			let view=new DataView(data);
			for(let i=0;i<strlen;i++){
				view.setUint8(i,v.charCodeAt(i),this.getEndian());
			}
			this.append(data,strlen*SIZE_OF_BYTE);
		}
	}
	readString(){
		let strlen=this.readSizeInt();
		let v=new Uint8Array(strlen);
		for(let i=0;i<strlen;i++){
			v[i]=this._readView.getUint8(this.getReadPoint(),this.getEndian());
			this.addReadIndex(SIZE_OF_BYTE);
		}
		return String.fromCharCode.apply(null,new Uint8Array(v));
	}

	writeStringSeq(v){
		let size=v.length;
		this.writeSizeInt(size);
		if(size>0){
			let originalUseBitMark=this._useBitMark;
			this._useBitMark=false;
			for(let i=0;i<size;i++){
				this.writeString(v[i]);
			}
			this._useBitMark=originalUseBitMark;
		}
	}

	readStringSeq(){
		let size=this.readSizeInt();
		let strSeq=new Array();
		if(size>0){
			let originalUseBitMark=this._useBitMark;
			for(let i=0;i<size;i++){
				strSeq.push(this.readString());
			}
			this._useBitMark=originalUseBitMark;
		}
		return strSeq;
	}


	print(){
		console.log("CSerializeStream data:")
		console.log("_useBitMark:"+this._useBitMark);
		console.log("_isUseFlagBitMark:"+this._isUseFlagBitMark);
		console.log("_flagBytes:"+this._flagBytes);
		console.log("_flagBit:"+this._flagBit);
		console.log("_flagByte:"+this._flagByte);
		console.log("_readIndex:"+this._readIndex);
		console.log("_flagByteReadPos:"+this._flagByteReadPos);
	}
};


export {CSerializeStream}