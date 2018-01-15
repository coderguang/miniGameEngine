#include "Test.h"
#include "engine/rpc/rpcHelper.h"
using namespace csg;
using namespace Message;

void Message::_csg_write(CSerializeStream& __os,ETest __enumType){
	__os.write(static_cast<byte_t>(__enumType));
}

void Message::_csg_read(CSerializeStream& __is,ETest& __enumType){
	byte_t value;
	__is.read(value);
	__enumType=static_cast<ETest>(value);
	if(__enumType>5||__enumType<1)
	{
		throw CException("ExceptionCodeSerialize",ExceptionCodeSerialize);
	}
}

Message::STest::STest()
{
	_csg_init();
}

Message::STest::STest(const STest& __other)
{
	if(this==&__other)
	{
		return;
	}
	*this=__other;
}

Message::STest& Message::STest::operator=(const STest& __other)
{
	if(this==&__other)
	{
		return *this;
	}
	IMsgBase::operator=(__other);
	a = __other.a;
	b = __other.b;
	str = __other.str;
	ib = __other.ib;
	return *this;
}

int Message::STest::getType()const{
	return _msgType;
}

csg::IMsgBase* Message::STest::clone()
{
	return new STest(*this);
}

bool Message::STest::operator==(const STest& __other)const
{
	return !operator!=(__other);
}

bool Message::STest::operator!=(const STest& __other)const
{
	if(this==&__other)
	{
		return false;
	}
	if(a != __other.a)
	{
		return true;
	}
	if(b != __other.b)
	{
		return true;
	}
	if(str != __other.str)
	{
		return true;
	}
	if(ib != __other.ib)
	{
		return true;
	}
	return false;
}

bool Message::STest::operator<(const STest& __other)const
{
	if(this==&__other)
	{
		return false;
	}
	if(a < __other.a)
	{
		return true;
	}
	if(b < __other.b)
	{
		return true;
	}
	if(str < __other.str)
	{
		return true;
	}
	if(ib < __other.ib)
	{
		return true;
	}
	return false;
}

void Message::STest::_csg_init(){
	a=0;
	b=false;
	str="";
	ib.clear();
	
};

void Message::STest::_csg_read(CSerializeStream& __is){
	__is.read(a);
	__is.read(b);
	__is.read(str);
	__is.read(ib);
};

void Message::STest::_csg_write(CSerializeStream& __os)const{
	__os.write(a);
	__os.write(b);
	__os.write(str);
	__os.write(ib);
};

Message::STestMap::STestMap()
{
	_csg_init();
}

Message::STestMap::STestMap(const STestMap& __other)
{
	if(this==&__other)
	{
		return;
	}
	*this=__other;
}

Message::STestMap& Message::STestMap::operator=(const STestMap& __other)
{
	if(this==&__other)
	{
		return *this;
	}
	IMsgBase::operator=(__other);
	a = __other.a;
	ii = __other.ii;
	il = __other.il;
	ss = __other.ss;
	iff = __other.iff;
	return *this;
}

int Message::STestMap::getType()const{
	return _msgType;
}

csg::IMsgBase* Message::STestMap::clone()
{
	return new STestMap(*this);
}

bool Message::STestMap::operator==(const STestMap& __other)const
{
	return !operator!=(__other);
}

bool Message::STestMap::operator!=(const STestMap& __other)const
{
	if(this==&__other)
	{
		return false;
	}
	if(a != __other.a)
	{
		return true;
	}
	if(ii != __other.ii)
	{
		return true;
	}
	if(il != __other.il)
	{
		return true;
	}
	if(ss != __other.ss)
	{
		return true;
	}
	if(iff != __other.iff)
	{
		return true;
	}
	return false;
}

bool Message::STestMap::operator<(const STestMap& __other)const
{
	if(this==&__other)
	{
		return false;
	}
	if(a < __other.a)
	{
		return true;
	}
	if(ii < __other.ii)
	{
		return true;
	}
	if(il < __other.il)
	{
		return true;
	}
	if(ss < __other.ss)
	{
		return true;
	}
	if(iff < __other.iff)
	{
		return true;
	}
	return false;
}

void Message::STestMap::_csg_init(){
	a=0;
	ii.clear();
	il.clear();
	ss.clear();
	iff.clear();
	
};

void Message::STestMap::_csg_read(CSerializeStream& __is){
	__is.read(a);
	Message::__read(__is,ii,__Map_STestMap_int_int_Serialize_());
	Message::__read(__is,il,__Map_STestMap_int_double_Serialize_());
	Message::__read(__is,ss,__Map_STestMap_string_string_Serialize_());
	Message::__read(__is,iff,__Map_STestMap_int_float_Serialize_());
};

