# GMT-mini-GUI

## 下载地址
https://github.com/CovMat/GMT-mini-GUI/releases

## 注意事项
使用本工具前请先在您的系统中安装好GMT，版本最低要求为5.4。
如果想自行编译源代码，请使用Qt 5.13版。已知Qt 5.14版存在bug，无法编译。

## 运行方法
### windows
windows版直接双击运行exe即可
### Linux
如果执行'sh ./GMT-GUI.sh'无法运行成功的话，建议将库文件的路径添加至环境变量中。
具体做法为在~/.bashrc或~/.zshrc中添加"export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:(GMTGUI-LINUX库文件的路径)
------------

##致谢
感谢@SeisSpath协助编译了Linux版本并进行了大量测试，给出了修改意见。感谢@yjmzj、@seisman为软件修改提出的宝贵意见。