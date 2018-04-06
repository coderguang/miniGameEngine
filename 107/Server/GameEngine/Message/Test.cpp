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
	tt = __other.tt;
	ib = __other.ib;
	hss = __other.hss;
	il = __other.il;
	is = __other.is;
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
	if(tt != __other.tt)
	{
		return true;
	}
	if(ib != __other.ib)
	{
		return true;
	}
	if(hss != __other.hss)
	{
		return true;
	}
	if(il != __other.il)
	{
		return true;
	}
	if(is != __other.is)
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
	else if(__other.a<a)
	{
		return false;
	}
	if(b < __other.b)
	{
		return true;
	}
	else if(__other.b<b)
	{
		return false;
	}
	if(str < __other.str)
	{
		return true;
	}
	else if(__other.str<str)
	{
		return false;
	}
	if(tt < __other.tt)
	{
		return true;
	}
	else if(__other.tt<tt)
	{
		return false;
	}
	if(ib < __other.ib)
	{
		return true;
	}
	else if(__other.ib<ib)
	{
		return false;
	}
	if(hss < __other.hss)
	{
		return true;
	}
	else if(__other.hss<hss)
	{
		return false;
	}
	if(il < __other.il)
	{
		return true;
	}
	else if(__other.il<il)
	{
		return false;
	}
	if(is < __other.is)
	{
		return true;
	}
	else if(__other.is<is)
	{
		return false;
	}
	return false;
}

void Message::STest::_csg_init(){
	a=0;
	b=false;
	str="";
	tt._csg_init();
	ib.clear();
	hss.clear();
	il.clear();
	is.clear();
	
};

void Message::STest::_csg_read(CSerializeStream& __is){
	__is.read(a);
	__is.read(b);
	__is.read(str);
	tt._csg_read(__is);
	__is.read(ib);
	Message::__read(__is,hss,__STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize());
	__is.read(il);
	__is.read(is);
};

void Message::STest::_csg_write(CSerializeStream& __os)const{
	__os.write(a);
	__os.write(b);
	__os.write(str);
	tt._csg_write(__os);
	__os.write(ib);
	Message::__write(__os,hss,__STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize());
	__os.write(il);
	__os.write(is);
};

void Message::__read(csg::CSerializeStream& __is,std::vector<STestStruct>& __data,__STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		STestStruct val;
		val._csg_read(__is);
		__data.push_back(val);
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::vector<STestStruct>& __data,__STL_TYPE_ONE__Struct__STest__vector__STestStruct__hss__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::vector<STestStruct>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		(*it)._csg_write(__os);
	}
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
	mis = __other.mis;
	mss = __other.mss;
	msstring = __other.msstring;
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
	if(mis != __other.mis)
	{
		return true;
	}
	if(mss != __other.mss)
	{
		return true;
	}
	if(msstring != __other.msstring)
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
	else if(__other.a<a)
	{
		return false;
	}
	if(ii < __other.ii)
	{
		return true;
	}
	else if(__other.ii<ii)
	{
		return false;
	}
	if(il < __other.il)
	{
		return true;
	}
	else if(__other.il<il)
	{
		return false;
	}
	if(ss < __other.ss)
	{
		return true;
	}
	else if(__other.ss<ss)
	{
		return false;
	}
	if(iff < __other.iff)
	{
		return true;
	}
	else if(__other.iff<iff)
	{
		return false;
	}
	if(mis < __other.mis)
	{
		return true;
	}
	else if(__other.mis<mis)
	{
		return false;
	}
	if(mss < __other.mss)
	{
		return true;
	}
	else if(__other.mss<mss)
	{
		return false;
	}
	if(msstring < __other.msstring)
	{
		return true;
	}
	else if(__other.msstring<msstring)
	{
		return false;
	}
	return false;
}

void Message::STestMap::_csg_init(){
	a=0;
	ii.clear();
	il.clear();
	ss.clear();
	iff.clear();
	mis.clear();
	mss.clear();
	msstring.clear();
	
};

void Message::STestMap::_csg_read(CSerializeStream& __is){
	__is.read(a);
	Message::__read(__is,ii,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize());
	Message::__read(__is,il,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize());
	Message::__read(__is,ss,__STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize());
	Message::__read(__is,iff,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize());
	Message::__read(__is,mis,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize());
	Message::__read(__is,mss,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize());
	Message::__read(__is,msstring,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize());
};

