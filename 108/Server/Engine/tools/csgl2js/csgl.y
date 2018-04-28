%{

#include "csgl.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <cassert>
#include <json/json.h>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#ifdef _CSG_LINUX_
	#define RESET   "\033[0m"
	#define BLACK   "\033[30m"      /* Black */
	#define RED     "\033[31m"      /* Red */
	#define GREEN   "\033[32m"      /* Green */
	#define YELLOW  "\033[33m"      /* Yellow */
	#define BLUE    "\033[34m"      /* Blue */
	#define MAGENTA "\033[35m"      /* Magenta */
	#define CYAN    "\033[36m"      /* Cyan */
	#define WHITE   "\033[37m"      /* White */
	#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
	#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
	#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
	#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
	#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
	#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
	#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
	#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#else
	#define RESET   ""
	#define BLACK   ""      /* Black */
	#define RED     ""      /* Red */
	#define GREEN   ""      /* Green */
	#define YELLOW  ""      /* Yellow */
	#define BLUE    ""      /* Blue */
	#define MAGENTA ""      /* Magenta */
	#define CYAN    ""      /* Cyan */
	#define WHITE   ""      /* White */
	#define BOLDBLACK   ""      /* Bold Black */
	#define BOLDRED     ""      /* Bold Red */
	#define BOLDGREEN   ""      /* Bold Green */
	#define BOLDYELLOW  ""      /* Bold Yellow */
	#define BOLDBLUE    ""      /* Bold Blue */
	#define BOLDMAGENTA ""      /* Bold Magenta */
	#define BOLDCYAN    ""      /* Bold Cyan */
	#define BOLDWHITE   ""      /* Bold White */

#endif

using namespace std;

void csgInfo(std::string type,std::string s);

std::string toStr(int);


extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;

ofstream ofs;

fstream  jsonfs;
ofstream  jsonofs;

// headfile content
CSGStream headDefStream;
CSGStream endDefStream;
CSGStream headIncludeStream;
CSGStream headfileContentStream;

//cppfile content
CSGStream cppContentStream;

//output info stream
CSGStream outputInfo;

CSGStream exportStream;
CSGStream tipStream;

//interface content
CSGStream headInterfaceStream;
CSGStream cppInterfaceStream;

bool globalError=false;

std::vector<std::string> structVec;


//唯一key,id等
MapStructId mapStructId;
MapStructName mapStructName;
MapInterfaceId mapInterfaceId;
MapInterfaceFileName mapInterfaceFileName;
std::string nowInputFile;

bool checkIsCsglType(std::string type,std::string msg){
	if(mapStructName.find(type)==mapStructName.end()){
		csgInfo(msg,type);
		globalError=true;
		assert(false);
	}
};


%}



// ifndef token
%token TOKEN_IFNDEF TOKEN_IFNDEF_END TOKEN_IFDEF TOKEN_IFDEF_END 
%token <t_string> TOKEN_IFNDEF_FILE TOKEN_IFDEF_FILE TOKEN_ENDIF

//comment token
%token TOKEN_COMMENT_START TOKEN_COMMENT_END TOKEN_COMMENT_EX_START TOKEN_COMMENT_EX_END
%token <t_string> TOKEN_COMMENT_FILE TOKEN_COMMENT_EX_FILE

//include token
%token TOKEN_INCLUDE_START TOKEN_INCLUDE_END TOKEN_INCLUDE_SIGN
%token <t_string> TOKEN_INCLUDE_FILE

//enum
%token <t_string>TOKEN_ENUM_START 
%token <te_list>TOKEN_ENUM_CONTENT

//struct
%token TOKEN_STRUCT_START TOKEN_STRUCT_END
%token <t_string> TOKEN_STRUCT_NAME
%token <tstruct_list> TOKEN_STRUCT_CONTENT

//id
%token TOKEN_ID_START TOKEN_ID_END
%token <id> TOKEN_ID_NUM

//interface
%token TOKEN_INTERFACE_END TOKEN_INTERFACE_ID_START TOKEN_INTERFACE_ID_NUM TOKEN_INTERFACE_ID_END
%token <t_string> TOKEN_INTERFACE_NAME
%token <tinterface_list> TOKEN_INTERFACE_CONTENT
%token <tmpInterfaceKey.funcName> TOKEN_INTERFACE_FUNCTION_NAME


