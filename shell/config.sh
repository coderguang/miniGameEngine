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


VERSION=106_asio

BUILD_ROOT_DIR=/home/guang/GameWorld

PRO_ROOT_DIR=$BUILD_ROOT_DIR/$VERSION/Server

SHELL_ROOT_DIR=$BUILD_ROOT_DIR/shell

BIN_DIR=$PRO_ROOT_DIR/runnable/
LIB_DIR=$PRO_ROOT_DIR/lib/

CC="clang++"

#lib build params
LIB_CFLAG="-std=c++11 -g -D _DEBUG -rdynamic -I. -I$PRO_ROOT_DIR/Engine"

#bin build params
BIN_CFLAG="-std=c++11 -lstdc++ -g -D _DEBUG -rdynamic -L../../lib -L../../../../lib/linuxlib/mongodb-c++-driver -L../../../../lib/linuxlib/boost -I. -I../../Engine/ -I../../../../lib/include -I../Message"

LIBS="-lMessage -lEngine -lmongoclient -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -lboost_regex -lboost_program_options"

PRO_GAME_ENGINE_DIR=$PRO_ROOT_DIR/GameEngine

arr_lib=(Message)

arr_bin=(Test)


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

