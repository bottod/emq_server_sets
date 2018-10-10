## 2018.10.10_15:20   coding now please wait !!
####环境设置
## env 文件夹内的是客户端所需要的库文件 
## 为了让程序能找到库文件 可以将该文件夹放于指定位置后 
## 在/etc/ld.so.conf.d/内新建一个文件 如 qt_mqtt_env.conf
## 操作： sudo vim /etc/ld.so.conf.d/qt_mqtt_env.conf   将该文件夹的位置写入该conf内 保存退出 sudo ldconfig
####软件说明
## mqtt_c 是带gui的客户端 和一般网上的客户端一样的功能
## mqtt_s 是不带gui的fake_server 其是专门放在服务器上的客户端
## 
## 2018.10.10_16:18 
## 两个客户端功能还不完善 用作参考Demo