%%

program : program statement|statement{};

statement : define_line | comment |include | enum |struct |interface{};



interface : TOKEN_INTERFACE_NAME TOKEN_INTERFACE_CONTENT {
	//classNameDef

	std::string interfaceName=$1;
	std::vector<CSGInterface> interfaceList=$2;

	outputInfo<<"yacc match interface:"<<interfaceName<<"\n";
	//classNameDef
	std::string interfaceClassName=interfaceName;
	std::string srvCBprefix="CSrv_"+interfaceClassName+"_";
	std::string cliCBprefix="CCli_"+interfaceClassName+"_";

	std::string mNamespace="Message";
	std::string proxyNamespace="csg_proxy";


	exportStream<<"export {"<<interfaceName<<"}\n";
	tipStream<<interfaceName<<",";
	// 客户端部分使用代码
	//======================proxy callBack start============== //客户端回调对象

	CSGStream proxyCallBackDef;
	CSGStream cppProxyCallBack;

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		CSGStream cppProxyCallBackParam;
		CSGStream cppProxyReturnParam;

		CSGStream functionDefStlRead; //额外的读函数
		CSGStream functionCppStlRead; //额外的读函数

		exportStream<<"export {"<<cliCB<<"_callBack}\n";
		tipStream<<cliCB<<"_callBack,";
		proxyCallBackDef<<"class "<<cliCB<<"_callBack\n"
						<<"{\n"
						<<"	_successFunc;\n"
						<<"	_failFunc;\n "
						<<"	constructor(successFunc,failFunc){\n"
						<<"		this._successFunc=successFunc;\n"
						<<"		this._failFunc=failFunc;\n"
						<<"	}\n"
						<<"	__exception(__is)\n"
						<<"	{\n"
						<<"		let ex=__is.readException();\n"
						<<"		this._failFunc(ex);\n"
						<<"	}\n"
						<<"	__response(__is)\n"
						<<"	{\n";

