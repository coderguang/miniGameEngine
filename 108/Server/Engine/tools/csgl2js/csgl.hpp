//c++ header file
/*
#***********************************************
#
#      Filename: csgl.h
#
#      Author: coderguang 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#

#     Create: 2017-09-09 12:56:17
#     Last Modified: 2017-09-09 12:56:17
#***********************************************

*/

#ifndef _CSG_L_
#define _CSG_L_

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <cassert>

struct CSGEnum{ //记录 enum 內单个枚举的结构
	std::string identify;
	int value;
	void clear(){
		identify="";
		value=0;

	}
};

enum CSGStlType{  //判断是vector还是map
	CSGStlTypeOne=1,
	CSGStlTypeDouble=2,
};

struct CSGStruct{  // 记录结构体内,单个成员变量的信息
	std::string type;
	std::string identify;
	int stlTypeNum;
	std::string stlType; //针对vector,map等的解决方案
	std::string stlTypeEx;
	void clear(){
		type="";
		identify="";
		stlType="";
		stlTypeEx="";
		stlTypeNum=0;
	};

};

struct CSGInterfaceParam{  // 记录接口中，单个参数的数据信息
	std::string type;    //类型
	bool isOut;			 //是否是返回值
	std::string identify;  // identify
	int stlTypeNum;        // vector or map
	std::string stlType;  // vector
	std::string stlTypeEx;
	void clear(){
		type="";
		isOut=false;
		identify="";
		stlTypeNum=0;
		stlType="";
		stlTypeEx="";
	}
};

struct CSGInterface{  //单个接口的所有信息
	int rpcId;
	std::string funcName;
	std::vector<CSGInterfaceParam> paramList;
	void clear(){
		rpcId=0;
		funcName="";
		paramList.clear();
	};
};


struct CSGType{  //单个文件内的所有信息
	int id; //identify id
	int t_int;
	float t_float;
	double t_double;
	long t_long;
	std::string t_string;
	bool t_bool;
	std::vector<std::string> ts_list;
	//for enum
	CSGEnum tmpEnumKey;
	std::vector<CSGEnum> te_list;
	//for struct
	CSGStruct tmpStructKey;
	std::vector<CSGStruct> tstruct_list;
	//for interface
	CSGInterface tmpInterfaceKey;
	CSGInterfaceParam tmpInterfaceParamKey;
	std::vector<CSGInterface> tinterface_list;
	void clear(){
		id=0;
		t_int=0;
		t_float=0.0;
		t_double=0.0;
		t_long=0;
		t_string="";
		t_bool=false;
		ts_list.clear();
		tmpEnumKey.clear();
		te_list.clear();
		tmpStructKey.clear();
		tstruct_list.clear();
		tmpInterfaceKey.clear();
		tmpInterfaceParamKey.clear();
		tinterface_list.clear();
	}
};


//用于区分唯一key
class CSGStructKey{
public:
	int id;
	std::string name;
	std::string fileName;
};

class CSGInterfaceKey{
public:
	int rpcId;
	std::string interfaceFile;
	std::string interface;	
};

typedef std::map<int,CSGStructKey> MapStructId;
typedef std::map<std::string,CSGStructKey> MapStructName;

typedef std::map<int,CSGInterfaceKey> MapInterfaceId;
typedef std::map<std::string,CSGInterfaceKey> MapInterfaceName;
typedef std::map<std::string,MapInterfaceName> MapInterfaceFileName;


static std::string includeCsgFile="\
import {SRMICall} from \'../engine/rmi/CRmiDef\'\n\
import {CSerializeStream} from \'../engine/serializeStream/CSerializeStream\'\n\
import {CRpcHelper} from \'../engine/rmi/CRpcHelper\'\n\
import {CRMIProxyCallBackObject} from \'../engine/rmi/CRmiObject\'\n";


static std::string csgDefStr="\
//******************************************\n\
// generated by royalchen's csgl tools\n\
// email:royalchen@royalchen.com \n\
// FAQ:www.royalchen.com\n\
// ******************************************";


static std::string jsonfile="../MessageCsgl/csgljs.json";

class CSGStream{
public:
	std::string content;
};

static CSGStream& operator<<(CSGStream& os,std::string str){
	os.content+=str;
	return os;
};

static const std::string CSGL_INT="int";
static const std::string CSGL_FLOAT="float";
static const std::string CSGL_DOUBLE="double";
static const std::string CSGL_BOOL="bool";
static const std::string CSGL_LONG="long";
static const std::string CSGL_LONG64="long64_t";
static const std::string CSGL_STRING="string";
static const std::string CSGL_STD_STRING="std::string";



static std::set<std::string> baseTypeSet={CSGL_INT,CSGL_FLOAT,CSGL_DOUBLE,CSGL_BOOL,CSGL_LONG,CSGL_STRING};

static bool isBaseType(std::string type){
	return baseTypeSet.count(type)>0;
}

static std::string getCsglType(std::string type){
	if(CSGL_INT==type||CSGL_FLOAT==type||CSGL_DOUBLE==type||CSGL_BOOL==type)
		return type;
	if(CSGL_LONG==type)
		return CSGL_LONG64;
	if(CSGL_STRING==type)
		return CSGL_STD_STRING;
	return type; //自定义结构体
}

static std::string getInitTypeString(std::string type){
	if(CSGL_INT==type){
		return "0";
	}
	else if(CSGL_FLOAT==type){
		return "0.0f";
	}else if(CSGL_DOUBLE==type){
		return "0.0";
	}else if(CSGL_BOOL==type){
		return "false";
	}else if(CSGL_LONG==type){
		return "0";
	}else if(CSGL_STRING==type){
		return "\"\"";
	}

	assert(false);
	std::cout<<"getInitTypeString:error type:"<<type<<std::endl;
	return "";
}

static std::string getReadWriteString(std::string type){
	if(CSGL_INT==type){
		return "Int";
	}
	else if(CSGL_FLOAT==type){
		return "Float";
	}else if(CSGL_DOUBLE==type){
		return "Double";
	}else if(CSGL_BOOL==type){
		return "Boolean";
	}else if(CSGL_LONG==type){
		return "0";
	}else if(CSGL_STRING==type){
		return "String";
	}

	assert(false);
	std::cout<<"getReadWriteString:error type:"<<type<<std::endl;
	return "";
}




extern "C"{
	extern int yylex(void);
	extern void yyerror(const char* s);
}


#define YYSTYPE CSGType
#define YYDEBUG 1
#define YYERROR_VERBOSE






#endif

