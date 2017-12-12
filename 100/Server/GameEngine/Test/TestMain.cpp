#ifndef _TEST_TEST_MAIN_H_
#define _TEST_TEST_MAIN_H_

#include "framework/counter/counterHandler.h"
#include "engine/def/csg_def.h"
#include "engine/serialize/serializestream.h"
#include "TestSerialize.h"
#include "TestThread.h"


#include <iostream>


int main(int argc, char** argv){

	int k = 0;
	std::cout << "hello";

	testCounter(5);

	//testSerialize();

	system("pause");
}

#endif