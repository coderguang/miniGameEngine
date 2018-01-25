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

ofstream ofs;
ofstream ofscpp;

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

	//======================Server callBack start============== 服务器回调对象定义及实现
	CSGStream callBackDef;
	CSGStream cppCallBack;

	
	callBackDef<<"namespace "<<mNamespace<<"\n"
				<<"{\n";

	std::set<std::string> interfaceNameSet;

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;
		//check
		if(interfaceNameSet.count(functionName)>0){
			std::cerr<<"error interface function,duplicate function file:"<<interfaceName<<",identify:"<<functionName<<std::endl;
			globalError=true;
			assert(false);
		}
		interfaceNameSet.insert(functionName);
		//check
		MapInterfaceId::iterator rpcIdIter=mapInterfaceId.find(tmp.rpcId);
		if(rpcIdIter!=mapInterfaceId.end()){
			if(rpcIdIter->second.interfaceFile!=interfaceClassName||rpcIdIter->second.interface!=functionName){
				std::cout<<"rpcid:"<<tmp.rpcId<<" had already be use!"<<std::endl;
				globalError=true;
				assert(false);
			}
		}
		MapInterfaceFileName::iterator fileIter=mapInterfaceFileName.find(interfaceClassName);
		if(fileIter!=mapInterfaceFileName.end()){
			MapInterfaceName::iterator nameIt=fileIter->second.find(functionName);
			if(nameIt!=fileIter->second.end()){
				if(nameIt->second.rpcId!=tmp.rpcId){
				std::cout<<"interface functionName:"<<functionName<<" had already be use!"<<std::endl;
				globalError=true;
				assert(false);
				}
			}
		}


		CSGInterfaceKey tmpIkey;
		tmpIkey.rpcId=tmp.rpcId;
		tmpIkey.interface=functionName;
		tmpIkey.interfaceFile=interfaceClassName;
		mapInterfaceId[tmp.rpcId]=tmpIkey;
		mapInterfaceFileName[interfaceClassName][functionName]=tmpIkey;

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		callBackDef<<"	class "<<srvCB<<":public virtual CRMIObjectCallBackObject\n"
								<<"	{\n"
								<<"	public:\n"
								<<"		virtual void response(";
		cppCallBack<<"void Message::"<<srvCB<<"::response(";

		CSGStream cppCallBackWrite;

		bool isFirstOutParam=true;
		bool isFirstParam=true;
		CSGStream callBackStlWriteDef;
		CSGStream cppCallStlWriteBack;


		std::set<std::string> paramNameSet;
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];
			bool isOut=param.isOut;
			std::string type=param.type;
			std::string identify=param.identify;
			//检测重复的参数
			if(paramNameSet.count(identify)>0){
				std::cerr<<"error interface function,duplicate param file:"<<interfaceName<<",identify:"<<functionName<<",param:"<<identify<<std::endl;
				globalError=true;
				assert(false);
			}
			paramNameSet.insert(identify);

			CSGStream tmpCallBack;

			if(isOut){
				if(!isFirstOutParam) //第一个回调参数前不需要加逗号
				{
					tmpCallBack<<",";		
				}
				if(isBaseType(param.type)){ //返回值类型参数为基础类型
					tmpCallBack<<"const "<<getCsglType(param.type)<<" "<<param.identify;
					cppCallBackWrite<<"	__os->write("<<param.identify<<");\n";
				}else if(CSGStlTypeOne==param.stlTypeNum){ //返回值类型参数为vector
					if(!isBaseType(param.stlType)){
						 //元素类型为自定义结构类型
						checkIsCsglType(param.stlType,"out param stl one is not a define struct");

						//额外的写方法(回调对象只需要写方法),命名规则=前缀+接口文件名+接口名+类型+元素类型+identify
						std::string classWriteName="__STL_TYPE_ONE__Interface__CSrv__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;

						callBackStlWriteDef<<"	class "<<classWriteName<<"{};\n"
											<<"	void __write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classWriteName<<");\n\n";
						cppCallStlWriteBack<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classWriteName<<")\n"
											<<"{\n"
											<<"	int size=__data.size();\n"
											<<"	__os.writeSize(size);\n"
											<<"	for(int i=0;i<size;i++)\n"
											<<"	{\n"
											<<"		__data[i]._csg_write(__os);\n"
											<<"	}\n"
											<<"};\n\n";
						cppCallBackWrite<<"	Message::__write(*__os,"<<param.identify<<","<<classWriteName<<"());\n";
					}else{
						cppCallBackWrite<<"	__os->write("<<param.identify<<");\n";
					}
					tmpCallBack<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& "<<param.identify;

				}else if(CSGStlTypeDouble==param.stlTypeNum){
					if(!isBaseType(param.stlType)){
						 //元素类型为自定义结构类型
						checkIsCsglType(param.stlType,"out param stl double left key is not a define struct");
					}
					if(!isBaseType(param.stlTypeEx)){
						 //元素类型为自定义结构类型
						checkIsCsglType(param.stlTypeEx,"out param stl double right key is not a define struct");
					}

					//额外的写方法(回调对象只需要写方法),命名规则=前缀+接口文件名+接口名+类型+元素类型+identify
					std::string classWriteName="__STL_TYPE_ONE__Interface__CSrv__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;
					callBackStlWriteDef<<"	class "<<classWriteName<<"{};\n"
											<<"	void __write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classWriteName<<");\n\n";
					cppCallStlWriteBack<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classWriteName<<")\n"
										<<"{\n"
										<<"	int size=__data.size();\n"
										<<"	__os.writeSize(size);\n"
										<<"	for(std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">::const_iterator it=__data.cbegin();it!=__data.cend();++it)\n"
										<<"	{\n";
					if(!isBaseType(param.stlType)){
						 //元素类型为自定义结构类型
						cppCallStlWriteBack<<"		it->first._csg_write(__os);\n";
					}else{
						cppCallStlWriteBack<<"		__os.write(it->first);\n";
					}
					if(!isBaseType(param.stlTypeEx)){
						 //元素类型为自定义结构类型
						cppCallStlWriteBack<<"		it->second._csg_write(__os);\n";
					}else{
						cppCallStlWriteBack<<"		__os.write(it->second);\n";
					}
					
					cppCallStlWriteBack<<"	}\n"
										<<"};\n\n";

					cppCallBackWrite<<"	Message::__write(*__os,"<<param.identify<<","<<classWriteName<<"());\n";


					tmpCallBack<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& "<<param.identify;
					
				}else{ //自定义结构体返回值

					checkIsCsglType(param.type,"interface unknow csgl struct type");
					tmpCallBack<<"const "<<getCsglType(param.type)<<"& "<<param.identify;

					cppCallBackWrite<<"	"<<param.identify<<"._csg_write(*__os);\n";
				}
				isFirstOutParam=false;
			}

			callBackDef<<tmpCallBack.content;
			cppCallBack<<tmpCallBack.content;
		}



		callBackDef<<");\n"
					<<"	};\n"
					<<"	typedef CSmartPointShare<"<<srvCB<<"> "<<srvCBPtr<<";\n\n";
		callBackDef<<callBackStlWriteDef.content;

		cppCallBack<<")\n"
					<<"{\n"
					<<"	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());\n"
					<<"	SRMIReturn rmiReturn;\n"
					<<"	rmiReturn.dispatchStatus = ERMIDispatchResultOk;\n"
					<<"	rmiReturn.messageId = _rmiCall.messageId;\n\n"
					<<"	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);\n\n"
					<<"	__os->setUseBitMark(true);\n\n"
					<<cppCallBackWrite.content<<"\n"
					<<"	CRpcHelper::toReturn(_session,__os);\n\n"
					<<"}\n\n";	
		cppCallBack<<cppCallStlWriteBack.content;

	}

	callBackDef<<"}\n\n"<<"\n";
	
	headInterfaceStream<<callBackDef.content<<"\n";

	cppInterfaceStream<<cppCallBack.content;

	//*************************Server callBack end******************************

	//======================Server interface class struct and onCall Def start============== 服务器onCall函数+ rpc注册(cpp部分)

	CSGStream cppClassStruct;
	CSGStream cppClassOncall;

	
	cppClassStruct<<"Message::"<<interfaceClassName<<"::"<<interfaceClassName<<"()\n"
					<<"{\n"
					<<"	SRMIInfo rmiInfo;\n"
					<<"	rmiInfo.identify=\""<<interfaceClassName<<"\";\n\n";
	cppClassOncall<<"csg::ERMIDispatchResult Message::"<<interfaceClassName<<"::__onCall(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)\n"
					<<"{\n"
					<<"	switch(rmiCall.rpcId)\n"
					<<"	{\n";

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;
		outputInfo<<"functionName:"<<tmp.funcName<<",rpcid:"<<toStr(tmp.rpcId)<<"\n";

		//class def
		std::string srvCB=srvCBprefix+functionName;
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";
		CSGStream cppProxyCallBackRead;
		CSGStream cppProxyCallBackParam;
		CSGStream cppProxyReturnParam;

		CSGStream cppProxyFunction;
		CSGStream cppProxyCallWrite;
	

		cppClassStruct<<"	rmiInfo.operation=\""<<functionName<<"\";\n"
						<<"	addRMIInfo("<<toStr(tmp.rpcId)<<",rmiInfo);\n"
						<<"	addRpcId("<<toStr(tmp.rpcId)<<");\n\n";
		cppClassOncall<<"		case "<<toStr(tmp.rpcId)<<":\n"
						<<"		{\n"
						<<"			return __"<<functionName<<"_async(session,rmiCall,__is);\n"
						<<"		}\n"
						<<"		break;\n";
	}
	cppClassStruct<<"}\n\n";	
	cppClassOncall<<"		default:\n"
					<<"		break;\n"
					<<"	}\n\n"
					<<"	return ERMIDispatchObjectNotExist;\n\n"
					<<"}\n\n";
		

	cppInterfaceStream<<cppClassStruct.content;
	cppInterfaceStream<<cppClassOncall.content;

	//*********************Server interface class struct  and onCall Def end*************

	//======================Server interface class start============== 服务器onCall函数+ rpc注册+rpc分发

	CSGStream classDef;
	CSGStream cppClassInterface;

	CSGStream functionDefStlWrite; //额外的读函数
	CSGStream functionCppStlWrite; //额外的读函数
	
	classDef<<"namespace "<<mNamespace<<"\n"
				<<"{\n"
				<<"	class "<<interfaceClassName<<":public virtual CRMIObject\n"
				<<"	{\n"
				<<"	public:\n"
				<<"		"<<interfaceClassName<<"();\n\n"
				<<"		virtual ERMIDispatchResult __onCall(const CSessionPtr&,const SRMICall&,CSerializeStream&);\n\n";

	for(int i=0;i<interfaceList.size();i++){
		CSGInterface tmp=interfaceList[i];
		std::string functionName=tmp.funcName;

		//class def
		std::string srvCB=srvCBprefix+functionName;  
		std::string srvCBPtr=srvCB+"_Ptr";
		std::string cliCB=cliCBprefix+functionName;
		std::string cliCBPtr=cliCB+"_Ptr";

		CSGStream functionDefStream;
		CSGStream cppClassProxyParam;


		functionDefStream<<"		ERMIDispatchResult __"<<functionName<<"_async("<<"const CSessionPtr&,const SRMICall&,CSerializeStream&);\n\n";
		functionDefStream<<"		virtual void "<<functionName<<"_async(const CSessionPtr& ,"<<mNamespace<<"::"<<srvCBPtr<<"&";

		cppClassInterface<<"csg::ERMIDispatchResult Message::"<<interfaceName<<"::__"<<functionName<<"_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)\n"
						<<"{\n";

		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(!param.isOut){
				if(isBaseType(param.type)){
					functionDefStream<<","<<getCsglType(param.type);
					cppClassInterface<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
							<<"	__is.read("<<param.identify<<");\n";

				}else if(CSGStlTypeOne==param.stlTypeNum){

					functionDefStream<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&";

					cppClassInterface<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<"> "<<param.identify<<";\n";

					if(isBaseType(param.stlType)){
						cppClassInterface<<"	__is.read("<<param.identify<<");\n";

					}else{ //元素类型为自定义结构
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classWriteFunctionName="__STL_TYPE_ONE__Interface_CSrv__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;
						
						functionDefStlWrite<<"	class "<<classWriteFunctionName<<"{};\n"
											<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classWriteFunctionName<<");\n\n";

						functionCppStlWrite<<"void Message::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classWriteFunctionName<<")\n"
											<<"{\n"
											<<"	int size=0;\n"
											<<"	__is.readSize(size);\n"
											<<"	for(int i=0;i<size;i++)\n"
											<<"	{\n"
											<<"		"<<getCsglType(param.stlType)<<" val;\n"
											<<"		val._csg_read(__is);\n"
											<<"		__data.push_back(val);\n"
											<<"	}\n"
											<<"}\n\n";
						cppClassInterface<<"	Message::__read(__is,"<<param.identify<<","<<classWriteFunctionName<<"());\n";
					}
				}else if(CSGStlTypeDouble==param.stlTypeNum){
					functionDefStream<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&";
					cppClassInterface<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<"> "<<param.identify<<";\n";

					//map类均为自定义读函数
					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classWriteFunctionName="__STL_TYPE_DOUBLE__Interface_CSrv__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					functionDefStlWrite<<"	class "<<classWriteFunctionName<<"{};\n"
											<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classWriteFunctionName<<");\n\n";

					functionCppStlWrite<<"void Message::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classWriteFunctionName<<")\n"
										<<"{\n"
										<<"	int size=0;\n"
										<<"	__is.readSize(size);\n"
										<<"	for(int i=0;i<size;i++)\n"
										<<"	{\n"
										<<"		"<<getCsglType(param.stlType)<<" key;\n";
					if(isBaseType(param.stlType)){
						functionCppStlWrite<<"		__is.read(key);\n";
					}else{
						functionCppStlWrite<<"		key._csg_read(__is);\n";
					}

					functionCppStlWrite<<"		"<<getCsglType(param.stlTypeEx)<<" val;\n";

					if(isBaseType(param.stlTypeEx)){
						functionCppStlWrite<<"		__is.read(val);\n";
					}else{
						functionCppStlWrite<<"		val._csg_read(__is);\n";
					}
					functionCppStlWrite<<"		__data[key]=val;\n"
										<<"	}\n"
										<<"}\n\n";

					cppClassInterface<<"	Message::__read(__is,"<<param.identify<<","<<classWriteFunctionName<<"());\n";

				}else{
					checkIsCsglType(param.type,"interface param error");
					functionDefStream<<",const "<<getCsglType(param.type)<<" &";
					cppClassInterface<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n";
					cppClassInterface<<"	"<<param.identify<<"._csg_read(__is);\n";
				}

				cppClassProxyParam<<","<<param.identify;
			}
		}
		functionDefStream<<")=0;\n\n";

		classDef<<functionDefStream.content;


		cppClassInterface<<"	"<<srvCBPtr<<" cb=new "<<srvCB<<"();\n"
						<<"	cb->setSession(session,rmiCall);\n"
						<<"	"<<functionName<<"_async(session,cb"<<cppClassProxyParam.content<<");\n\n"
						<<"	return ERMIDispatchResultOk;\n\n"
						<<"}\n\n";
	}

	classDef<<"	};\n\n";
	classDef<<functionDefStlWrite.content;
	classDef<<"}\n";
	
	headInterfaceStream<<classDef.content<<"\n";


	cppInterfaceStream<<cppClassInterface.content;
	cppInterfaceStream<<functionCppStlWrite.content;


	//*************************Server interface class end******************************

	// 客户端部分使用代码
	//======================proxy callBack start============== //客户端回调对象

	CSGStream proxyCallBackDef;
	CSGStream cppProxyCallBack;

	
	proxyCallBackDef<<"namespace "<<proxyNamespace<<"\n"
					<<"{\n"
					<<"	using namespace Message;\n\n";

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

		proxyCallBackDef<<"	class "<<cliCB<<":public virtual CRMIProxyCallBackObject\n"
						<<"	{\n"
						<<"	public:\n"
						<<"		virtual void response(";
		cppProxyCallBack<<"void csg_proxy::"<<cliCB<<"::__response(CSerializeStream& __is)\n"
						<<"{\n";


		bool isFirstOutParam=true;
		bool isFirstParam=true;
		
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(param.isOut){
				if(!isFirstOutParam){
					proxyCallBackDef<<",";
					cppProxyReturnParam<<",";				
				}

				if(isBaseType(param.type)){
					proxyCallBackDef<<"const "<<getCsglType(param.type);

					cppProxyCallBackParam<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
										<<"	__is.read("<<param.identify<<");\n";

				}else if(CSGStlTypeOne==param.stlTypeNum){
					proxyCallBackDef<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& ";
					cppProxyCallBackParam<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<"> "<<param.identify<<";\n";
					if(isBaseType(param.stlType)){
						cppProxyCallBackParam<<"	__is.read("<<param.identify<<");\n";
					}else{
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classReadFunctionName="__STL_TYPE_ONE__Interface_CCli__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.identify;

						functionDefStlRead<<"	class "<<classReadFunctionName<<" {};\n"
											<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classReadFunctionName<<");\n\n";

						functionCppStlRead<<"void "<<proxyNamespace<<"::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classReadFunctionName<<")\n"
											<<"{\n"
											<<"	int size=0;\n"
											<<"	__is.readSize(size);\n"
											<<"	for(int i=0;i<size;i++)\n"
											<<"	{\n"
											<<"		"<<getCsglType(param.stlType)<<" val;\n"
											<<"		val._csg_read(__is);\n"
											<<"		__data.push_back(val);\n"
											<<"	}\n"
											<<"}\n\n";

						cppProxyCallBackParam<<"	"<<proxyNamespace<<"::__read(__is,"<<param.identify<<","<<classReadFunctionName<<"());\n";
					}


					
				}else if(CSGStlTypeDouble==param.stlTypeNum){
					proxyCallBackDef<<"const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)
<<">&";
					cppProxyCallBackParam<<"	std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<"> "<<param.identify<<";\n";

					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classReadFunctionName="__STL_TYPE_DOUBLE__Interface_CCli__Read__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					functionDefStlRead<<"	class "<<classReadFunctionName<<" {};\n"
										<<"	void __read(CSerializeStream&,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classReadFunctionName<<");\n\n";

					functionCppStlRead<<"void "<<proxyNamespace<<"::__read(CSerializeStream& __is,std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classReadFunctionName<<")\n"
										<<"{\n"
										<<"	int size=0;\n"
										<<"	__is.readSize(size);\n"
										<<"	for(int i=0;i<size;i++)\n"
										<<"	{\n"
										<<"		"<<getCsglType(param.stlType)<<" key;\n";
					
					if(isBaseType(param.stlType)){
						functionCppStlRead<<"		__is.read(key);\n";
					}else{
						functionCppStlRead<<"		key._csg_read(__is);\n";
					}
					functionCppStlRead<<"		"<<getCsglType(param.stlTypeEx)<<" val;\n";

					if(isBaseType(param.stlTypeEx)){
						functionCppStlRead<<"		__is.read(val);\n";
					}else{
						functionCppStlRead<<"		val._csg_read(__is);\n";
					}
					functionCppStlRead<<"		__data[key]=val;\n"
										<<"	}\n"
										<<"}\n\n";

					cppProxyCallBackParam<<"	"<<proxyNamespace<<"::__read(__is,"<<param.identify<<","<<classReadFunctionName<<"());\n";


				}else{ //自定义结构体
					checkIsCsglType(param.type,"client respond not define struct");
					proxyCallBackDef<<"const "<<getCsglType(param.type)<<"&";

					cppProxyCallBackParam<<"	"<<getCsglType(param.type)<<" "<<param.identify<<";\n"
										<<"	"<<param.identify<<"._csg_read(__is);\n";

				}
				isFirstOutParam=false;
				cppProxyReturnParam<<param.identify;
			}
		}
		proxyCallBackDef<<")=0;\n"
						<<"	protected:\n"
						<<"		virtual void __response(CSerializeStream& __is);\n"
						<<"	};\n"
						<<"	typedef CSmartPointShare<"<<cliCB<<"> "<<cliCBPtr<<";\n\n";

		proxyCallBackDef<<functionDefStlRead.content;

		cppProxyCallBack<<cppProxyCallBackParam.content
						<<"\n"
						<<"	response("<<cppProxyReturnParam.content<<");\n\n"
						<<"}\n\n";
		cppProxyCallBack<<functionCppStlRead.content;

	}

	proxyCallBackDef<<"}\n";
	
	headInterfaceStream<<proxyCallBackDef.content<<"\n";
	cppInterfaceStream<<cppProxyCallBack.content;
	//*************************proxy callBack end******************************


	//======================proxy class start============== //客户端调用接口

	CSGStream proxyClassDef;
	CSGStream cppProxyClass;
	CSGStream cppProxyFunction;

	
	proxyClassDef<<"namespace "<<proxyNamespace<<"\n"
					<<"{\n"
					<<"	using namespace Message;\n\n"
					<<"	class "<<interfaceClassName<<":public virtual CRMIProxyObject\n"
					<<"	{\n"
					<<"	public:\n"
					<<"		"<<interfaceClassName<<"();\n";
	cppProxyClass<<"csg_proxy::"<<interfaceClassName<<"::"<<interfaceClassName<<"()\n"
					<<"{\n"
					<<"}\n\n";

	CSGStream proxyWriteFunctionDef;
	CSGStream proxyWriteFunctionCpp;

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
		proxyClassDef<<"		void "<<functionName<<"_async(const CSessionPtr&,const "<<cliCBPtr<<"&";
		cppProxyFunction<<"void csg_proxy::"<<interfaceName<<"::"<<functionName<<"_async(const CSessionPtr& session,const "<<cliCBPtr<<"& cb";

		bool isFirstOutParam=true;
		bool isFirstParam=true;
		
		for(int j=0;j<tmp.paramList.size();j++){
			CSGInterfaceParam param=tmp.paramList[j];

			if(!param.isOut){
				if(isBaseType(param.type)){
					proxyClassDef<<",const "<<getCsglType(param.type);
					cppProxyFunction<<",const "<<getCsglType(param.type)<<" "<<param.identify;
					cppProxyCallWrite<<"	__os->write("<<param.identify<<");\n";
				}else if(CSGStlTypeOne==param.stlTypeNum){
					proxyClassDef<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&";
					cppProxyFunction<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& "<<param.identify;

					if(isBaseType(param.stlType)){
						cppProxyCallWrite<<"	__os->write("<<param.identify<<");\n";
					}else{
						//命名规则=前缀+接口文件+接口名+类型+元素+identify
						std::string classWriteFunctionName="__STL_TYPE_ONE__Interface_CCli__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

						proxyWriteFunctionDef<<"	class "<<classWriteFunctionName<<" {};\n"
												<<"	void __write(CSerializeStream&,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">&,"<<classWriteFunctionName<<");\n\n";
						proxyWriteFunctionCpp<<"void csg_proxy::__write(CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<">& __data,"<<classWriteFunctionName<<")\n"
												<<"{\n"
												<<"	int size=__data.size();\n"
												<<"	__os.writeSize(size);\n"
												<<"	for(int i=0;i<size;i++)\n"
												<<"	{\n"
												<<"		__data[i]._csg_write(__os);\n"
												<<"	}\n"
												<<"}\n\n";

						cppProxyCallWrite<<"	csg_proxy::__write(*__os,"<<param.identify<<","<<classWriteFunctionName<<"());\n";
					}						


				}else if(CSGStlTypeDouble==param.stlTypeNum){
					proxyClassDef<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&";
					cppProxyFunction<<",const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& "<<param.identify;

					//命名规则=前缀+接口文件+接口名+类型+元素1+元素2+identify
					std::string classWriteFunctionName="__STL_TYPE_DOUBLE__Interface_CCli__Write__"+interfaceName+"__"+functionName+"__"+param.type+"__"+param.stlType+"__"+param.stlTypeEx+"__"+param.identify;

					proxyWriteFunctionDef<<"	class "<<classWriteFunctionName<<" {};\n"
												<<"	void __write(CSerializeStream&,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">&,"<<classWriteFunctionName<<");\n\n";
					proxyWriteFunctionCpp<<"void csg_proxy::__write(CSerializeStream& __os,const std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">& __data,"<<classWriteFunctionName<<")\n"
										<<"{\n"
										<<"	int size=__data.size();\n"
										<<"	__os.writeSize(size);\n"
										<<"	for(std::"<<param.type<<"<"<<getCsglType(param.stlType)<<","<<getCsglType(param.stlTypeEx)<<">::const_iterator it=__data.cbegin();it!=__data.end();++it)\n"
										<<"	{\n";
					if(isBaseType(param.stlType)){
						proxyWriteFunctionCpp<<"		__os.write(it->first);\n";
					}else{
						proxyWriteFunctionCpp<<"		it->first._csg_write(__os);\n";
					}

					if(isBaseType(param.stlTypeEx)){
						proxyWriteFunctionCpp<<"		__os.write(it->second);\n";
					}else{
						proxyWriteFunctionCpp<<"		it->second._csg_write(__os);\n";
					}

					proxyWriteFunctionCpp<<"	}\n"
											<<"}\n\n";


					cppProxyCallWrite<<"	csg_proxy::__write(*__os,"<<param.identify<<","<<classWriteFunctionName<<"());\n";
				}else{
					checkIsCsglType(param.type,"interface client call function param undefine");
					proxyClassDef<<",const "<<getCsglType(param.type)<<"&";
					cppProxyFunction<<",const "<<getCsglType(param.type)<<"& "<<param.identify;
					cppProxyCallWrite<<"	"<<param.identify<<"._csg_write(*__os);\n";
				}
			}
		}
		proxyClassDef<<");\n\n";
		cppProxyFunction<<")\n"
						<<"{\n"
						<<"	csg::SRMICall call;\n"
						<<"	call.rpcId="<<toStr(tmp.rpcId)<<";\n\n"
						<<"	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());\n"
						<<"	CRMIObjectBindPtr objectBind=NULL;\n"
						<<"	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);\n\n"
						<<"	__os->setUseBitMark(true);\n"
						<<cppProxyCallWrite.content<<"\n"
						<<"	CRpcHelper::toCall(session,__os,objectBind"<<");\n\n"
						<<"}\n\n";
	}

	proxyClassDef<<"	};\n\n"
				<<proxyWriteFunctionDef.content
				<<"}\n";
	
	
	headInterfaceStream<<proxyClassDef.content<<"\n";
	cppInterfaceStream<<cppProxyClass.content;
	cppInterfaceStream<<cppProxyFunction.content;
	cppInterfaceStream<<proxyWriteFunctionCpp.content;

	//**********************proxy class start end******************************

};




