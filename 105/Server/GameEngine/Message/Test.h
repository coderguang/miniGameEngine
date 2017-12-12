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
		std::vector<int>  ib;

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
		virtual void response(bool b,string os);
	};
	typedef CSmartPointShare<CSrv_ITest_t3> CSrv_ITest_t3_Ptr;

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

		virtual void t2_async(const CSessionPtr& ,Message::CSrv_ITest_t2_Ptr&,int,string)=0;

		ERMIDispatchResult __t3_async(const CSessionPtr&,const SRMICall&,CSerializeStream&);

		virtual void t3_async(const CSessionPtr& ,Message::CSrv_ITest_t3_Ptr&,int,string)=0;

	};
}

namespace csg_proxy
{
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
		virtual void response(bool b,string os)=0;
	protected:
		virtual void __response(CSerializeStream& __is);
	};
	typedef CSmartPointShare<CCli_ITest_t3> CCli_ITest_t3_Ptr;

}

namespace csg_proxy
{
	class ITest:public virtual CRMIProxyObject
	{
	public:
		ITest();
		void t1_async(const CSessionPtr&,const CCli_ITest_t1_Ptr&);

		void t2_async(const CSessionPtr&,const CCli_ITest_t2_Ptr&,int,string);

		void t3_async(const CSessionPtr&,const CCli_ITest_t3_Ptr&,int,string);

	};
}


#endif


