set NAME=csgl
set NAME_EX=csgl2cpp
set CC=g++
set TOOL_PATH=..\..\..\..\Public\tools\
set CFLAG= -c -g -w

bison -d -t --verbose %NAME%.y
@If errorlevel 1 (
    pause
) 
%CC% %CFLAG% %NAME%.tab.c -std=c++11 -lstdc++ -I.
@If errorlevel 1 (
    pause
) 
flex -o%NAME%.yy.c %NAME%.l 
@If errorlevel 1 (
    pause
) 
%CC% %CFLAG% %NAME%.yy.c  -I.
@If errorlevel 1 (
    pause
) 

::for json file
%CC%  %CFLAG% -o ./json/json_value.o ./json/json_value.cpp 
%CC%  %CFLAG% -o ./json/json_reader.o ./json/json_reader.cpp 
%CC%  %CFLAG% -o ./json/json_writer.o ./json/json_writer.cpp


%CC% -g -w %NAME%.tab.o %NAME%.yy.o json/json_value.o json/json_reader.o json/json_writer.o -o %TOOL_PATH%%NAME_EX%.exe
@If errorlevel 1 (
    pause
) 