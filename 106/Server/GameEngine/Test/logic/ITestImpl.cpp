#include "ITestImpl.h"
#include "../../Message/Test.h"


using namespace csg;
using namespace Message;


void ITestImpl::t1_async(const CSessionPtr& session,CSrv_ITest_t1_Ptr& cb)
{
	LogInfo("t1_async be call");

	cb->response();
}

void ITestImpl::t2_async(const CSessionPtr& ,Message::CSrv_ITest_t2_Ptr& cb,int param,string str)
{
	LogInfo("t2_async be call,param="<<param<<",str="<<str);

	cb->response();
}

void ITestImpl::t3_async(const CSessionPtr& ,Message::CSrv_ITest_t3_Ptr& cb,int param,string str)
{
	LogInfo("t3_async be call,param=" << param << ",str=" << str);

	bool ok = true;
	std::string hi = "hi geo";
	cb->response(ok,hi);
}

void CCli_ITest_t3_CallBack::response(bool b ,string os)
{
	LogInfo("CSrv_ITest_t3_CallBack,b=" << b << ",str=" << os);
}
