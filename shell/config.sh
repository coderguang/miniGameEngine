#shell
#***********************************************
#
#      Filename: config.sh
#
#      Author: royalchen 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#

#     Create: 2017-12-20 20:05:19
#     Last Modified: 2017-12-20 20:05:19
#***********************************************

cd ../
# pwd

BUILD_ROOT_DIR=$(cd "$(dirname "$0")";pwd)

cd shell

VERSION=109

PRO_ROOT_DIR=$BUILD_ROOT_DIR/$VERSION/Server

SHELL_ROOT_DIR=$BUILD_ROOT_DIR/shell

BIN_DIR=$PRO_ROOT_DIR/runnable/
LIB_DIR=$PRO_ROOT_DIR/lib/

CC="clang++"
CCEX="clang"

#lib build params
LIB_CFLAG="-std=c++11 -MMD -MP -g -D NDEBUG -I. -I../../../lib/include -I../../../../lib/include -I$PRO_ROOT_DIR/Engine"

LIB_CFLAG_EX=" -MMD -MP -g -D NDEBUG -I -I$PRO_ROOT_DIR/Engine -I../../../lib/include -I../../../../lib/include"

#bin build params
BIN_CFLAG="-std=c++11 -MMD -MP -lstdc++ -g -D NDEBUG -L../../lib -L../../../../lib/linuxlib/mongodb-c++-driver -L../../../../lib/linuxlib/boost -I. -I../../Engine/ -I../../../../lib/include -I../Message"

LIBS="-lMessage -lEngine -lmongoclient -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -lboost_regex -lboost_program_options"

#build with static 

STATIC_LIBS="-lMessage -lEngine -lmongoclient ../../../../lib/linuxlib/boost/libboost_thread.a ../../../../lib/linuxlib/boost/libboost_system.a ../../../../lib/linuxlib/boost/libboost_filesystem.a ../../../../lib/linuxlib/boost/libboost_date_time.a ../../../../lib/linuxlib/boost/libboost_regex.a ../../../../lib/linuxlib/boost/libboost_program_options.a -lMessage -lEngine -lmongoclient -lpthread"





PRO_GAME_ENGINE_DIR=$PRO_ROOT_DIR/GameEngine

arr_lib=(Message)

arr_bin=(Test)


test -d $BIN_DIR||mkdir -p $BIN_DIR
test -d $LIB_DIR||mkdir -p $LIB_DIR

############################dont change below code################

#color def
BLACK="\e[33;0m"
RED="\e[31;1m"
GREEN="\e[32;1m"
YELLOW="\e[33;3m"
BLUE="\e[34;1m"
PURPLE="\e[35;1m"
CYAN="\e[36;1m"
WHITE="\e[37;1m"

