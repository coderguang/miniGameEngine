//******************************************
// generated by royalchen's csgl tools
// email:royalchen@royalchen.com 
// FAQ:www.royalchen.com
// ******************************************
#ifndef _MESSAGE_TEST_H_
#define _MESSAGE_TEST_H_

#include "engine/serialize/serializestream.h"
#include "engine/def/csg_def.h"
#include "engine/mq/msgBlock.h"
#include "engine/mq/msgManager.h"
#include "engine/rpc/rmiObject.h"

#include "TestStruct.h"

using namespace csg;

namespace Message {

	enum ETest {
		ETestOne = 1,
		ETestTwo,
		ETestThree = 5,
	};

	void _csg_write(CSerializeStream& __os,ETest __enumType);
	void _csg_read(CSerializeStream& __is,ETest& __enumType);


	class STest
		:public virtual csg::IMsgBase {
	public:
		int  a;
		bool  b;
		std::string  str;
		STestStruct  tt;
		std::vector<int> ib;
		std::vector<STestStruct> hss;
		std::vector<long64_t> il;
		std::vector<std::string> is;

	public:
		STest();
		STest(const STest &);
		STest& operator=(const STest &);

	public:
		bool operator==(const STest &)const;
		bool operator!=(const STest &)const;
		bool operator<(const STest &)const;

		void _csg_init();
		void _csg_read(CSerializeStream&);
		void _csg_write(CSerializeStream&)const;

		virtual IMsgBase* clone();
		virtual int getType()const;
	private:
		static const int _msgType = 1;
	};

	typedef csg::CSmartPointShare<STest> STest_Ptr;

	class __STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize {};
	void __read(csg::CSerializeStream& __is,std::vector<STestStruct>&,__STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize);
	void __write(csg::CSerializeStream& __os,const std::vector<STestStruct>&,__STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize);

	class STestMap
		:public virtual csg::IMsgBase {
	public:
		int  a;
		std::map<int,long64_t> ii;
		std::map<int,double> il;
		std::map<std::string,std::string> ss;
		std::map<int,float> iff;
		std::map<int,STestStruct> mis;
		std::map<STestStruct,STest> mss;
		std::map<STestStruct,std::string> msstring;

	public:
		STestMap();
		STestMap(const STestMap &);
		STestMap& operator=(const STestMap &);

	public:
		bool operator==(const STestMap &)const;
		bool operator!=(const STestMap &)const;
		bool operator<(const STestMap &)const;

		void _csg_init();
		void _csg_read(CSerializeStream&);
		void _csg_write(CSerializeStream&)const;

		virtual IMsgBase* clone();
		virtual int getType()const;
	private:
		static const int _msgType = 6;
	};

	typedef csg::CSmartPointShare<STestMap> STestMap_Ptr;

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<int,long64_t>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<int,long64_t>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize);

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<int,double>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<int,double>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize);

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<std::string,std::string>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<std::string,std::string>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize);

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<int,float>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<int,float>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize);

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<int,STestStruct>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<int,STestStruct>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize);

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<STestStruct,STest>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<STestStruct,STest>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize);

	class __STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize {};
	void __read(csg::CSerializeStream& __is,std::map<STestStruct,std::string>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize);
	void __write(csg::CSerializeStream& __os,const std::map<STestStruct,std::string>&,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize);


	class CTest{
	public:
		static void regist();
	};

}

namespace Message
{
	class CSrv_ITest_t1:public virtual CRMIObjectCallBackObject
	{
	public:
		virtual void response();
	};
	typedef CSmartPointShare<CSrv_ITest_t1> CSrv_ITest_t1_Ptr;

	class CSrv_ITest_t2:public virtual CRMIObjectCallBackObject
	{
	public:
		virtual void response();
	};
	typedef CSmartPointShare<CSrv_ITest_t2> CSrv_ITest_t2_Ptr;

	class CSrv_ITest_t3:public virtual CRMIObjectCallBackObject
	{
	public:
		virtual void response(const bool b,const std::string os);
	};
	typedef CSmartPointShare<CSrv_ITest_t3> CSrv_ITest_t3_Ptr;

	class CSrv_ITest_t4:public virtual CRMIObjectCallBackObject
	{
	public:
		virtual void response(const STestMap& os);
	};
	typedef CSmartPointShare<CSrv_ITest_t4> CSrv_ITest_t4_Ptr;

	class CSrv_ITest_t5:public virtual CRMIObjectCallBackObject
	{
	public:
		virtual void response(const std::vector<long64_t>& vl);
	};
	typedef CSmartPointShare<CSrv_ITest_t5> CSrv_ITest_t5_Ptr;

	class CSrv_ITest_t6:public virtual CRMIObjectCallBackObject
	{
	public:
		virtual void response(const std::map<STest,long64_t>& vl);
	};
	typedef CSmartPointShare<CSrv_ITest_t6> CSrv_ITest_t6_Ptr;