		bool isFirstOutParam=true;
		bool isFirstParam=true;
		
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(param.isOut){
				if(!isFirstOutParam){
					cppProxyReturnParam<<",";				
				}
				if(isBaseType(param.type)){
					proxyCallBackDef<<"		let "<<param.identify<<"=__is.read"+getReadWriteString(param.type)+"();\n";

					cppProxyCallBackParam<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
										<<"	__is.read("<<param.identify<<");\n";

				}else if(CSGStlTypeOne==param.stlTypeNum){
					
					cppProxyCallBackParam<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<"> "<<param.identify<<";\n";
					if(isBaseType(param.stlType)){
						proxyCallBackDef<<"		let "<<param.identify<<"=__is.read"+getReadWriteString(param.stlType)+"Seq();\n";
						cppProxyCallBackParam<<"	__is.read("<<param.identify<<");\n";
					}else{
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classReadFunctionName="_csg_read__STL_TYPE_ONE__Interface_CCli__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;

						proxyCallBackDef<<"		let "<<param.identify<<"=this."+classReadFunctionName+"(__is);\n";

						functionDefStlRead<<"	"<<classReadFunctionName<<"(__is){\n"
											<<"		let size=__is.readSizeInt();\n"
											<<"		let data=new Array();\n"
											<<"		for(let i=0;i<size;i++){\n"
											<<"			let val=new "<<param.stlType<<"();\n"
											<<"			val._csg_read(__is);\n"
											<<"			data.push(val);\n"
											<<"		}\n"
											<<"		return data;\n"
											<<"	}\n";
					}


					
				}else if(CSGStlTypeDouble==param.stlTypeNum){
					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classReadFunctionName="_csg_read__STL_TYPE_DOUBLE__Interface_CCli__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;
					proxyCallBackDef<<"		let "<<param.identify<<"=this."+classReadFunctionName+"(__is);\n";
					functionDefStlRead<<"	"<<classReadFunctionName<<"(__is){\n"
										<<"		let size=__is.readSizeInt();\n"
										<<"		let data=new Map();\n"
										<<"		for(let i=0;i<size;i++){\n";

					if(isBaseType(param.stlType)){
						functionDefStlRead<<"			let key=__is.read"+getReadWriteString(param.stlType)+"();\n";
					}else{
						functionDefStlRead<<"			let key=new "+param.stlType+"();\n"
											<<"			key._csg_read(__is);\n";
					}
					if(isBaseType(param.stlTypeEx)){
						functionDefStlRead<<"			let val=__is.read"+getReadWriteString(param.stlTypeEx)+"();\n";
					}else{
						functionDefStlRead<<"			let val=new "+param.stlTypeEx+"();\n"
											<<"			val._csg_read(__is);\n";
					}

					functionDefStlRead<<"			data[key]=val;\n"
									<<"		}\n"
									<<"		return data;\n"
									<<"	}\n";


				}else{ //自定义结构体
					checkIsCsglType(param.type,"client respond not define struct");
					
					proxyCallBackDef<<"		let "<<param.identify<<"=new "+param.type+"();\n"
									<<"		"<<param.identify<<"._csg_read(__is);\n";

					cppProxyCallBackParam<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
										<<"	"<<param.identify<<"._csg_read(__is);\n";

				}
				isFirstOutParam=false;
				cppProxyReturnParam<<param.identify;
			}
		}
		proxyCallBackDef<<"		this._successFunc("<<cppProxyReturnParam.content<<");\n"
						<<"	}\n"
						<<functionDefStlRead.content
						<<"}\n\n";
	}
	
	headInterfaceStream<<proxyCallBackDef.content<<"\n";
	//*************************proxy callBack end******************************


	//======================proxy class start============== //客户端调用接口

	CSGStream proxyClassDef;
	CSGStream cppProxyClass;

	
	proxyClassDef<<"class "<<interfaceClassName<<"\n"
					<<"{\n"
					<<"	constructor(){\n"
					<<"	}\n\n";


	CSGStream proxyWriteFunctionDef;

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		CSGStream cppProxyCallWrite;

		//proxy headfile code
		proxyClassDef<<"	"<<functionName<<"_async(session,";

		CSGStream cppProxyFunction;
		cppProxyFunction<<"		let call=new SRMICall();\n"
						<<"		call.rpcId="<<toStr(tmp.rpcId)<<";\n"
						<<"		let __os=new CSerializeStream();\n"
						<<"		let objectBind;\n"
						<<"		CRpcHelper.prepareToCall(session,__os,call,cb,objectBind);\n"
						<<"		__os.setUseBitMark(true);\n";

		bool isFirstOutParam=true;
		bool isFirstParam=true;
		
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];
			if(!param.isOut){
				proxyClassDef<<param.identify<<",";
				if(isBaseType(param.type)){
					cppProxyFunction<<"		__os.write"<<getReadWriteString(param.type)<<"("<<param.identify<<");\n";
				}else if(CSGStlTypeOne==param.stlTypeNum){
					if(isBaseType(param.stlType)){
						cppProxyFunction<<"	__os->write("<<getReadWriteString(param.stlType)<<"Seq("<<param.identify<<");\n";
					}else{
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classWriteFunctionName="__STL_TYPE_ONE__Interface_CCli__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

						cppProxyFunction<<"		this."<<classWriteFunctionName<<"(__os,"<<param.identify<<");\n";

						proxyWriteFunctionDef<<"	"<<classWriteFunctionName<<"(__os,data){\n"
											<<"			let size=data.length;\n"
											<<"			__os.writeSizeInt(size);\n"
											<<"			for(let i=0;i<size;i++){\n"
											<<"				data[i]._csg_write(__os);\n"
											<<"			}\n"
											<<"	}\n\n";
					}						
				}else if(CSGStlTypeDouble==param.stlTypeNum){
					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classWriteFunctionName="__STL_TYPE_DOUBLE__Interface_CCli__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					cppProxyFunction<<"		this."<<classWriteFunctionName<<"(__os,"<<param.identify<<");\n";

					proxyWriteFunctionDef<<"	"<<classWriteFunctionName<<"(__os,data){\n"
										<<"		let size=Object.keys(data).length;\n"
										<<"		__os.writeSizeInt(size);\n"
										<<"		for(let x in data){\n";
					if(isBaseType(param.stlType)){
						proxyWriteFunctionDef<<"			__os.write"+getReadWriteString(param.stlType)+"(x);\n";
					}else{
						proxyWriteFunctionDef<<"			x._csg_write(__os);\n";
					}

					if(isBaseType(param.stlTypeEx)){
						proxyWriteFunctionDef<<"			__os.write"+getReadWriteString(param.stlTypeEx)+"(data[x]);\n";
					}else{
						proxyWriteFunctionDef<<"			data[x]._csg_write(__os);\n";
					}

					proxyWriteFunctionDef<<"		}\n"
											<<"	}\n\n";
				}else{
					checkIsCsglType(param.type,"interface client call function param undefine");
					cppProxyFunction<<"		"<<param.identify<<"._csg_write(__os);\n";
					cppProxyCallWrite<<"	"<<param.identify<<"._csg_write(*__os);\n";
				}
			}
		}

		proxyClassDef<<"cb){\n"
						<<cppProxyFunction.content
						<<"		CRpcHelper.toCall(session,__os,objectBind);\n"
						<<"	}\n\n";
	}

	proxyClassDef<<proxyWriteFunctionDef.content
				<<"}\n";
	
	
	headInterfaceStream<<proxyClassDef.content<<"\n";
	cppInterfaceStream<<cppProxyClass.content;

	//**********************proxy class start end******************************

};