void Message::STestMap::_csg_write(CSerializeStream& __os)const{
	__os.write(a);
	Message::__write(__os,ii,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize());
	Message::__write(__os,il,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize());
	Message::__write(__os,ss,__STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize());
	Message::__write(__os,iff,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize());
	Message::__write(__os,mis,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize());
	Message::__write(__os,mss,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize());
	Message::__write(__os,msstring,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize());
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,long64_t>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		long64_t val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,long64_t>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__long__ii__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<int,long64_t>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,double>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		double val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,double>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__double__il__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<int,double>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<std::string,std::string>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		std::string key;
		__is.read(key);
		std::string val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<std::string,std::string>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__string__string__ss__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<std::string,std::string>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,float>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		float val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,float>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__float__iff__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<int,float>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		__os.write(it->second);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<int,STestStruct>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		int key;
		__is.read(key);
		STestStruct val;
		val._csg_read(__is);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<int,STestStruct>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__int__STestStruct__mis__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<int,STestStruct>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		__os.write(it->first);
		it->second._csg_write(__os);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<STestStruct,STest>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		STestStruct key;
		key._csg_read(__is);
		STest val;
		val._csg_read(__is);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<STestStruct,STest>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__STest__mss__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<STestStruct,STest>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		it->first._csg_write(__os);
		it->second._csg_write(__os);
	}
};

void Message::__read(csg::CSerializeStream& __is,std::map<STestStruct,std::string>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		STestStruct key;
		key._csg_read(__is);
		std::string val;
		__is.read(val);
		__data[key]=val;
	}
};

void Message::__write(csg::CSerializeStream& __os,const std::map<STestStruct,std::string>& __data,__STL_TYPE_DOUBLE__Struct__STestMap__map__STestStruct__string__msstring__Serialize)

{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<STestStruct,std::string>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		it->first._csg_write(__os);
		__os.write(it->second);
	}
};

Message::SScapyTest::SScapyTest()
{
	_csg_init();
}

Message::SScapyTest::SScapyTest(const SScapyTest& __other)
{
	if(this==&__other)
	{
		return;
	}
	*this=__other;
}

Message::SScapyTest& Message::SScapyTest::operator=(const SScapyTest& __other)
{
	if(this==&__other)
	{
		return *this;
	}
	IMsgBase::operator=(__other);
	str = __other.str;
	return *this;
}

int Message::SScapyTest::getType()const{
	return _msgType;
}

csg::IMsgBase* Message::SScapyTest::clone()
{
	return new SScapyTest(*this);
}

bool Message::SScapyTest::operator==(const SScapyTest& __other)const
{
	return !operator!=(__other);
}

bool Message::SScapyTest::operator!=(const SScapyTest& __other)const
{
	if(this==&__other)
	{
		return false;
	}
	if(str != __other.str)
	{
		return true;
	}
	return false;
}

bool Message::SScapyTest::operator<(const SScapyTest& __other)const
{
	if(this==&__other)
	{
		return false;
	}
	if(str < __other.str)
	{
		return true;
	}
	else if(__other.str<str)
	{
		return false;
	}
	return false;
}

void Message::SScapyTest::_csg_init(){
	str="";
	
};

void Message::SScapyTest::_csg_read(CSerializeStream& __is){
	__is.read(str);
};

void Message::SScapyTest::_csg_write(CSerializeStream& __os)const{
	__os.write(str);
};

void Message::CTest::regist()
{
	csg::CMsgManager::instance()->regist(new STest());
	csg::CMsgManager::instance()->regist(new STestMap());
	csg::CMsgManager::instance()->regist(new SScapyTest());
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

void Message::CSrv_ITest_t3::response(const bool b,const std::string os)
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

void Message::CSrv_ITest_t4::response(const STestMap& os)
{
	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	SRMIReturn rmiReturn;
	rmiReturn.dispatchStatus = ERMIDispatchResultOk;
	rmiReturn.messageId = _rmiCall.messageId;

	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);

	__os->setUseBitMark(true);

	os._csg_write(*__os);

	CRpcHelper::toReturn(_session,__os);

}

void Message::CSrv_ITest_t5::response(const std::vector<long64_t>& vl)
{
	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	SRMIReturn rmiReturn;
	rmiReturn.dispatchStatus = ERMIDispatchResultOk;
	rmiReturn.messageId = _rmiCall.messageId;

	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);

	__os->setUseBitMark(true);

	__os->write(vl);

	CRpcHelper::toReturn(_session,__os);

}

