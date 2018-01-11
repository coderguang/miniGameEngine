#!/bin/bash
#***********************************************
#
#      Filename: generateCsg.sh
#
#      Author: royalchen 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#
#     Create: 2017-09-16 11:36:05
#     Last Modified: 2017-09-16 11:36:05
#***********************************************
inputfile=$1
if [ -z  $inputfile ] ; then
	./../tools/csgl Message/ ../../Server/GameEngine/Message/ TestStruct
else
	echo "input file is $inputfile"
	./../tools/csgl Message/ ../../Server/GameEngine/Message/ $inputfile
fi

outputfile=../../Server/GameEngine/Message

#svn add $outputfile/*.h $outputfile/*.cpp
#svn commit -m "update message file by csgl" $outputfile