define_line: TOKEN_IFNDEF TOKEN_IFNDEF_FILE TOKEN_IFNDEF_END {
	;
}|TOKEN_IFDEF TOKEN_IFDEF_FILE TOKEN_IFDEF_END {
	;
}|TOKEN_ENDIF {
	;
};







comment: TOKEN_COMMENT_START TOKEN_COMMENT_FILE TOKEN_COMMENT_END {
	outputInfo<<"yacc match comment:"<<BOLDGREEN<<"//"<<$2<<"\r"<<RESET<<"\n";
}|TOKEN_COMMENT_EX_START TOKEN_COMMENT_EX_FILE TOKEN_COMMENT_EX_END {
	outputInfo<<"yacc match commentex:"<<BOLDGREEN<<"/**"<<$2<<"\r"<<RESET<<"\n";
}
;









include: TOKEN_INCLUDE_START TOKEN_INCLUDE_SIGN TOKEN_INCLUDE_FILE TOKEN_INCLUDE_END {
	//headIncludeStream<<"#include \""+$3+"\"\n";
	;
};







enum : TOKEN_ENUM_START TOKEN_ENUM_CONTENT {
	
	std::string enumName=$1;
	int minEnumValue=999999;
	int maxEnumValue=-99999;
	int lastValue=-1;
	std::set<std::string> enumNameSet;

