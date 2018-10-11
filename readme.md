##非md语法 直接阅读即可	ORG

###关于服务器选择
本次测评采用ubuntu server 也可采用ubuntu desktop 方便管理
(没有专业的运维人员建议采用ubuntu 至于desktop还是server 操作简单选desktop)
有能力可上centos

###关于测评步骤
本次测评采用ubuntu-18.04-server-x64 
所需大部分资源可在Souce文件夹下找到(基本没有源码安装(-_-) 也是选择ubuntu的一个理由ORG) 也可自行下载
执行步骤记录在Source/action里

###关于单机模式和集群模式 
目前主要负责单服务器模式
如果需要多台服务器集群并发 可以提出需求

###关于emq插件
emq插件编写需要erlang基础

emq插件理论上支持热配置(即随改随用，不影响客户端连接) 
可以使用  ./bin/emqttd_ctl plugins load <emq_plugin_name> 来加载 ( 注： <emq_plugin_name>::= emq_auth_username .... )
也可以直接使用dashboard来加载配置
但经过实际测试发现有些配置在更改后不能立即启用
存在一定的延时 可能3-5分钟也可能很长，所以可能需要重新配置emq
./bin/emqttd stop
rm -rf data/mnesia/*
rm -rf data/configs/*
rm -rf log/*
./bin/emqttd start
经过上述步骤emq插件即可加载，但是会重置登录dashboard的登录用户名和密码为admin:public (注： 此登录名和密码与http Acl无关)

####关于WebSocket客户端(Paho.Client)
WebSocket客户端需求不大，可以采用dashboard里内置的websocket客户端
如有需求，可以参考当前目录下WebSocket目录里的index.html (注：该Demo采用Paho.Mqtt.Client实现）只是简单的demo
(只是为了节省大家看文档的时间，我刚看文档时一脸崩溃，js文件专业不对口ORG)
建议采用Firefox或chrome浏览器打开index.html 按f12切到控制台与index.html里的代码进行比对 可以大致了解程序结构
也可联系Author讨论相关主题


####关于http请求
http请求采用curl发送
具体可参考curl文档


####关于javascript FileApi
文件上传采用js FileApi 以post/get请求方式发送保存到服务器(可不保存至服务器直接发送，现采用先上传到服务器)，后端处理请求程序
由php编写 服务器端结构为nginx + php 
(后续可自行更改）基本文件在Upload文件夹下 可参考Source文件夹下的action.md来执行



####客户端和代理服务端编程 采用Qt5.11.2 低版本qt可能需要自行移植mqtt(后发现5.11.2还是需要自己编译)
##源代码地址 git clone https://codereview.qt-project.org/qt/qtmqtt （注 ：直接在github上下载的是有问题的 别踩坑了）
可根据该qt官方文档源码改编，也可根据我给出的Demo改编，有需求可联系
也可自行寻找客户端框架 如Paho等一系列优秀框架(具体需要自行研究)
本(core server； gui client) add mysql
过程中出现找不到 libmysqlclient.so.18 的问题 
(
解决方案 是下载依赖
wget http://launchpadlibrarian.net/212189159/libmysqlclient18_5.6.25-0ubuntu1_amd64.deb
sudo dpkg -i libmysqlclient18_5.6.25-0ubuntu1_amd64.deb
[也可尝试直接移植libmysqlclient.so.18到相关目录 经测试可行]
注、该 deb文件 以及 libmysqlclient.so.18 已下载在Source文件夹中
)
远程连接mysql需要mysql设置处开启外部访问权限，否则无法连接上数据库 具体设置在action.md中已经给出
相关建表语句模板已给出 (Clients/table_template) 供参考




