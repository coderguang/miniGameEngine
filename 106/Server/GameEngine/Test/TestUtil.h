#ifndef _TEST_TEST_UTIL_H_
#define _TEST_TEST_UTIL_H_

#include "framework/util/sysUtil.h"
#include "framework/json/value.h"

void processNum()
{
	int num = csg::CSysUtil::getNumberOfProcessors();
	LogDebug("core=" << ToStr(num));
}



void testUtil()
{ 
	processNum();
}

class testStaticDesconstructor
{
public:
	testStaticDesconstructor(std::string n):name(n)
	{
		std::cout << "test StaticDesconstructor:" << name << " is be constructor" << std::endl;
	}
	~testStaticDesconstructor()
	{
		std::cout << "test StaticDesconstructor:" << name << " is be desconstructor" << std::endl;
	}
private:
	std::string name;
};

class testStatic
{
public:
	testStatic(std::string n):name(n)
	{
		std::cout << "testStatic:" << name << " is be constructor" << std::endl;
	}
	~testStatic()
	{
		std::cout << "testStatic:" << name << " is be desconstructor" << std::endl;
	}
private:
	std::string name;
	static testStaticDesconstructor test;
};

//testStaticDesconstructor testStatic::test("testStatic");

class testStaticNotStaticMember
{
public:
	testStaticNotStaticMember(std::string n) :name(n),test("testStaticNotStaticMember")
	{
		std::cout << "testStaticNotStaticMember:" << name << " is be constructor" << std::endl;
	}
	~testStaticNotStaticMember()
	{
		std::cout << "testStaticNotStaticMember:" << name << " is be desconstructor" << std::endl;
	}
private:
	std::string name;
	testStaticDesconstructor test;
};

void testStaticDesconstructorWithStatic(Json::Value& js)
{
	std::cout << "start ......." << std::endl;;
	testStatic("testStatic");
	std::cout << "end.........." << std::endl;
}

void testStaticDesconstructorNotStatic(Json::Value& js)
{
	std::cout << "start ......." << std::endl;
	testStaticNotStaticMember("testStaticNotStaticMember");
	std::cout << "end.........." << std::endl;
}


void onlyQforExitFunc()
{
	char ch;
	do
	{
		LogDebug("only q exit this function")
		ch = cin.get();
		if('\n'==ch || ' '==ch )
			continue;
		if ( 'q' == ch )
			break;
	} while ( true );
}


#endif