	exportStream<<"export {"<<enumName<<"}\n";
	tipStream<<enumName<<",";
	//generated enum code
	CSGStream enumHeadfileStream;
	enumHeadfileStream<<"if(typeof "+enumName+" == \"undefined\") {\n"
						<<"	var "<<enumName<<"={};\n";
	for(int i=0;i<$2.size();i++){
		CSGEnum tmp=$2[i];
		if(enumNameSet.count(tmp.identify)>0){
			std::cerr<<"error enum value,duplicate enum identify:"<<enumName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		enumNameSet.insert(tmp.identify);

		enumHeadfileStream<<"	"<<enumName<<"."<<tmp.identify;
		if(0!=tmp.value){
			enumHeadfileStream<<" = "<<toStr(tmp.value);
			if(lastValue>=tmp.value){
				std::cerr<<"error enum value,less than last one,enum name:"<<enumName<<",identify:"<<tmp.identify<<std::endl;
				globalError=true;
				assert(false);
			}
			lastValue=tmp.value;
		}else{
			lastValue++;
			std::cerr<<"error enum must define a value in js,enum name:"<<enumName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		enumHeadfileStream<<";\n";
		minEnumValue=minEnumValue<lastValue?minEnumValue:lastValue;
		maxEnumValue=maxEnumValue>lastValue?maxEnumValue:lastValue;
	}
	enumHeadfileStream<<"};\n\n";
	
	headfileContentStream<<enumHeadfileStream.content;
};












struct: TOKEN_ID_START TOKEN_ID_NUM TOKEN_ID_END TOKEN_STRUCT_START TOKEN_STRUCT_NAME TOKEN_STRUCT_CONTENT {
	std::string structName=$5;
	structVec.push_back(structName);
	int idNum=$2;

	exportStream<<"export {"<<structName<<"}\n";
	tipStream<<structName<<",";
	//check
	MapStructId::iterator idIter=mapStructId.find(idNum);
	if(idIter!=mapStructId.end()){
		if(idIter->second.name!=structName||idIter->second.fileName!=nowInputFile){
			std::cout<<"struct id="<<idNum<<" had be used by "<<std::endl;
			globalError=true;
			assert(false);
		}
	}
	MapStructName::iterator nameIter=mapStructName.find(structName);
	if(nameIter!=mapStructName.end()){
		if(nameIter->second.id!=idNum||nameIter->second.fileName!=nowInputFile){
			std::cout<<"struct name="<<structName<<" had be used by "<<std::endl;
			globalError=true;
			assert(false);
		}
	}

	CSGStructKey tmpStructKey;
	tmpStructKey.id=idNum;
	tmpStructKey.name=structName;
	tmpStructKey.fileName=nowInputFile;
	mapStructId[idNum]=tmpStructKey;
	mapStructName[structName]=tmpStructKey;

	CSGStream structHeadfileStream;
	structHeadfileStream<<"class "<<structName<<"{\n";

	//针对vector,map类型的成员变量,额外另生成方法读写
	CSGStream stlStructHeadStream;   //生成额外读写方法的头文件内容
	//CSGStream stlStructCppStream;	//生成额外读写方法的cpp文件内容

	//每个结构体变量成员，都需要有 init,read,write,=,!=,< 这几个方法
	std::string initDef="	";		// _csg_init()函数内容
	std::string readDef;			// _csg_read()函数内容
	std::string writeDef;			// _csg_write()函数内容
	
	std::string operatorEq="	";
	std::string operatorEqEq;
	std::string operatorless;
	
	std::set<std::string> structNameSet; //判断结构体内同名的identify
	structHeadfileStream<<"	//props\n";
	for(int i=0;i<$6.size();i++){
		CSGStruct tmp=$6[i];
		if(structNameSet.count(tmp.identify)>0){
			std::cerr<<"error struct value,duplicate name:"<<structName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		structNameSet.insert(tmp.identify);

		if(isBaseType(tmp.type)){  //基础类型结构体成员变量

			structHeadfileStream<<"	"<<tmp.identify<<";\n";  //类型显示处理  getCsglType

			initDef+="	this."+tmp.identify+"="+getInitTypeString(tmp.type)+";\n	"; //代码初始值根据类型初始化 getInitTypeString
			readDef+="		this."+tmp.identify+"=__is.read"+getReadWriteString(tmp.type)+"();\n";
			writeDef+="		__os.write"+getReadWriteString(tmp.type)+"(this."+tmp.identify+");\n";

		}else if(CSGStlTypeOne==tmp.stlTypeNum){   // vector类结构体成员变量处理
			
			structHeadfileStream<<"	"<<tmp.identify<<";\n";  //变量定义

			initDef+="	this."+tmp.identify+"=new Array();\n	"; 

			if(isBaseType(tmp.stlType)){
				readDef+="		this."+tmp.identify+"=__is.read"+getReadWriteString(tmp.stlType)+"Seq();\n";
				writeDef+="		__os.write"+getReadWriteString(tmp.stlType)+"Seq(this."+tmp.identify+");\n";
			}else{ //vector类自定义结构体成员变量
				// vector<A> ai;
				// tmp.type=vector
				// tmp.stlType=A
				// tmp.identify=ai
				// check

				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl one");


				//函数命名规则= 前缀+结构体名+stl类型+stl内的元素类型+identify
				std::string structReadFuncName="_csg_read__STL_TYPE_ONE__Struct__"+tmp.type+"__"+tmp.stlType+"__"+tmp.identify+"__Serialize";

				readDef+="		this."+tmp.identify+"=this."+structReadFuncName+"(__is);\n";

				std::string structWriteFuncName="_csg_write__STL_TYPE_ONE__Struct__"+tmp.type+"__"+tmp.stlType+"__"+tmp.identify+"__Serialize";
				
				writeDef+="		this."+structWriteFuncName+"(__os,this."+tmp.identify+");\n";


				stlStructHeadStream<<"	"<<structReadFuncName<<"(__is)\n"
									<<"	{\n"
									<<"		let size=__is.readSizeInt();\n"
									<<"		let data=new Array();\n"
									<<"		for(let i=0;i<size;i++)\n"
									<<"		{\n"
									<<"			let val=new "<<tmp.stlType<<"();\n"
									<<"			val._csg_read(__is);\n"
									<<"			data.push_back(val);\n"
									<<"		}\n"
									<<"		return data;\n"
									<<"	}\n\n";

				stlStructHeadStream<<"	"<<structWriteFuncName<<"(__os,data)\n"
									<<"	{\n"
									<<"		let size=data.size;\n"
									<<"		__os.writeSizeInt(size);\n"
									<<"		for(let i=0;i<size;i++)\n"
									<<"		{\n"
									<<"			data[i]._csg_write(__os);\n"
									<<"		}\n"
									<<"	}\n\n";				
			}


		}else if(CSGStlTypeDouble==tmp.stlTypeNum){ //map类结构体成员变量
			// map<A,B> ab;
			// tmp.type=map
			// tmp.stlType=A
			// tmp.stlTypeEx=B
			// tmp.identify=ab

			structHeadfileStream<<"	"<<tmp.identify<<";\n";  //变量定义
			initDef+="	this."+tmp.identify+"=new Map();\n	"; 
			
			//函数命名规则= 前缀+结构体名+stl类型+stlEx类型+stl内的元素类型+identify
			std::string structReadFuncName="_csg_read__STL_TYPE_DOUBLE__Struct__"+tmp.type+"__"+tmp.stlType+"__"+tmp.stlTypeEx+"__"+tmp.identify+"__Serialize";

			readDef+="		this."+tmp.identify+"=this."+structReadFuncName+"(__is);\n";

			std::string structWriteFuncName="_csg_write__STL_TYPE_DOUBLE__Struct__"+tmp.type+"__"+tmp.stlType+"__"+tmp.stlTypeEx+"__"+tmp.identify+"__Serialize";
			writeDef+="		this."+structWriteFuncName+"(__os,this."+tmp.identify+");\n";


			stlStructHeadStream<<"	"<<structReadFuncName<<"(__is){\n"
								<<"		let size=__is.readSizeInt();\n"
								<<"		let data=new Map();\n"
								<<"		for(let i=0;i<size;i++){\n";
			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlType)){
				stlStructHeadStream<<"			let key=__is.read"+getReadWriteString(tmp.stlType)+"();\n";
			}else{
				//check
				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl double first key ");

				stlStructHeadStream<<"			let key=new "<<tmp.stlType<<"();\n"
									<<"			key._csg_read(__is);\n";
			}
			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlTypeEx)){
				stlStructHeadStream<<"			let val=__is.read"+getReadWriteString(tmp.stlTypeEx)+"();\n";
			}else{
				//check
				checkIsCsglType(tmp.stlTypeEx,"unknow csgl struct type from struct stl double second key");

				stlStructHeadStream<<"			let val=new "<<tmp.stlTypeEx<<"();\n"
									<<"			val._csg_read(__is);\n";
			}
			stlStructHeadStream<<"			data[key]=val;\n"
								<<"		}\n"
								<<"		return data;\n"
								<<"	}\n";
			

			stlStructHeadStream<<"	"<<structWriteFuncName<<"(__os,data)\n"
								<<"	{\n"
								<<"		let size=Object.keys(data).length;\n"
								<<"		__os.writeSizeInt(size);\n"
								<<"		for(let x in data)\n"
								<<"		{\n";

			//根据类型,使用不同的写方法
			if(isBaseType(tmp.stlType)){
				stlStructHeadStream<<"			__os.write"<<getReadWriteString(tmp.stlType)<<"(x);\n";
			}else{
				//check
				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl double first key ");

				stlStructHeadStream<<"			x._csg_write(__os);\n";
			}
			//根据类型,使用不同的写方法
			if(isBaseType(tmp.stlTypeEx)){
				stlStructHeadStream<<"			__os.write"<<getReadWriteString(tmp.stlTypeEx)<<"(data[x]);\n";
			}else{
				//check
				checkIsCsglType(tmp.stlTypeEx,"unknow csgl struct type from struct stl double second key");

				stlStructHeadStream<<"			data[x]._csg_write(__os);\n";;
			}
			stlStructHeadStream<<"		}\n"
								<<"	}\n";
		}
		else{ //自定义结构体成员变量
			checkIsCsglType(tmp.type,"unknow csgl struct type");

			structHeadfileStream<<"	"<<tmp.identify<<";\n";  //类型显示处理  getCsglType

			initDef+="	this."+tmp.identify+"=new "+tmp.type+"();\n	"; //代码初始值根据类型初始化 getInitTypeString

			readDef+="		this."+tmp.identify+"._csg_read(__is);\n";
			writeDef+="		this."+tmp.identify+"._csg_write(__os);\n";

		};

