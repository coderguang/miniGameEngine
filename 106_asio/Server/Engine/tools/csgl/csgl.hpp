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

struct CSGEnum{
	std::string identify;
	int value;
	void clear(){
		identify="";
		value=0;

	}
};

enum CSGStlType{
	CSGStlTypeOne=1,
	CSGStlTypeDouble=2,
};

struct CSGStruct{
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

struct CSGInterfaceParam{
	std::string type;
	bool isOut;
	std::string identify;
	void clear(){
		type="";
		isOut=false;
		identify="";
	}
};

struct CSGInterface{
	int rpcId;
	std::string funcName;
	std::vector<CSGInterfaceParam> paramList;
	void clear(){
		rpcId=0;
		funcName="";
		paramList.clear();
	};
};


struct CSGType{
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
#include \"engine/serialize/serializestream\.h\"\n\
#include \"engine/def/csg_def\.h\"\n\
#include \"engine/mq/msgBlock\.h\"\n\
#include \"engine/mq/msgManager\.h\"\n\
#include \"engine/rpc/rmiObject.h\"\n";

static std::string csgDefStr="\
//******************************************\n\
// generated by royalchen's csgl tools\n\
// email:royalchen@royalchen.com \n\
// FAQ:www.royalchen.com\n\
// ******************************************";


static std::string jsonfile="../MessageCsgl/csgl.json";

class CSGStream{
public:
	std::string content;
};

static CSGStream& operator<<(CSGStream& os,std::string str){
	os.content+=str;
	return os;
};


extern "C"{
	extern int yylex(void);
	extern void yyerror(const char* s);
}


#define YYSTYPE CSGType
#define YYDEBUG 1
#define YYERROR_VERBOSE






#endif

