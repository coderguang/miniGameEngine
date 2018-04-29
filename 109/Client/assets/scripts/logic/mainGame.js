// Learn cc.Class:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/class.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/class.html
// Learn Attribute:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/reference/attributes.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/life-cycle-callbacks.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/life-cycle-callbacks.html

import {CByteBuffer,concatArrayBuffer} from '../engine/serializeStream/CByteBuffer'
import {CSerializeStream} from '../engine/serializeStream/CSerializeStream'
import {CSession} from '../engine/net/session/CSession'
import {CMsgManager} from '../engine/mq/CMsgManager'
import {CException,ECSGEErrorCode,ECSGEErrorCodeSystem} from '../engine/exception/CException'

import {ETest,STest,STestMap,SScapyTest,ITest,CCli_ITest_t1_callBack,CCli_ITest_t2_callBack,CCli_ITest_t3_callBack,CCli_ITest_t4_callBack,CCli_ITest_t5_callBack,CCli_ITest_t6_callBack,CCli_ITest_t7_callBack} from '../message/Test'
import {ETestStruct,STestStruct} from '../message/TestStruct'

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

        ss.initReadView();

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

function testMap(){
    let t=new Map();
    t["1"]=4;
    t["3"]=4;
    t["3"]=4;
    t["2"]=4;
    t.set("5",45);
    let size=Object.keys(t).length;
    console.log("size="+size)
    // for( let [key,value] of t.entries()){--erro
    //     console.log(key+","+value)
    // }
    // t.forEach(function(value,key){---error
    //     console.log("aaa");
    //     console.log(key+","+value)
    // },t);
    for(let v in t){
        console.log("aaa");
    }
}

function testSocket(){
    // testMap();
    // return ;
    console.log("testSocket")

    CMsgManager.getInstance().regist(new STestStruct());
    CMsgManager.getInstance().regist(new STest());
    CMsgManager.getInstance().regist(new STestMap());
    CMsgManager.getInstance().regist(new SScapyTest());

    //CSession.getInstance().init("test.royalchen.com",9201);
    //CSession.getInstance().init("game.0cpp.com",9201);
    //CSession.getInstance().init("192.168.100.104",9201);
    CSession.getInstance().init("127.0.0.1",9201);
    CSession.getInstance().startConnect(false);
    //CSession.getInstance().startConnect(true);
    
    let proxy_test=new ITest();
    let cbb=new CCli_ITest_t3_callBack(
        function(a,os){
            console.log("res by inner,a="+a+",os="+os);
    },
        function(ex){
            console.log("error");
    });

    let test=new STest();
    test.a=5657;
    test.b=false;
    test.str="gewgwoe";
    test.ib.push(46);
    test.il.push(1);
    test.il.push(3);
    test.il.push(4);
    test.il.push(7);
    test.is.push("hi how are you");
    test.is.push("hi how are you ok");
    let mm=new Map();
    //mm.set("1",test);
    mm["1"]=test;
    test.ib.push(783);
    mm["2"]=test;
    //mm.set("2",test);
    test.ib.push(78335);
    mm["3"]=test;
    //mm.set("34668",test);

    let t7=new CCli_ITest_t6_callBack(
        function(v){
            //console.log("res by inner,a="+a+",os="+os);
             console.log("success t7");
        },
        function(ex){
            console.log("error");
    }
    );

    let t5=new CCli_ITest_t5_callBack(
        function(v){
            console.log("success t5");
        },
        function(ex){
            console.log("error t5");
        }
        );

    setTimeout(function(){
        //mitest.t1_async(CSession.getInstance(),3);
        //mitest.t2_async(CSession.getInstance(),5,"hi.hello");
        //mitest.t7_async(CSession.getInstance(),88,st);
        //proxy_test.t3_async(CSession.getInstance(),5,"hi.hellot2",cbb);
        proxy_test.t6_async(CSession.getInstance(),mm,t7);
        proxy_test.t5_async(CSession.getInstance(),new Array(),t5);
    },5000);
}

function testException(){
   

    let ex=new CException(ECSGEErrorCodeSystem.ExceptionCodeMsgTypeNotRegist,"not regist the type");
    //let code=ex.code();
    try{
        throw ex;
    }catch(err){
        console.log("error,what="+err.message);
    }
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
       //testException();
     },

    start () {
        console.log("mainGame star");
        
    },

    // update (dt) {},
});
