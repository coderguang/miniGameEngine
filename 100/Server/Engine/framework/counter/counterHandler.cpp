#include "framework/counter/counterHandler.h"
#include "framework/io/IOHandler.h"
#include <strstream>
#include "framework/counter/counterHandlerManager.h"
#include "engine/lock/lockObjectManager.h"
#include <iostream>


using namespace csg;


CCounterHandler::CCounterHandler(const std::string& name)
:_name(name) 
{
	_count = 0;
	_countEx = 0;
	CCounterHandlerManager::registCounterHandler(this);
}
CCounterHandler::~CCounterHandler()
{
	CCounterHandlerManager::removeCounterHandler(this);
}

void CCounterHandler::increaseCount(int add)
{
	_count += add;
}
void CCounterHandler::decreaseCount(int dec)
{
	_count -= dec;
}

void CCounterHandler::increaseCountEx(int add)
{
	_countEx += add;
}
void CCounterHandler::decreaseCountEx(int dec)
{
	_countEx -= dec;
}

void CCounterHandler::print(IIOHandler* handle)
{
	std::strstream stream;
#ifdef _DEBUG
	stream << "counter address:" << this << ",io address" << handle;
#endif
	stream <<"CounterHandlerName:" << _name << "_count:" << _count << ",_countEx:" << _countEx;

	handle->write(stream.str() ,stream.pcount() ,NULL);
	stream.freeze(false);
}

#ifdef _DEBUG

void CCounterHandler::print()
{
	CAutoLock l(CLockObjectManager::getSingletonLock());
	std::cout << "CounterHandlerName:" << _name << "_count:" << _count << ",_countEx:" << _countEx << std::endl;;
	std::cout.flush();
}

#endif