		//判断==的方法都是一样的
		operatorEq+=tmp.identify+" = "+"__other."+tmp.identify+";\n	";
		operatorEqEq+="	if("+tmp.identify+" !="+" __other."+tmp.identify+")\n"
						+"	{\n"
						+"		return true;\n"
						+"	}\n";
		operatorless+="	if("+tmp.identify+" <"+" __other."+tmp.identify+")\n"
						+"	{\n"
						+"		return true;\n"
						+"	}\n"
						+"	else if(__other."+tmp.identify+"<"+tmp.identify+")\n"
						+"	{\n"
						+"		return false;\n"
						+"	}\n";
	}
	
	structHeadfileStream<<"\n";
	structHeadfileStream<<"	constructor(){\n"
						<<"		this._csg_init();\n"
						<<"	}\n";

	structHeadfileStream<<"	_csg_init(){\n"
						<<initDef
						<<"}\n";

	structHeadfileStream<<"	_csg_read(__is){\n"
						<<readDef
						<<"	}\n";

	structHeadfileStream<<"	_csg_write(__os){\n"
						<<writeDef
						<<"	}\n";
	structHeadfileStream<<"	getType(){\n"
						<<"		return "<<toStr(idNum)<<";\n"
						<<"	}\n"
						<<"	clone(){\n"
						<<"		return new "<<structName<<"();\n"
						<<"	}\n"
						<<stlStructHeadStream.content
						<<"}\n\n";
						
	headfileContentStream<<structHeadfileStream.content;
};


