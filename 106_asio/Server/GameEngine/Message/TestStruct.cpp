#include "TestStruct.h"
#include "engine/rpc/rpcHelper.h"
using namespace csg;
using namespace Message;

void Message::_csg_write(CSerializeStream& __os,ETestStruct __enumType){
	__os.write(static_cast<byte_t>(__enumType));
}

void Message::_csg_read(CSerializeStream& __is,ETestStruct& __enumType){
	byte_t value;
	__is.read(value);
	__enumType=static_cast<ETestStruct>(value);
	if(__enumType>5||__enumType<1)
	{
		throw CException("ExceptionCodeSerialize",ExceptionCodeSerialize);
	}
}

Message::STestStruct::STestStruct()
{
	_csg_init();
}

Message::STestStruct::STestStruct(const STestStruct& __other)
{
	if(this==&__other)
	{
		return;
	}
	*this=__other;
}

Message::STestStruct& Message::STestStruct::operator=(const STestStruct& __other)
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

int Message::STestStruct::getType()const{
	return _msgType;
}

csg::IMsgBase* Message::STestStruct::clone()
{
	return new STestStruct(*this);
}

bool Message::STestStruct::operator==(const STestStruct& __other)const
{
	return !operator!=(__other);
}

bool Message::STestStruct::operator!=(const STestStruct& __other)const
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

bool Message::STestStruct::operator<(const STestStruct& __other)const
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

void Message::STestStruct::_csg_init(){
	a=0;
	b=false;
	str="";
	ib.clear();
	
};

void Message::STestStruct::_csg_read(CSerializeStream& __is){
	__is.read(a);
	__is.read(b);
	__is.read(str);
	__is.read(ib);
};

void Message::STestStruct::_csg_write(CSerializeStream& __os)const{
	__os.write(a);
	__os.write(b);
	__os.write(str);
	__os.write(ib);
};

void Message::CTestStruct::regist()
{
	csg::CMsgManager::instance()->regist(new STestStruct());
}