define_line: TOKEN_IFNDEF TOKEN_IFNDEF_FILE TOKEN_IFNDEF_END {
	headDefStream<<"#ifndef "<<$2<<"\n";
}|TOKEN_IFDEF TOKEN_IFDEF_FILE TOKEN_IFDEF_END {
	headDefStream<<"#define "<<$2<<"\n";
}|TOKEN_ENDIF {
	endDefStream<<$1<<"\n";
};







comment: TOKEN_COMMENT_START TOKEN_COMMENT_FILE TOKEN_COMMENT_END {
	outputInfo<<"yacc match comment:"<<BOLDGREEN<<"//"<<$2<<"\r"<<RESET<<"\n";
}|TOKEN_COMMENT_EX_START TOKEN_COMMENT_EX_FILE TOKEN_COMMENT_EX_END {
	outputInfo<<"yacc match commentex:"<<BOLDGREEN<<"/**"<<$2<<"\r"<<RESET<<"\n";
}
;









include: TOKEN_INCLUDE_START TOKEN_INCLUDE_SIGN TOKEN_INCLUDE_FILE TOKEN_INCLUDE_END {
	headIncludeStream<<"#include \""+$3+"\"\n";
};







enum : TOKEN_ENUM_START TOKEN_ENUM_CONTENT {
	