void Message::CSrv_ITest_t6::response(const std::map<STest,long64_t>& vl)
{
	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	SRMIReturn rmiReturn;
	rmiReturn.dispatchStatus = ERMIDispatchResultOk;
	rmiReturn.messageId = _rmiCall.messageId;

	CRpcHelper::prepareToReturn(_session,__os,rmiReturn);

	__os->setUseBitMark(true);

	Message::__write(*__os,vl,__STL_TYPE_ONE__Interface__CSrv__ITest__t6__map__STest__long__vl());

	CRpcHelper::toReturn(_session,__os);

}

void Message::__write(csg::CSerializeStream& __os,const std::map<STest,long64_t>& __data,__STL_TYPE_ONE__Interface__CSrv__ITest__t6__map__STest__long__vl)
{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<STest,long64_t>::const_iterator it=__data.cbegin();it!=__data.cend();++it)
	{
		it->first._csg_write(__os);
		__os.write(it->second);
	}
};

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

	rmiInfo.operation="t4";
	addRMIInfo(14,rmiInfo);
	addRpcId(14);

	rmiInfo.operation="t5";
	addRMIInfo(15,rmiInfo);
	addRpcId(15);

	rmiInfo.operation="t6";
	addRMIInfo(16,rmiInfo);
	addRpcId(16);

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
		case 14:
		{
			return __t4_async(session,rmiCall,__is);
		}
		break;
		case 15:
		{
			return __t5_async(session,rmiCall,__is);
		}
		break;
		case 16:
		{
			return __t6_async(session,rmiCall,__is);
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
	try{
		t1_async(session,cb);
	}catch(const csg::CException &ex){
		cb->exception(ex);
	}catch(const std::exception& ex){
		cb->exception(ex);
	}catch(...){
		cb->exception("ExceptionCodeUnknow");
	}
	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t2_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	int a;
	__is.read(a);
	std::string s;
	__is.read(s);
	CSrv_ITest_t2_Ptr cb=new CSrv_ITest_t2();
	cb->setSession(session,rmiCall);
	try{
		t2_async(session,cb,a,s);
	}catch(const csg::CException &ex){
		cb->exception(ex);
	}catch(const std::exception& ex){
		cb->exception(ex);
	}catch(...){
		cb->exception("ExceptionCodeUnknow");
	}
	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t3_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	int a;
	__is.read(a);
	std::string s;
	__is.read(s);
	CSrv_ITest_t3_Ptr cb=new CSrv_ITest_t3();
	cb->setSession(session,rmiCall);
	try{
		t3_async(session,cb,a,s);
	}catch(const csg::CException &ex){
		cb->exception(ex);
	}catch(const std::exception& ex){
		cb->exception(ex);
	}catch(...){
		cb->exception("ExceptionCodeUnknow");
	}
	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t4_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	STestMap t;
	t._csg_read(__is);
	CSrv_ITest_t4_Ptr cb=new CSrv_ITest_t4();
	cb->setSession(session,rmiCall);
	try{
		t4_async(session,cb,t);
	}catch(const csg::CException &ex){
		cb->exception(ex);
	}catch(const std::exception& ex){
		cb->exception(ex);
	}catch(...){
		cb->exception("ExceptionCodeUnknow");
	}
	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t5_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	std::vector<STest> v;
	Message::__read(__is,v,__STL_TYPE_ONE__Interface_CSrv__Read__ITest__t5__vector__STest__v());
	CSrv_ITest_t5_Ptr cb=new CSrv_ITest_t5();
	cb->setSession(session,rmiCall);
	try{
		t5_async(session,cb,v);
	}catch(const csg::CException &ex){
		cb->exception(ex);
	}catch(const std::exception& ex){
		cb->exception(ex);
	}catch(...){
		cb->exception("ExceptionCodeUnknow");
	}
	return ERMIDispatchResultOk;

}

csg::ERMIDispatchResult Message::ITest::__t6_async(const CSessionPtr& session,const SRMICall& rmiCall,CSerializeStream& __is)
{
	std::map<std::string,STest> mss;
	Message::__read(__is,mss,__STL_TYPE_DOUBLE__Interface_CSrv__Read__ITest__t6__map__string__STest__mss());
	CSrv_ITest_t6_Ptr cb=new CSrv_ITest_t6();
	cb->setSession(session,rmiCall);
	try{
		t6_async(session,cb,mss);
	}catch(const csg::CException &ex){
		cb->exception(ex);
	}catch(const std::exception& ex){
		cb->exception(ex);
	}catch(...){
		cb->exception("ExceptionCodeUnknow");
	}
	return ERMIDispatchResultOk;

}

