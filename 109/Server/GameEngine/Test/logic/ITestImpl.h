
#ifndef _TEST_LOGIC_ITEST_IMPL_H_
#define _TEST_LOGIC_ITEST_IMPL_H_


#include "../../Message/Test.h"

using namespace Message;
using namespace csg;

class CCli_ITest_t3_CallBack :public virtual csg_proxy::CCli_ITest_t3
{
public:
	virtual void response(const bool b ,const string os)override;

};

typedef CSmartPointShare<CCli_ITest_t3_CallBack> CCli_ITest_t3_CallBackPtr;


class CCli_ITest_t4_CallBack :public virtual csg_proxy::CCli_ITest_t4 {
public:
	virtual void response(const STestMap&);
};

typedef CSmartPointShare<CCli_ITest_t4_CallBack> CCli_ITest_t4_CallBackPtr;

class CCli_ITest_t5_CallBack :public virtual csg_proxy::CCli_ITest_t5 {
public:
	virtual void response(const std::vector<int>&);

	virtual void exception(const csg::CException& ex);
};

typedef CSmartPointShare<CCli_ITest_t5_CallBack> CCli_ITest_t5_CallBackPtr;


class CCli_ITest_t6_CallBack :public virtual csg_proxy::CCli_ITest_t6 {
public:
	virtual void response(const std::map<STest, int>&);
};

typedef CSmartPointShare<CCli_ITest_t6_CallBack> CCli_ITest_t6_CallBackPtr;

class CCli_ITest_t7_CallBack :public virtual csg_proxy::CCli_ITest_t7 {
public:
	virtual void response(const STestStruct& t);
};


class ITestImpl:public virtual Message::ITest
{
public:
	virtual void t1_async(const CSessionPtr& ,CSrv_ITest_t1_Ptr&)override;

	virtual void t2_async(const CSessionPtr& ,Message::CSrv_ITest_t2_Ptr& , int , string)override;

	virtual void t3_async(const CSessionPtr& ,Message::CSrv_ITest_t3_Ptr& , int , string)override;

	virtual void t4_async(const CSessionPtr&, Message::CSrv_ITest_t4_Ptr&,  const STestMap &)override;

	virtual void t5_async(const CSessionPtr&, Message::CSrv_ITest_t5_Ptr&, const std::vector<STest>&)override;

	virtual void t6_async(const CSessionPtr&, Message::CSrv_ITest_t6_Ptr&, const std::map<std::string, STest>&)override;

	virtual void t7_async(const CSessionPtr&, Message::CSrv_ITest_t7_Ptr&, int a, const STestStruct &b);
	
};




#endif