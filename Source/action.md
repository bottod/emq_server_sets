## 写在开头 local_server: 172.16.163.134
>  	本文一切从简 能用包管理工具直接安装的绝不用源码安装 ORG
> 如果有源码安装需求也可自行操作





#### 换源 
> source.list已经给出 替换掉/etc/apt/source.list	(需要root权限)
> sudo apt-get update
> sudo apt-get upgrade





#### 安装nginx
> sudo apt-get install nginx

#### nginx相关
--------------------------------------------------------------------
> nginx -h 可查看帮助文档
> (关于nginx启停)
> sudo service nginx start    <==>    sudo nginx -s start
> sudo service nginx stop    <==>    sudo nginx -s stop
> sudo service nginx restart    <==>    sudo nginx -s restart
> sudo service nginx reload    <==>    sudo nginx -s reload

> --------------------------------------------------------------------
> ####  基本配置
> nginx 安装完可以适当优化，也可以不优化 这里稍加修改
> (由于之后还要配置php等，之后将配置放在source文件夹下 可根据需要自行修改)
>
> #### 安装php7.2以及相关扩展
> sudo apt-get install php7.2 php7.2-fpm
> sudo apt-get install php7.2-mysql php-pear php7.2-curl php7.2-json php7.2-cgi
> __关闭php文件解析漏洞 __
> sudo vim /etc/php/7.2/fpm/php.ini
> 键入 /;cgi.fix_pathinfo=1
> 找到该条将其修改为
> cgi.fix_pathinfo=0
> 该条前的分号也需要删除
> 重启服务
> sudo service php7.2-fpm restart
>
> #### 开启nginx解析php 
>
> -------------------------------------------------------
> _只需在server里加入:_
> ```
> location ~ \.php$
>     {
>         include snippets/fastcgi-php.conf;
>         fastcgi_pass unix:/var/run/php/php7.2-fpm.sock;
>     }
> ```
> --------------------------------------------------------
	这里我的步骤是(避免直接修改default 当然你可以直接修改default 甚至可以直接修改/etc/nginx/nginx.conf 这样做只是方便管理)	
sudo cp /etc/nginx/sites-available/default /etc/nginx/sites-available/php_supportt
sudo vim /etc/nginx/sites-available/php_supportt
__适当修改 即上面提到的在server中加入的东西__
sudo rm /etc/nginx/sites-enabled/default
sudo ln -s /etc/nginx/sites-available/php_supportt /etc/nginx/sites-enabled/php_supportt
__php_support和nginx.conf已经给出__
_测试nginx解析php以及连接mysql数据库；_mysql安装在下面(这里测试 用户名root 密码jack)
根据php_support的设置可知网站根目录为 /var/www/html
我们新建一个index.php 放在根目录下 写上相关测试代码用于测试
__index.php已经给出__





#### 安装emqx 3.0 | dashboard端口18083 | admin/public
> wget -O emq.deb http://emqtt.com/downloads/latest/ubuntu16_04-deb
> sudo dpkg -i emq.deb 
> __关于启停__
> sudo service emqx start
> sudo service emqx stop
> __关于emq优化__
> 相关部分可参阅About文件夹下的相关文档
> /etc/emqx
> __关闭匿名认证 __
> 在/etc/emqx/emq.conf中找到mqtt.allow_anonymous = true 设为false即可
> mysql鉴权按照About下的文档来





#### 安装mysql5.7.23 并做适当配置
> sudo apt-get install mysql-server mysql-common mysql-client libmysqlclient-dev
> __修改mysql默认字符集__
> sudo vim /etc/mysql/my.cnf

> --------------------------------------
> __添加如下： 也可以直接使用source文件夹下的my.cnf__

> ```
> [mysqld]
> collation-server = utf8_unicode_ci
> init-connect='SET NAMES utf8'
> character-set-server = utf8
> ```
> ---------------------------------------
> sudo service mysql restart	##也能以非root权限运行
----------------------------------------
> __修改root用户密码__
> sudo mysql -u root 
> DROP USER 'root'@'localhost';
> CREATE USER 'root'@'%' IDENTIFIED BY 'jack';     ##最后的引号内为密码
> GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
> FLUSH PRIVILEGES;
> _为方便管理mysql 可以讲sql_desk.php至于网页根目录下，即可网页控制数据库(前提是配置好php环境)_
> sql_desk.php已经给出，可根据需求更改名字确保无安全隐患
> __开启mysql的外部访问权限__
> sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
> 找到 bind-address = 127.0.0.1
> 将其改为 #bind-address = 127.0.0.1  即注释掉
> 重启mysql 
> sudo service mysql restart
> 重新以root身份登录mysql更新权限 （mysql -uroot -p）
> FLUSH PRIVILEGES;

~~interactive_timeout=31536000~~
~~wait_timeout=31536000~~


#### 关于文件上传
> 可以参考Upload文件夹下的文件 将Upload文件夹下的所以东西置于nginx根目录下 (/var/www/html)
> 其中给upload文件夹加权限(chmod +777 upload)以让php可以存储上传的文件
> 注: 由于上传的是固件文件 不允许出现 '中文字符' 会出现乱码问题





