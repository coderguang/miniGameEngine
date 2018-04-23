// Learn cc.Class:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/class.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/class.html
// Learn Attribute:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/reference/attributes.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/life-cycle-callbacks.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/life-cycle-callbacks.html

import {CRmi} from '../engine/rmi/CRmi'
import {CByteBuffer,concatArrayBuffer} from '../engine/serializeStream/CByteBuffer'
import {CSerializeStream} from '../engine/serializable/CSerializeStream'
import {CSession} from '../engine/net/session/CSession'
import {MITest} from '../message/MITest'

function test(){
    console.log("test ok");
}

function testSerialize(){
 console.log("test concat");
        let bf1=new ArrayBuffer(10);
        let bv1=new DataView(bf1);
        bv1.setInt32(0,2323,true);

        let bf2=new ArrayBuffer(10);
        let bv2=new DataView(bf2);
        bv2.setInt32(0,-13323,true);

        let tmp=concatArrayBuffer(bf1,4,bf2,4);
        let tmpbv=new DataView(tmp);
        let v1=tmpbv.getInt32(0,true);
        let v2=tmpbv.getInt32(4,true);
        //console.log("v1="+v1+",v2="+v2);

        //test serialize
        let ss=new CSerializeStream();
        ss.setUseBitMark(false);
        ss.writeByte(232);
        ss.writeInt(234242);
        ss.writeBoolean(true);
        ss.writeShort(3242);
        ss.writeFloat(24.242); 
        ss.writeDouble(233.2431);

        let hi="hi,are you ok?zzz..."
        ss.writeString(hi);

        let hiex=""
        ss.writeString(hiex);


        let byteseq=new Uint8Array(4);
        byteseq[0]=22;
        byteseq[1]=33;
        byteseq[2]=44;
        byteseq[3]=55;

        ss.writeByteSeq(byteseq);

        let intseq=new Int32Array(3);
        intseq[0]=4647646;
        intseq[1]=4647323;
        intseq[2]=554647646;

        ss.writeIntSeq(intseq);

        let shortSeq=new Int16Array(4);
        shortSeq[0]=464;
        shortSeq[1]=23;
        shortSeq[2]=-554;

        ss.writeShortSeq(shortSeq);

        let boolseq=new Uint8Array(3);
        boolseq[0]=true;
        boolseq[1]=false;
        boolseq[2]=false;

        ss.writeBooleanSeq(boolseq);

        console.log(boolseq);

        let floatseq=new Float32Array(3);
        floatseq[0]=464.7646;
        floatseq[1]=46.47323;
        floatseq[2]=554.647646;

        ss.writeFloatSeq(floatseq);


        let doubleseq=new Float64Array(3);
        doubleseq[0]=464.7646;
        doubleseq[1]=4647.323;
        doubleseq[2]=55464.7646;

        ss.writeDoubleSeq(doubleseq);

        let sseq=new Array("hi","hello","how are you");
        ss.writeStringSeq(sseq);

        ss.prepareToRead();

        let bv=ss.readByte();
        let iv=ss.readInt();
        let blv=ss.readBoolean();
        let sv=ss.readShort();
        let fv=ss.readFloat();
        let dv=ss.readDouble();
        let str=ss.readString();
        let strex=ss.readString();
        let byteseqv=ss.readByteSeq();
        let intseqv=ss.readIntSeq();
        let shortseqv=ss.readShortSeq();
        let boolseqv=ss.readBooleanSeq();
        let floatseqv=ss.readFloatSeq();
        let doubleseqv=ss.readDoubleSeq();
        let sseqv=ss.readStringSeq();

        console.log("bv="+bv);
        console.log("iv="+iv);
        console.log("blv="+blv);
        console.log("sv="+sv);
        console.log("fv="+fv);
        console.log("dv="+dv);
        console.log("str="+str);
        console.log("strex="+strex);
        console.log(byteseqv);
        console.log(intseqv);
        console.log(shortseqv);
        console.log(floatseqv);
        console.log(doubleseqv);
        console.log(boolseqv);
        console.log(sseqv);
}

function testSocket(){
    let session=new CSession();
    session.init("test.royalchen.com",9201);
    session.startConnect();

    let mitest=new MITest();
    let cb=3;
    setTimeout(function(){
        mitest.t1_async(session,3);
        mitest.t2_async(session,5,"are you ok,zz");
    },5000);


}

cc.Class({
    extends: cc.Component,

    properties: {
        // foo: {
        //     // ATTRIBUTES:
        //     default: null,        // The default value will be used only when the component attaching
        //                           // to a node for the first time
        //     type: cc.SpriteFrame, // optional, default is typeof default
        //     serializable: true,   // optional, default is true
        // },
        // bar: {
        //     get () {
        //         return this._bar;
        //     },
        //     set (value) {
        //         this._bar = value;
        //     }
        // },
    },

    // LIFE-CYCLE CALLBACKS:

     onLoad () {
       //testSerialize();
       testSocket();
     },

    start () {
        console.log("mainGame star");
        
    },

    // update (dt) {},
});
