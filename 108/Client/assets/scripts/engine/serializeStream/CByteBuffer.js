
import {isUndefined} from '../util/CUtil'

const MAX_BUFFER_SIZE=1024*100;


let concatArrayBuffer=function(ArrayBufferLeft,leftLen,ArrayBfferRight,rightLen){
	//console.log("left.byteLength="+ArrayBufferLeft.byteLength+",get="+leftLen+",right.byteLength="+ArrayBfferRight.byteLength+",get="+rightLen)
	let tmp=new Uint8Array(leftLen+rightLen);
	tmp.set(new Uint8Array(ArrayBufferLeft,0,leftLen),0);
	tmp.set(new Uint8Array(ArrayBfferRight,0,rightLen),leftLen);
	return tmp.buffer;
};

let popArrayBuffer=function(ArrayBfferValue,len){
	console.log("popArrayBuffer,byteLength"+ArrayBfferRight.byteLength+",pop size="+len)
	let left_len=ArrayBfferValue.byteLength-len;
	if(left_len<=0)
		left_len=0;
	let tmp=new Uint8Array(left_len);
	tmp.set(new Uint8Array(ArrayBfferValue,len,left_len));
	return tmp.buffer;
}

class CByteBuffer{
	//------this is props
	_buffer=new ArrayBuffer(0);
	_dataSize=0;

	//-------next is function
	constructor(){

	}
	append(arrayBuffer,len){
		this._buffer=concatArrayBuffer(this._buffer,this._dataSize,arrayBuffer,len);
		this._dataSize=this._buffer.byteLength;
	}
	getData(){
		return this._buffer;
	}
	getDataSize(){
		return this._dataSize;
	}
	popData(len){
		this._buffer=popArrayBuffer(this._buffer,len);
		this._dataSize=this._buffer.byteLength;
	}

}

export {CByteBuffer,concatArrayBuffer}