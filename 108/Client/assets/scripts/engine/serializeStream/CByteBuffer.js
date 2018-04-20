

const MAX_BUFFER_SIZE=1024*100

class CByteBuffer{
	constructor(buffer_size){
		//this.buffer_size=buffer_size?MAX_BUFFER_SIZE;
	}
	getBufferSize(){
		return this.buffer_size;
	}
}

export {CByteBuffer}