void Message::__read(CSerializeStream& __is,std::vector<STest>& __data,__STL_TYPE_ONE__Interface_CSrv__Read__ITest__t5__vector__STest__v)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		STest val;
		val._csg_read(__is);
		__data.push_back(val);
	}
}

void Message::__read(CSerializeStream& __is,std::map<std::string,STest>& __data,__STL_TYPE_DOUBLE__Interface_CSrv__Read__ITest__t6__map__string__STest__mss)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		std::string key;
		__is.read(key);
		STest val;
		val._csg_read(__is);
		__data[key]=val;
	}
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
	std::string os;
	__is.read(os);

	response(b,os);

}

void csg_proxy::CCli_ITest_t4::__response(CSerializeStream& __is)
{
	STestMap os;
	os._csg_read(__is);

	response(os);

}

void csg_proxy::CCli_ITest_t5::__response(CSerializeStream& __is)
{
	std::vector<long64_t> vl;
	__is.read(vl);

	response(vl);

}

void csg_proxy::CCli_ITest_t6::__response(CSerializeStream& __is)
{
	std::map<STest,long64_t> vl;
	csg_proxy::__read(__is,vl,__STL_TYPE_DOUBLE__Interface_CCli__Read__ITest__t6__map__STest__long__vl());

	response(vl);

}

void csg_proxy::__read(CSerializeStream& __is,std::map<STest,long64_t>& __data,__STL_TYPE_DOUBLE__Interface_CCli__Read__ITest__t6__map__STest__long__vl)
{
	int size=0;
	__is.readSize(size);
	for(int i=0;i<size;i++)
	{
		STest key;
		key._csg_read(__is);
		long64_t val;
		__is.read(val);
		__data[key]=val;
	}
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

void csg_proxy::ITest::t2_async(const CSessionPtr& session,const CCli_ITest_t2_Ptr& cb,const int a,const std::string s)
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

void csg_proxy::ITest::t3_async(const CSessionPtr& session,const CCli_ITest_t3_Ptr& cb,const int a,const std::string s)
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

void csg_proxy::ITest::t4_async(const CSessionPtr& session,const CCli_ITest_t4_Ptr& cb,const STestMap& t)
{
	csg::SRMICall call;
	call.rpcId=14;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	CRMIObjectBindPtr objectBind=NULL;
	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);

	__os->setUseBitMark(true);
	t._csg_write(*__os);

	CRpcHelper::toCall(session,__os,objectBind);

}

void csg_proxy::ITest::t5_async(const CSessionPtr& session,const CCli_ITest_t5_Ptr& cb,const std::vector<STest>& v)
{
	csg::SRMICall call;
	call.rpcId=15;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	CRMIObjectBindPtr objectBind=NULL;
	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);

	__os->setUseBitMark(true);
	csg_proxy::__write(*__os,v,__STL_TYPE_ONE__Interface_CCli__Write__ITest__t5__vector__STest____v());

	CRpcHelper::toCall(session,__os,objectBind);

}

void csg_proxy::ITest::t6_async(const CSessionPtr& session,const CCli_ITest_t6_Ptr& cb,const std::map<std::string,STest>& mss)
{
	csg::SRMICall call;
	call.rpcId=16;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());
	CRMIObjectBindPtr objectBind=NULL;
	CRpcHelper::prepareToCall(session,__os,call,cb,objectBind);

	__os->setUseBitMark(true);
	csg_proxy::__write(*__os,mss,__STL_TYPE_DOUBLE__Interface_CCli__Write__ITest__t6__map__string__STest__mss());

	CRpcHelper::toCall(session,__os,objectBind);

}

void csg_proxy::__write(CSerializeStream& __os,const std::vector<STest>& __data,__STL_TYPE_ONE__Interface_CCli__Write__ITest__t5__vector__STest____v)
{
	int size=__data.size();
	__os.writeSize(size);
	for(int i=0;i<size;i++)
	{
		__data[i]._csg_write(__os);
	}
}

void csg_proxy::__write(CSerializeStream& __os,const std::map<std::string,STest>& __data,__STL_TYPE_DOUBLE__Interface_CCli__Write__ITest__t6__map__string__STest__mss)
{
	int size=__data.size();
	__os.writeSize(size);
	for(std::map<std::string,STest>::const_iterator it=__data.cbegin();it!=__data.end();++it)
	{
		__os.write(it->first);
		it->second._csg_write(__os);
	}
}