%%


std::string toStr(int i){
	std::stringstream ss;
	ss<<i;
	return ss.str();

};


void csgInfo(std::string type,std::string s){
	bool defineType=false;
	if(type=="ifndef"){
		//defineType=true ;
	}		
	
	bool unknowB=false;
	if("table"==type)
		unknowB=true;
	if("newline"==type)
		unknowB=true;
	if("blank"==type)
		unknowB=true;
	if("unknow"==type)
		unknowB=true;

	if(unknowB){
		//return ;
	
	}
	if(defineType){
		//return ;
	}
	
	//outputInfo<<YELLOW<<"csgl:"<<type<<","<<BOLDYELLOW<<"["<<s<<"]"<<RESET<<RESET<<"\n";
	std::cout<<YELLOW<<"csgl:"<<type<<","<<BOLDYELLOW<<"["<<s<<"]"<<RESET<<RESET<<"\n";
}


void csgOutputHead(){
	ofs<<csgDefStr<<"\n";
	ofs<<headDefStream.content<<"\n";
	ofs<<includeCsgFile<<"\n";
	
}

void csgOutputEnd(std::string fileName){

	ofs<<headInterfaceStream.content<<"\n";
	ofs<<"\n\n"<<exportStream.content<<"\n";
	ofs<<"\n\n"<<tipStream.content<<"\n";
}



void yyerror(const char* s){
	std::cerr<<"\033[31m"<<"get error:["<<s<<"]\033[0m"<<",line "<<yylineno<<std::endl;
	assert(false);
}

void csgReadJson(Json::Value& jsonInfo){
	
	for(Json::Value::iterator it=jsonInfo["struct"].begin();it!=jsonInfo["struct"].end();++it){
		CSGStructKey key;
		key.id=(*it)["id"].asInt();
		key.name=(*it)["name"].asString();
		key.fileName=(*it)["file"].asString();
		mapStructId[key.id]=key;
		mapStructName[key.name]=key;
	}
	for(Json::Value::iterator it=jsonInfo["interface"].begin();it!=jsonInfo["interface"].end();++it){
		CSGInterfaceKey key;
		key.rpcId=(*it)["rpcId"].asInt();
		key.interface=(*it)["name"].asString();
		key.interfaceFile=(*it)["file"].asString();
		mapInterfaceId[key.rpcId]=key;
		mapInterfaceFileName[key.interfaceFile][key.interface]=key;
	}
}


