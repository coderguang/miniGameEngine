
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
	virtual void response(const std::vector<long64_t>&);
};

typedef CSmartPointShare<CCli_ITest_t5_CallBack> CCli_ITest_t5_CallBackPtr;


class CCli_ITest_t6_CallBack :public virtual csg_proxy::CCli_ITest_t6 {
public:
	virtual void response(const std::map<STest, long64_t>&);
};

typedef CSmartPointShare<CCli_ITest_t6_CallBack> CCli_ITest_t6_CallBackPtr;




class ITestImpl:public virtual Message::ITest
{
public:
	virtual void t1_async(const CSessionPtr& ,CSrv_ITest_t1_Ptr&)override;

	virtual void t2_async(const CSessionPtr& ,Message::CSrv_ITest_t2_Ptr& ,const int ,const string)override;

	virtual void t3_async(const CSessionPtr& ,Message::CSrv_ITest_t3_Ptr& ,const int ,const string)override;

	virtual void t4_async(const CSessionPtr&, Message::CSrv_ITest_t4_Ptr&, const STestMap &)override;

	virtual void t5_async(const CSessionPtr&, Message::CSrv_ITest_t5_Ptr&, const std::vector<STest>&)override;

	virtual void t6_async(const CSessionPtr&, Message::CSrv_ITest_t6_Ptr&, const std::map<std::string, STest>&)override;


	
};




#endif