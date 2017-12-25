1. 首先下载unxutils压缩包 http://sourceforge.net/search/?type_of_search=soft&words=unxutils&search=Search
2.把压缩包解压到一个文件夹，例如我的解压包放在  E:/compiler/UnxUtils下
3.配置环境变量。分别把unxtils下的lib与wbin两个子文件夹路径添加到环境变量path中。
	a.在控制台上输入命令：
		path=%path%; E:/compiler/UnxUtils/usr/local/lib
		path=%path%; E:/compiler/UnxUtils/usr/local/wbin
	b.直接在“系统属性”的环境变量上配置。
4.在解压包中的E:/compiler/UnxUtils/usr/local/share下有两个文件，bison.hairy，bison.simple，为这两个文件建立两个环境变量。（Administrator的用户变量）
变量				值
bison_hairy      E:/compiler/UnxUtils/usr/local/share/bison.hairy      （注意变量名称必须为 bison_hairy）
bison_simple    E:/compiler/UnxUtils/usr/local/share/bison.simple   （注意变量名称必须为 bison_simple）
 
至此万事俱备，我们可以开始两个简单的文件来测试一下。
1.新建文本文件，更改名称为lex.l，敲入下面代码
%{
int yywrap(void);
%}
%%
%%
int yywrap(void)
{
	return 1;
}
2.新建文本文件，更改名称为yacc.y,敲入下面代码
 
%{
void yyerror(const char *s);
%}
%%
program:
       ;
%%
void yyerror(const char *s)
{
}
int main()
{
        yyparse();
        return 0;
} 
我们暂且不讨论上面代码的意思。
打开控制台，进入到刚才所建立文件（lex.l,yacc.y）所在的文件夹。
1.输入 flex lex.l
2.输入 bison yacc.y
如果我们看到当前文件夹上多了两个文件（yacc.tab.c，lex.yy.c），那么说明lex&&yacc已经安装配置成功，接下来就好好享受这两个小工具的魅力吧。
 
问题：
1.在控制台输入 flex lex.l时，提示" 'flex' 不是内部命令或外部命令，也不是可运行的程序或批处理文件"则说明环境变量的path设置不正解。
2.在控制台输入 bison yacc.y时，提示“bison : /usr/local/share/bison.simple: No such file or directory ”最有可能是上面“Administrator的用户变量”中变量的名称设置不正确（必须为bison_simple）.