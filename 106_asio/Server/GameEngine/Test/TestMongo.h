#ifndef _TEST_TEST_MONGO_H_
#define _TEST_TEST_MONGO_H_

#include "mongo/client/dbclient.h"
#include "engine/def/environment_def.h"
#include "mongo/bson/bsonobjbuilder.h"




using namespace mongo;

void run()
{	

	mongo::client::initialize();

	mongo::DBClientConnection conn;
	conn.connect("127.0.0.1:27017");

	std::string errMsg;


	//conn.createCollection("guang");
	
	BSONObj p = BSONObjBuilder().append("name", "guang").append("age", "26").obj();
	
	std::string dbName = "guang_test";
	std::string collection = "testCollection";
	std::string tdb = dbName + "."+collection;

	conn.insert(tdb, p);

	conn.insert(tdb, p);

	conn.insert(tdb, p);

	//create databases

	conn.createCollection("hello");
	BSONObj p1 = BSONObjBuilder().append("hello", "p1").obj();
	
	

	
}




void testMongo() {
	
#ifdef CSG_WIN
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		return ;
	}
#endif

	try
	{
		run();
		LogInfo("conn ok");
	}
	catch (const mongo::DBException &e)
	{
		LogErr("caught " << e.what() );
	}
	getchar();
	return ;

	
}












#endif
