#include "ITestImpl.h"
#include "../../Message/Test.h"
#include "framework/util/typetransform.h"


using namespace csg;
using namespace Message;


void ITestImpl::t1_async(const CSessionPtr& session,CSrv_ITest_t1_Ptr& cb)
{
	LogInfo("t1_async be call");

	//cb->response();
	cb->exception("hello");
}

void ITestImpl::t2_async(const CSessionPtr& ,Message::CSrv_ITest_t2_Ptr& cb, int param, string str)
{
	LogInfo("t2_async be call,param="<<param<<",str="<<str);

	cb->response();
}

void ITestImpl::t3_async(const CSessionPtr& session ,Message::CSrv_ITest_t3_Ptr& cb, int param, string str)
{
	LogInfo("t3_async be call,param=" << param << ",str=" << str);

	bool ok = true;
	std::string hi = "hi geo";
	cb->response(ok,hi);

	STestStruct_Ptr t = new STestStruct();
	t->a = 45;
	t->b = true;
	t->str = "gewgw w3";
	t->ib.push_back(4646);
	t->ib.push_back(46461);
	t->ib.push_back(0);
	t->ib.push_back(0);
	t->ib.push_back(6);
	t->ib.push_back(0);
	t->ib.push_back(0);
	t->ib.push_back(46461);
	t->ib.push_back(46462);

	CMsgBlockPtr mb = new CMsgBlock();
	mb->_msgHead.command = 46452;
	mb->_msgBase = t;
	session->pushMessage(mb);
}

void ITestImpl::t4_async(const CSessionPtr&, Message::CSrv_ITest_t4_Ptr& cb, const STestMap &tm)
{
	LogInfo("t4_async be call");

	cb->response(tm);
}

void ITestImpl::t5_async(const CSessionPtr&, Message::CSrv_ITest_t5_Ptr& cb,const  std::vector<STest>& vs)
{
	LogInfo("t5_async be call");
	std::vector<long64_t> vl;
	for (int i = 0; i < 500; i++)
		vl.push_back(111111111 * i);
	//cb->response(vl);
	cb->exception("hello");
}

void ITestImpl::t6_async(const CSessionPtr&, Message::CSrv_ITest_t6_Ptr& cb,const  std::map<std::string, STest>& ss)
{
	LogInfo("t6_async be call");
	for (std::map<std::string, STest>::const_iterator it = ss.begin(); it != ss.end(); ++it) {
		std::string s = it->first;
		STest t = it->second;
	}
	std::map<Message::STest, int> vl;
	STest t;
	int times = 100;
	for (int i = 0; i < times; i++) {
		t.a = i*11111;
		t.str = ToStr(t.a);
		t.ib.push_back(t.a);
		vl[t] = i * 111;
	}
	cb->response(vl);
}

void ITestImpl::t7_async(const CSessionPtr&, Message::CSrv_ITest_t7_Ptr& cb, int a, const STestStruct &b)
{
	LogInfo("t7_async be call");
	LogInfo("a=" << b.a);
	LogInfo("b=" << b.b);
	LogInfo("str=" << b.str);
	int i = 0;
	for (std::vector<int>::const_iterator it = b.ib.begin(); it != b.ib.end(); ++it) {
		LogInfo("  i="<<i++<<",v="<<*it);
	}
	cb->response(b);
}

void CCli_ITest_t3_CallBack::response(const bool b ,const string os)
{
	LogInfo("CSrv_ITest_t3_CallBack,b=" << b << ",str=" << os);
}

void CCli_ITest_t4_CallBack::response(const STestMap& t)
{
	LogInfo("CSrv_ITest_t4_CallBack");
}
 
void CCli_ITest_t5_CallBack::response(const std::vector<int>& vl)
{
	LogInfo("CSrv_ITest_t5_CallBack");
}

void CCli_ITest_t5_CallBack::exception(const csg::CException& ex)
{
	LogInfo("CSrv_ITest_t5_CallBack exception code="<<ex.code()<<",ex.what="<<ex.what() );
}

void CCli_ITest_t6_CallBack::response(const std::map<STest, int>& msl)
{
	LogInfo("CSrv_ITest_t6_CallBack");
}

void CCli_ITest_t7_CallBack::response(const STestStruct& t)
{
	LogInfo("CCli_ITest_t7_CallBack");
}