void rewriteJson(){
	jsonofs.open(jsonfile);
	if(!jsonofs.is_open()){
		std::cerr<<RED<<"can't open json_file by writer"<<jsonfile<<RESET<<std::endl;
		return ;
	}
	Json::Value rewriteJs;
	for(MapStructId::iterator it=mapStructId.begin();it!=mapStructId.end();++it){
		Json::Value tmpJs;
		tmpJs["id"]=it->second.id;
		tmpJs["name"]=it->second.name;
		tmpJs["file"]=it->second.fileName;
		rewriteJs["struct"].append(tmpJs);
	}
	for(MapInterfaceId::iterator it=mapInterfaceId.begin();it!=mapInterfaceId.end();++it){	
		Json::Value tmpJs;
		tmpJs["rpcId"]=it->second.rpcId;
		tmpJs["name"]=it->second.interface;
		tmpJs["file"]=it->second.interfaceFile;
		rewriteJs["interface"].append(tmpJs);
	}

	std::string rewriteStr=rewriteJs.toStyledString();
	jsonofs<<rewriteStr;
	jsonofs.flush();
	jsonofs.close();
	//std::cout<<"rewrite js="<<rewriteStr<<std::endl;
};


int main(int argc,char **argv){
	
	//get csl file
	if(argc<4){
		std::cerr<<RED<<"no enough param,first is csgl file ,next is outfile dir"<<RESET<<std::endl;
	}
	jsonfs.open(jsonfile);
	if(!jsonfs.is_open()){
		std::cerr<<RED<<"can't open json_file "<<jsonfile<<RESET<<std::endl;
		return 1;
	}
	std::string jsonStr,lineStr;
	Json::Value jsonInfo;
	while(getline(jsonfs,lineStr)){
		jsonStr.append(lineStr);
	}
	jsonfs.close();
	Json::Reader reader;
	if ( false == reader.parse(jsonStr ,jsonInfo) )
	{
		std::cerr<<RED<<"can't parse json_file "<<jsonfile<<RESET<<std::endl;
		return 1;
	}
	csgReadJson(jsonInfo);

	std::string inputfile(*(argv+3));
	nowInputFile=inputfile;
	std::cout<<"now inputfile is "<<nowInputFile<<std::endl;
	std::string inputfileName=inputfile+".csgl";
	std::string inputDir(*(argv+1));
	std::string outputDir(*(argv+2));
	std::string inputfileCsg=inputDir+inputfileName;
	std::string outputHeadFileName=outputDir+inputfile+".js";

	std::cout<<"input file is "<<YELLOW<<inputfileCsg<<RESET<<std::endl;
	std::cout<<"output dir is "<<YELLOW<<outputDir<<RESET<<std::endl;
	std::cout<<"output jsfile is "<<GREEN<<outputHeadFileName<<RESET<<std::endl;

	tipStream<<"//import {";
	FILE *fp=fopen(inputfileCsg.c_str(),"r");
	if(NULL==fp){
		std::cerr<<RED<<"can't open file "<<inputfileCsg<<RESET<<std::endl;
		return 0;
	}
	
	ofs.open(outputHeadFileName);


	if(!ofs.is_open()){
		std::cerr<<RED<<"can't open file "<<outputHeadFileName<<RESET<<std::endl;
		return 0;
	}

	yyin=fp;
	yyparse();
	fclose(fp);

	if(globalError){
		assert(false);
		return 1;
	}
	rewriteJson();

	std::cout<<GREEN<<"start generated head file "<<inputfileName<<RESET<<std::endl;
	//generated headfile
	csgOutputHead();
	ofs<<headfileContentStream.content<<std::endl;


	csgOutputEnd(inputfile);

	std::cout<<BOLDGREEN<<"build csgl file success!"<<RESET<<std::endl;
	
	ofs.close();
	return 0;
}