	std::string enumName=$1;
	int minEnumValue=999999;
	int maxEnumValue=-99999;
	int lastValue=-1;
	std::set<std::string> enumNameSet;
	//generated enum code
	CSGStream enumHeadfileStream;
	enumHeadfileStream<<"	enum "+enumName+" {\n";
	for(int i=0;i<$2.size();i++){
		CSGEnum tmp=$2[i];
		if(enumNameSet.count(tmp.identify)>0){
			std::cerr<<"error enum value,duplicate enum identify:"<<enumName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		enumNameSet.insert(tmp.identify);

		enumHeadfileStream<<"		"<<tmp.identify;
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
		}
		enumHeadfileStream<<",\n";
		minEnumValue=minEnumValue<lastValue?minEnumValue:lastValue;
		maxEnumValue=maxEnumValue>lastValue?maxEnumValue:lastValue;
	}
	enumHeadfileStream<<"	};\n\n";
	
	//generated serialize code
	enumHeadfileStream<<"	void _csg_write(CSerializeStream& __os,"<<enumName<<" __enumType);\n";
	enumHeadfileStream<<"	void _csg_read(CSerializeStream& __is,"<<enumName<<"& __enumType);\n";
	enumHeadfileStream<<"\n\n";
	
	headfileContentStream<<enumHeadfileStream.content;
	