void Message::STestMap::_csg_write(CSerializeStream& __os)const{
	__os.write(a);
	Message::__write(__os,ii,__Map_STestMap_int_int_Serialize_());
	Message::__write(__os,il,__Map_STestMap_int_double_Serialize_());
	Message::__write(__os,ss,__Map_STestMap_string_string_Serialize_());
	Message::__write(__os,iff,__Map_STestMap_int_float_Serialize_());
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,int>& __data,__Map_STestMap_int_int_Serialize_)
{
	int size=0;
	__is.read(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		int val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,int>& __data,__Map_STestMap_int_int_Serialize_)
{
	int size=__data.size();
	__os.write(size);
	for(std::map<int,int>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,double>& __data,__Map_STestMap_int_double_Serialize_)
{
	int size=0;
	__is.read(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		double val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,double>& __data,__Map_STestMap_int_double_Serialize_)
{
	int size=__data.size();
	__os.write(size);
	for(std::map<int,double>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<string,string>& __data,__Map_STestMap_string_string_Serialize_)
{
	int size=0;
	__is.read(size);
	for(int i=0;i<size;i++)
	{
		string key;
		__is.read(key);
		string val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<string,string>& __data,__Map_STestMap_string_string_Serialize_)
{
	int size=__data.size();
	__os.write(size);
	for(std::map<string,string>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,float>& __data,__Map_STestMap_int_float_Serialize_)
{
	int size=0;
	__is.read(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		float val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,float>& __data,__Map_STestMap_int_float_Serialize_)
{
	int size=__data.size();
	__os.write(size);
	for(std::map<int,float>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::CTest::regist()
{
	csg::CMsgManager::instance()->regist(new STest());
	csg::CMsgManager::instance()->regist(new STestMap());
}

void Message::CSrv_ITest_t1::response()
{
	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	SRMIReturn rmiReturn;
	rmiReturn.dispatchStatus = ERMIDispatchResultOk;
	rmiReturn.messageId = _rmiCall.messageId;

	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);

	__os->setUseBitMark(true);


	CRpcHelper::toReturn(_session,__os);

}

void Message::CSrv_ITest_t2::response()
{
	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	SRMIReturn rmiReturn;
	rmiReturn.dispatchStatus = ERMIDispatchResultOk;
	rmiReturn.messageId = _rmiCall.messageId;

	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);

	__os->setUseBitMark(true);


	CRpcHelper::toReturn(_session,__os);

}

void Message::CSrv_ITest_t3::response(bool b,string os)
{
	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	SRMIReturn rmiReturn;
	rmiReturn.dispatchStatus = ERMIDispatchResultOk;
	rmiReturn.messageId = _rmiCall.messageId;

	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);

	__os->setUseBitMark(true);

	__os->write(b);
	__os->write(os);

	CRpcHelper::toReturn(_session,__os);

}

Message::ITest::ITest()
{
	SRMIInfo rmiInfo;
	rmiInfo.identify="ITest";

	rmiInfo.operation="t1";
	addRMIInfo(11,rmiInfo);
	addRpcId(11);

	rmiInfo.operation="t2";
	addRMIInfo(12,rmiInfo);
	addRpcId(12);

	rmiInfo.operation="t3";
	addRMIInfo(13,rmiInfo);
	addRpcId(13);

}

csg::ERMIDispatchResult Message::ITest::__onCall(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	switch(rmiCall.rpcId)
	{
		case 11:
		{
			return __t1_async(session,rmiCall,__is);
		}
		break;
		case 12:
		{
			return __t2_async(session,rmiCall,__is);
		}
		break;
		case 13:
		{
			return __t3_async(session,rmiCall,__is);
		}
		break;
		default:
		break;
	}

	return ERMIDispatchObjectNotExist;

}

csg::ERMIDispatchResult Message::ITest::__t1_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	CSrv_ITest_t1_Ptr cb=new CSrv_ITest_t1();
	cb->setSession(session,rmiCall);
	t1_async(session,cb);

	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t2_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	int a;
	__is.read(a);
	string s;
	__is.read(s);
	CSrv_ITest_t2_Ptr cb=new CSrv_ITest_t2();
	cb->setSession(session,rmiCall);
	t2_async(session,cb,a,s);

	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t3_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	int a;
	__is.read(a);
	string s;
	__is.read(s);
	CSrv_ITest_t3_Ptr cb=new CSrv_ITest_t3();
	cb->setSession(session,rmiCall);
	t3_async(session,cb,a,s);

	return ERMIDispatchResultOk;

}

void csg_proxy::CCli_ITest_t1::__response(CSerializeStream& __is)
{

	response();

}

void csg_proxy::CCli_ITest_t2::__response(CSerializeStream& __is)
{

	response();

}

void csg_proxy::CCli_ITest_t3::__response(CSerializeStream& __is)
{
	bool b;
	__is.read(b);
	string os;
	__is.read(os);

	response(b,os);

}

csg_proxy::ITest::ITest()
{
}

void csg_proxy::ITest::t1_async(const CSessionPtr& session,const CCli_ITest_t1_Ptr& cb)
{
	csg::SRMICall call;
	call.rpcId=11;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	CRMIObjectBindPtr objectBind=NULL;
	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);

	__os->setUseBitMark(true);

	CRpcHelper::toCall(session,__os,objectBind);

}

void csg_proxy::ITest::t2_async(const CSessionPtr& session,const CCli_ITest_t2_Ptr& cb,int a,string s)
{
	csg::SRMICall call;
	call.rpcId=12;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	CRMIObjectBindPtr objectBind=NULL;
	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);

	__os->setUseBitMark(true);
	__os->write(a);
	__os->write(s);

	CRpcHelper::toCall(session,__os,objectBind);

}

void csg_proxy::ITest::t3_async(const CSessionPtr& session,const CCli_ITest_t3_Ptr& cb,int a,string s)
{
	csg::SRMICall call;
	call.rpcId=13;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	CRMIObjectBindPtr objectBind=NULL;
	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);

	__os->setUseBitMark(true);
	__os->write(a);
	__os->write(s);

	CRpcHelper::toCall(session,__os,objectBind);

}


