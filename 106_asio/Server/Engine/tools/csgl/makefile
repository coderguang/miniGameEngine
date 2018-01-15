
##############################for csgl##################################
OBJ	:= csgl
TOOLS_DIR	:=../../../../Public/tools/
SRCC_LEX	:=$(OBJ).yy.c
SRCC_YACC	:=$(OBJ).tab.c
SRCH_YACC	:=$(OBJ).tab.h
SRCO_LEX	:=$(OBJ).yy.o
SRCO_YACC	:=$(OBJ).tab.o
SRCH_CSGL	:=csgl.hpp
SRCL	:=$(OBJ).l	
SRCY	:=$(OBJ).y
CC	:= clang++
CFLAGS	:= -std=c++11 -lstdc++ -D _Debug -g -w -I. -D _CSG_LINUX_
LIBS	:=
LEX	:= flex
YACC :=bison

##############################for json##################################

#set file dir 
SEARCH_FILE	= $(wildcard $(subdir)/*.h $(subdir)/*.cpp)
CUR_SRC_DIR	= $(shell ls -AxR $(PROJECT_DIR)|grep ":"|tr -d ':')
CUR_SRC 	:= $(foreach subdir,$(CUR_SRC_DIR),$(SEARCH_FILE))
CUR_H		:= $(filter %.h, $(CUR_SRC))
CUR_CPP 	:= $(filter %.cpp, $(CUR_SRC))
CUR_CPP_DIR	:= $(dir $(CUR_CPP))
CUR_CPP_DIR	:= $(sort $(CUR_CPP_DIR))
CUR_H_DIR	:= $(dir $(CUR_H))
CUR_H_PRE	:= $(addprefix -I,$(CUR_H_DIR))

#set obj dir
CUR_OBJ		:=$(strip $(CUR_CPP:.cpp=.o))
CUR_OBJ_EX	:=$(patsubst %.o,%,$(CUR_OBJ))
CUR_DEP		:=$(strip $(CUR_CPP:.cpp=.d) $(CUR_H:.h=.d))


define build_obj
$1:$2
	$(CC) -c $(CFLAG) -o $1 $2 
endef

define build_dep
$2:$1
	$(CC) $(CFLAG) -MM $1 >$2
endef


$(foreach tmp,$(CUR_OBJ_EX),$(eval $(call build_dep,$(tmp).cpp,$(tmp).d)))

$(foreach tmp,$(CUR_OBJ_EX),$(eval $(call build_obj,$(tmp).o,$(tmp).cpp)))

#######################################build##################################

.PHONY:all
all:$(OBJ)

$(OBJ):$(SRCO_YACC) $(SRCO_LEX) $(CUR_OBJ)
	$(CC) $(CFLAGS) $^ -o $(TOOLS_DIR)$@ $(LIBS)
	
$(SRCO_LEX):$(SRCC_LEX) $(SRCH_CSGL)
	$(CC) -c $(CFLAGS) $< $(LIBS)

$(SRCO_YACC):$(SRCC_YACC) $(SRCH_CSGL)
	$(CC) -c $(CFLAGS) $< $(LIBS)

$(SRCC_YACC) $(SRCH_YACC):$(SRCY)
	$(YACC) -d -t --verbose $^


$(SRCC_LEX):$(SRCL)
	$(LEX) -o $@ $^ 

	
.PHONY:clean
clean:
	rm -rf $(CUR_OBJ) $(OBJ) $(SRCC) *.h *.c *.o core.* *.output *.gch *.cpp json/json_value.o json/json_reader.o json/json_writer.o

.PHONY:cleanobj
cleanobj:
	rm -rf *.o