	//generated cpp serialize code
	std::string typeName=maxEnumValue>255?"int":"byte_t";
	
	CSGStream enumCppStream;
	
	enumCppStream<<"void Message::_csg_write(CSerializeStream& __os,"<<enumName<<" __enumType){\n"
				<<"	__os.write(static_cast<"<<typeName<<">(__enumType));\n}\n\n";
	enumCppStream<<"void Message::_csg_read(CSerializeStream& __is,"<<enumName<<"& __enumType){\n"
				<<"	"<<typeName<<" value;\n"
				<<"	__is.read(value);\n"
				<<"	__enumType=static_cast<"<<enumName<<">(value);\n"
				<<"	if(__enumType>"<<toStr(maxEnumValue)<<"||__enumType<"<<toStr(minEnumValue)<<")\n"
				<<"	{\n"
				<<"		throw CException(\"ExceptionCodeSerialize\",ExceptionCodeSerialize);\n"
				<<"	}\n"
				<<"}\n\n";
	
	cppContentStream<<enumCppStream.content;

};












struct: TOKEN_ID_START TOKEN_ID_NUM TOKEN_ID_END TOKEN_STRUCT_START TOKEN_STRUCT_NAME TOKEN_STRUCT_CONTENT {
	std::string structName=$5;
	structVec.push_back(structName);
	int idNum=$2;

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
	structHeadfileStream<<"	class "<<structName<<"\n"
						<<"		:public virtual csg::IMsgBase {\n"
						<<"	public:\n";

