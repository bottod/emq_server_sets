## 2018.10.10_15:20   coding now please wait !!
#### 环境设置：

## env 文件夹内的是客户端所需要的库文件 
## 为了让程序能找到库文件 可以将该文件夹放于指定位置后 
## 在/etc/ld.so.conf.d/内新建一个文件 如 qt_mqtt_env.conf
## 操作： sudo vim /etc/ld.so.conf.d/qt_mqtt_env.conf   将该文件夹的位置写入该conf内 保存退出 sudo ldconfig
#### 软件说明：

## mqtt_c 是带gui的客户端 和一般网上的客户端一样的功能
## mqtt_s 是不带gui的fake_server 其是专门放在服务器上的客户端
<>

## 2018.10.10_16:18 
## 两个客户端功能还不完善 用作参考Demo

## 2018.10.11_12:27 功能相对完善 做为server端够用了
!!!!!
本测试用程序要测试通过见下文 也可自行改代码 代码并不长
必须保证的点：(举例说明)
假如你的conf/subscribe.conf里其中一行是 /temperature
数据库名必须是mq_playground
创建用户名mq_admin 密码mq_password
数据表名必须 mq_ 开头,后面跟conf里的'/'后的内容 (例子中为mq_temperature)
按照建表模板(table_template)创建数据表 ctime可改 主列名必须是conf里的'/'后的内容 (例子中为temperature)
!!!!!

<>
由于之前本地构建 固定了本机IP
现更新一个localhost版本mqtt_s 直接替换原来的即可
版本置于fix/IPname_localhost目录下

#### 2018.10.11_16:51 删除fix文件夹 更新release 解压即用  给出打包脚本 pack.sh



