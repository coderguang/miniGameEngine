bison -d -t --verbose csgl.y
g++ -c csgl.tab.c -std=c++11 -lstdc++
flex csgl.l 
mv -f lex.yy.c csgl.yy.c
g++ -c -g -w csgl.yy.c 
g++ -g -w csgl.tab.o csgl.yy.o -o ..\..\..\..\Public\tools\csgl.exe
pause