	//针对vector,map类型的成员变量,额外另生成方法读写
	CSGStream stlStructHeadStream;   //生成额外读写方法的头文件内容
	CSGStream stlStructCppStream;	//生成额外读写方法的cpp文件内容

	//每个结构体变量成员，都需要有 init,read,write,=,!=,< 这几个方法
	std::string initDef="	";		// _csg_init()函数内容
	std::string readDef;			// _csg_read()函数内容
	std::string writeDef;			// _csg_write()函数内容
	
	std::string operatorEq="	";
	std::string operatorEqEq;
	std::string operatorless;
	
	std::set<std::string> structNameSet; //判断结构体内同名的identify

	for(int i=0;i<$6.size();i++){
		CSGStruct tmp=$6[i];
		if(structNameSet.count(tmp.identify)>0){
			std::cerr<<"error struct value,duplicate name:"<<structName<<",identify:"<<tmp.identify<<std::endl;
			globalError=true;
			assert(false);
		}
		structNameSet.insert(tmp.identify);

		if(isBaseType(tmp.type)){  //基础类型结构体成员变量

			structHeadfileStream<<"		"<<getCsglType(tmp.type)<<"  "<<tmp.identify<<";\n";  //类型显示处理  getCsglType

			initDef+=tmp.identify+"="+getInitTypeString(tmp.type)+";\n	"; //代码初始值根据类型初始化 getInitTypeString
			readDef+="	__is.read("+tmp.identify+");\n";
			writeDef+="	__os.write("+tmp.identify+");\n";

		}else if(CSGStlTypeOne==tmp.stlTypeNum){   // vector类结构体成员变量处理
			
			structHeadfileStream<<"		std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<"> "<<tmp.identify<<";\n";  //变量定义

			initDef+=tmp.identify+".clear();\n	"; 

			if(isBaseType(tmp.stlType)){
				readDef+="	__is.read("+tmp.identify+");\n";
				writeDef+="	__os.write("+tmp.identify+");\n";
			}else{ //vector类自定义结构体成员变量
				// vector<A> ai;
				// tmp.type=vector
				// tmp.stlType=A
				// tmp.identify=ai
				// check

				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl one");


				//函数命名规则= 前缀+结构体名+stl类型+stl内的元素类型+identify
				std::string classFunctionName="__STL_TYPE_ONE__Struct__"+structName+"__"+tmp.type+"__"+tmp.stlType+"__"+tmp.identify+"__Serialize";

				readDef+="	Message::__read(__is,"+tmp.identify+","+classFunctionName+"());\n";
				writeDef+="	Message::__write(__os,"+tmp.identify+","+classFunctionName+"());\n";

				stlStructHeadStream<<"	class "<<classFunctionName<<" {};\n"
								<<"	void __read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<">"<<"&,"<<classFunctionName<<");\n"
								<<"	void __write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<">&,"<<classFunctionName<<");\n\n";
				
				stlStructCppStream<<"void Message::__read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<">"<<"& __data,"<<classFunctionName<<")\n"
									<<"{\n"
									<<"	int size=0;\n"
									<<"	__is.readSize(size);\n"
									<<"	for(int i=0;i<size;i++)\n"
									<<"	{\n"
									<<"		"<<tmp.stlType<<" val;\n"
									<<"		val._csg_read(__is);\n"
									<<"		__data.push_back(val);\n"
									<<"	}\n"
									<<"};\n\n"