	class __STL_TYPE_ONE__Interface__CSrv__ITest__t6__map__STest__long__vl{};
	void __write(csg::CSerializeStream& __os,const std::map<STest,long64_t>&,__STL_TYPE_ONE__Interface__CSrv__ITest__t6__map__STest__long__vl);

}



namespace Message
{
	class ITest:public virtual CRMIObject
	{
	public:
		ITest();

		virtual ERMIDispatchResult __onCall(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		ERMIDispatchResult __t1_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t1_async(const CSessionPtr& ,Message::CSrv_ITest_t1_Ptr&)=0;

		ERMIDispatchResult __t2_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t2_async(const CSessionPtr& ,Message::CSrv_ITest_t2_Ptr&,int,std::string)=0;

		ERMIDispatchResult __t3_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t3_async(const CSessionPtr& ,Message::CSrv_ITest_t3_Ptr&,int,std::string)=0;

		ERMIDispatchResult __t4_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t4_async(const CSessionPtr& ,Message::CSrv_ITest_t4_Ptr&,const STestMap &)=0;

		ERMIDispatchResult __t5_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t5_async(const CSessionPtr& ,Message::CSrv_ITest_t5_Ptr&,const std::vector<STest>&)=0;

		ERMIDispatchResult __t6_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t6_async(const CSessionPtr& ,Message::CSrv_ITest_t6_Ptr&,const std::map<std::string,STest>&)=0;

	};

	class __STL_TYPE_ONE__Interface_CSrv__Read__ITest__t5__vector__STest__v{};
	void __read(CSerializeStream&,std::vector<STest>&,__STL_TYPE_ONE__Interface_CSrv__Read__ITest__t5__vector__STest__v);

	class __STL_TYPE_DOUBLE__Interface_CSrv__Read__ITest__t6__map__string__STest__mss{};
	void __read(CSerializeStream&,std::map<std::string,STest>&,__STL_TYPE_DOUBLE__Interface_CSrv__Read__ITest__t6__map__string__STest__mss);

}

namespace csg_proxy
{
	using namespace Message;

	class CCli_ITest_t1:public virtual CRMIProxyCallBackObject
	{
	public:
		virtual void response()=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t1> CCli_ITest_t1_Ptr;

	class CCli_ITest_t2:public virtual CRMIProxyCallBackObject
	{
	public:
		virtual void response()=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t2> CCli_ITest_t2_Ptr;

	class CCli_ITest_t3:public virtual CRMIProxyCallBackObject
	{
	public:
		virtual void response(const bool,const std::string)=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t3> CCli_ITest_t3_Ptr;

	class CCli_ITest_t4:public virtual CRMIProxyCallBackObject
	{
	public:
		virtual void response(const STestMap&)=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t4> CCli_ITest_t4_Ptr;

	class CCli_ITest_t5:public virtual CRMIProxyCallBackObject
	{
	public:
		virtual void response(const std::vector<long64_t>& )=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t5> CCli_ITest_t5_Ptr;

	class CCli_ITest_t6:public virtual CRMIProxyCallBackObject
	{
	public:
		virtual void response(const std::map<STest,long64_t>&)=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t6> CCli_ITest_t6_Ptr;

	class __STL_TYPE_DOUBLE__Interface_CCli__Read__ITest__t6__map__STest__long__vl {};
	void __read(CSerializeStream&,std::map<STest,long64_t>&,__STL_TYPE_DOUBLE__Interface_CCli__Read__ITest__t6__map__STest__long__vl);

}

namespace csg_proxy
{
	using namespace Message;

	class ITest:public virtual CRMIProxyObject
	{
	public:
		ITest();
		void t1_async(const CSessionPtr&,const CCli_ITest_t1_Ptr&);

		void t2_async(const CSessionPtr&,const CCli_ITest_t2_Ptr&,const int,const std::string);

		void t3_async(const CSessionPtr&,const CCli_ITest_t3_Ptr&,const int,const std::string);

		void t4_async(const CSessionPtr&,const CCli_ITest_t4_Ptr&,const STestMap&);

		void t5_async(const CSessionPtr&,const CCli_ITest_t5_Ptr&,const std::vector<STest>&);

		void t6_async(const CSessionPtr&,const CCli_ITest_t6_Ptr&,const std::map<std::string,STest>&);

	};

	class __STL_TYPE_ONE__Interface_CCli__Write__ITest__t5__vector__STest____v {};
	void __write(CSerializeStream&,const std::vector<STest>&,__STL_TYPE_ONE__Interface_CCli__Write__ITest__t5__vector__STest____v);

	class __STL_TYPE_DOUBLE__Interface_CCli__Write__ITest__t6__map__string__STest__mss {};
	void __write(CSerializeStream&,const std::map<std::string,STest>&,__STL_TYPE_DOUBLE__Interface_CCli__Write__ITest__t6__map__string__STest__mss);

}


#endif

