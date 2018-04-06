windows 下用于输出exe文件所依赖的库文件
dumpbin.exe /DEPENDENTS **.exe

1，查看导出接口：

        tape :    dumpbin -exports dll文件全路径

2，查看导入接口：

        tape :    dumpbin -imports dll文件全路径