									<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<tmp.stlType<<">& __data,"<<classFunctionName<<")\n\n"
									<<"{\n"
									<<"	int size=__data.size();\n"
									<<"	__os.writeSize(size);\n"
									<<"	for(std::"<<tmp.type<<"<"<<tmp.stlType<<">::const_iterator it=__data.cbegin();it!=__data.cend();++it)\n"
									<<"	{\n"
									<<"		(*it)._csg_write(__os);\n"
									<<"	}\n"
									<<"};\n\n";				
			}


		}else if(CSGStlTypeDouble==tmp.stlTypeNum){ //map类结构体成员变量
			// map<A,B> ab;
			// tmp.type=map
			// tmp.stlType=A
			// tmp.stlTypeEx=B
			// tmp.identify=ab

			structHeadfileStream<<"		std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<"> "<<tmp.identify<<";\n";  //变量定义
			initDef+=tmp.identify+".clear();\n	"; 
			
			//函数命名规则= 前缀+结构体名+stl类型+stlEx类型+stl内的元素类型+identify
			std::string classFunctionName="__STL_TYPE_DOUBLE__Struct__"+structName+"__"+tmp.type+"__"+tmp.stlType+"__"+tmp.stlTypeEx+"__"+tmp.identify+"__Serialize";

			readDef+="	Message::__read(__is,"+tmp.identify+","+classFunctionName+"());\n";
			writeDef+="	Message::__write(__os,"+tmp.identify+","+classFunctionName+"());\n";


			stlStructHeadStream<<"	class "<<classFunctionName<<" {};\n"
								<<"	void __read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">"<<"&,"<<classFunctionName<<");\n"
								<<"	void __write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">&,"<<classFunctionName<<");\n\n";

			
			stlStructCppStream<<"void Message::__read(csg::CSerializeStream& __is,std::"<<tmp.type+"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">"<<"& __data,"<<classFunctionName<<")\n"
								<<"{\n"
								<<"	int size=0;\n"
								<<"	__is.readSize(size);\n"
								<<"	for(int i=0;i<size;i++)\n"
								<<"	{\n"
								<<"		"<<getCsglType(tmp.stlType)<<" key;\n";

			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlType)){
				stlStructCppStream<<"		__is.read(key);\n";
			}else{
				//check
				checkIsCsglType(tmp.stlType,"unknow csgl struct type from struct stl double first key ");

				stlStructCppStream<<"		key._csg_read(__is);\n";
			}
					
			stlStructCppStream<<"		"<<getCsglType(tmp.stlTypeEx)<<" val;\n";

			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlTypeEx)){
				stlStructCppStream<<"		__is.read(val);\n";
			}else{
				//check
				checkIsCsglType(tmp.stlTypeEx,"unknow csgl struct type from struct stl double second key");

				stlStructCppStream<<"		val._csg_read(__is);\n";
			}

			stlStructCppStream<<"		__data[key]=val;\n"
								<<"	}\n"
								<<"};\n\n";

			stlStructCppStream<<"void Message::__write(csg::CSerializeStream& __os,const std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">& __data,"<<classFunctionName<<")\n\n"
								<<"{\n"
								<<"	int size=__data.size();\n"
								<<"	__os.writeSize(size);\n"
								<<"	for(std::"<<tmp.type<<"<"<<getCsglType(tmp.stlType)<<","<<getCsglType(tmp.stlTypeEx)<<">"<<"::const_iterator it=__data.cbegin();it!=__data.cend();++it)\n"
								<<"	{\n";
			//根据类型,使用不同的写方法
			if(isBaseType(tmp.stlType)){
				stlStructCppStream<<"		__os.write(it->first);\n";
			}else{
				stlStructCppStream<<"		it->first._csg_write(__os);\n";
			}
			//根据类型,使用不同的读方法
			if(isBaseType(tmp.stlTypeEx)){
				stlStructCppStream<<"		__os.write(it->second);\n";
			}else{
				stlStructCppStream<<"		it->second._csg_write(__os);\n";
			}
				
			stlStructCppStream<<"	}\n"
								<<"};\n\n";
		}
		else{ //自定义结构体成员变量
			checkIsCsglType(tmp.type,"unknow csgl struct type");

			structHeadfileStream<<"		"<<tmp.type<<"  "<<tmp.identify<<";\n";  //类型显示处理  getCsglType

			initDef+=tmp.identify+"._csg_init();\n	"; //代码初始值根据类型初始化 getInitTypeString

			readDef+="	"+tmp.identify+"._csg_read(__is);\n";
			writeDef+="	"+tmp.identify+"._csg_write(__os);\n";

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
	structHeadfileStream<<"	public:\n"
						<<"		"<<structName<<"();\n"
						<<"		"<<structName<<"(const "<<structName<<" &);\n"
						<<"		"<<structName<<"& operator=(const "<<structName<<" &);\n";
	structHeadfileStream<<"\n";
	structHeadfileStream<<"	public:\n";
	structHeadfileStream<<"		bool operator==(const "<<structName<<" &)const;\n"
						<<"		bool operator!=(const "<<structName<<" &)const;\n"
						<<"		bool operator<(const "<<structName<<" &)const;\n\n"
						<<"		void _csg_init();\n"
						<<"		void _csg_read(CSerializeStream&);\n"
						<<"		void _csg_write(CSerializeStream&)const;\n\n"
						<<"		virtual IMsgBase* clone();\n"
						<<"		virtual int getType()const;\n";
	structHeadfileStream<<"	private:\n"
						<<"		static const int _msgType = "<<toStr(idNum)<<";\n";
						
	structHeadfileStream<<"	};\n\n";
	structHeadfileStream<<"	typedef csg::CSmartPointShare<"<<structName<<"> "<<structName<<"_Ptr;\n\n";
	
	headfileContentStream<<structHeadfileStream.content;
	headfileContentStream<<stlStructHeadStream.content;

	//generated cpp code
	CSGStream structCppStream;
	std::string constructioncpp="";

	//construcion
	structCppStream<<"Message::"<<structName<<"::"<<structName<<"()\n"
					<<"{\n"
					<<"	_csg_init();\n"
					<<"}\n\n";

	structCppStream<<"Message::"<<structName<<"::"<<structName<<"(const "<<structName<<"& __other)\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return;\n"
					<<"	}\n"
					<<"	*this=__other;\n"
					<<"}\n\n";

	structCppStream<<"Message::"<<structName<<"& Message::"<<structName<<"::operator=(const "<<structName<<"& __other)\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return *this;\n"
					<<"	}\n"
					<<"	IMsgBase::operator=(__other);\n"
					<<operatorEq
					<<"return *this;\n"
					<<"}\n\n";

	structCppStream<<"int Message::"<<structName<<"::getType()const{\n"
					<<"	return _msgType;\n"
					<<"}\n\n";
	
	structCppStream<<"csg::IMsgBase* Message::"<<structName<<"::clone()\n"
					<<"{\n"
					<<"	return new "<<structName<<"(*this);\n"
					<<"}\n\n";
				
	structCppStream<<"bool Message::"<<structName<<"::operator==(const "<<structName<<"& __other)const\n"
					<<"{\n"
					<<"	return !operator!=(__other);\n"
					<<"}\n\n";

	structCppStream<<"bool Message::"<<structName<<"::operator!=(const "<<structName<<"& __other)const\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return false;\n"
					<<"	}\n"
					<<operatorEqEq
					<<"	return false;\n"
					<<"}\n\n";

	structCppStream<<"bool Message::"<<structName<<"::operator<(const "<<structName<<"& __other)const\n"
					<<"{\n"
					<<"	if(this==&__other)\n"
					<<"	{\n"
					<<"		return false;\n"
					<<"	}\n"
					<<operatorless
					<<"	return false;\n"
					<<"}\n\n";



	structCppStream<<"void Message::"<<structName<<"::_csg_init(){\n"
					<<initDef<<"\n};\n\n";	
	structCppStream<<"void Message::"<<structName<<"::_csg_read(CSerializeStream& __is){\n"
					<<readDef<<"};\n\n";
	structCppStream<<"void Message::"<<structName<<"::_csg_write(CSerializeStream& __os)const{\n"
					<<writeDef<<"};\n\n";
					
	structCppStream<<stlStructCppStream.content;

	cppContentStream<<structCppStream.content;
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

void csgOutputCppHead(std::string fileName){
	ofscpp<<"#include "<<"\""<<fileName+"\.h\"\n";
	ofscpp<<"#include \"engine/rpc/rpcHelper.h\"\n";
	ofscpp<<"using namespace csg;\n";
	ofscpp<<"using namespace Message;\n\n";
}


void csgOutputHead(){
	ofs<<csgDefStr<<"\n";
	ofs<<headDefStream.content<<"\n";
	ofs<<includeCsgFile<<"\n";
	ofs<<headIncludeStream.content<<"\n";
	ofs<<"using namespace csg;"<<"\n\n";
	ofs<<"namespace Message {"<<"\n\n";
	
}

void csgOutputEnd(std::string fileName){
	//regist struct
	std::string registClass="C"+fileName;
	ofs<<"	class "<<registClass<<"{\n"
		<<"	public:\n"
		<<"		static void regist();\n"
		<<"	};\n";
	ofs<<"\n}\n\n";//namespace

	//interface

	ofs<<headInterfaceStream.content<<"\n";

	ofs<<endDefStream.content<<"\n";

	CSGStream cppregistStream;
	cppregistStream<<"void Message::"<<registClass<<"::regist()\n"
					<<"{\n";
	for(int i=0;i<structVec.size();i++){
		cppregistStream<<"	csg::CMsgManager::instance()->regist(new "<<structVec[i]<<"());\n";
	}
	cppregistStream<<"}\n";
	cppContentStream<<cppregistStream.content;
}



void yyerror(const char* s){
	std::cerr<<"\033[31m"<<"get error:["<<s<<"]\033[0m"<<std::endl;
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
	std::string outputHeadFileName=outputDir+inputfile+".h";
	std::string outputCppFileName=outputDir+inputfile+".cpp";

	std::cout<<"input file is "<<YELLOW<<inputfileCsg<<RESET<<std::endl;
	std::cout<<"output dir is "<<YELLOW<<outputDir<<RESET<<std::endl;
	std::cout<<"output headfile is "<<GREEN<<outputHeadFileName<<RESET<<std::endl;
	std::cout<<"output cppfile is "<<GREEN<<outputCppFileName<<RESET<<std::endl;

	FILE *fp=fopen(inputfileCsg.c_str(),"r");
	if(NULL==fp){
		std::cerr<<RED<<"can't open file "<<inputfileCsg<<RESET<<std::endl;
		return 0;
	}
	
	ofs.open(outputHeadFileName);
	ofscpp.open(outputCppFileName);

	if(!ofs.is_open()){
		std::cerr<<RED<<"can't open file "<<outputHeadFileName<<RESET<<std::endl;
		return 0;
	}
	if(!ofscpp.is_open()){
		std::cerr<<RED<<"can't open file "<<outputCppFileName<<RESET<<std::endl;
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


	std::cout<<GREEN<<"start generated cpp file "<<inputfileName<<RESET<<std::endl;
	//generated cppfile
	csgOutputCppHead(inputfile);
	ofscpp<<cppContentStream.content<<std::endl;
	ofscpp<<cppInterfaceStream.content<<"\n";

	std::cout<<BOLDGREEN<<"build csgl file success!"<<RESET<<std::endl;
	
	ofs.close();
	ofscpp.close();
	return 0;
}



