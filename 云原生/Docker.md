# 概述

官网：https://www.docker.com/

文档：https://docs.docker.com/

windows安装wsl：https://docs.microsoft.com/zh-cn/windows/wsl/install-manual

容器化技术，隔离

**Docker的作用**

传统：开发jar一套环境，上线运维一套环境，配置环境麻烦

现在：开发打包部署上线，一套流程做完

**更快速的交付部署，更便捷的升级扩容，更简单的系统运维，更高效的资源利用**



**Docker与传统虚拟机**

VM用的原生镜像，很笨重（几G），需要虚拟出硬件；Docker有比VM更少的抽象层，只有最重要的核心（几M），十分小巧，秒级启动

<img src="http://mdimg.sofice.top/202112131031861.png" alt="image-20211213103119636" style="zoom: 50%;" />







## 架构

Docker 使用客户端-服务器架构。 Docker 客户端与 Docker 守护进程对话，后者负责构建、运行和分发 Docker  容器的繁重工作。 Docker 客户端和守护程序可以运行在同一系统上，或者您可以将 Docker 客户端连接到远程 Docker 守护程序。  Docker 客户端和守护进程使用 REST API、UNIX 套接字或网络接口进行通信。另一个 Docker 客户端是 Docker  Compose，它允许您使用由一组容器组成的应用程序。

<img src="http://mdimg.sofice.top/202112131031885.svg+xml" alt="Docker Architecture Diagram" style="zoom:67%;" />

**Docker 守护进程 (dockerd)** 

侦听 Docker API 请求并管理 Docker 对象，例如图像、容器、网络和卷。守护进程还可以与其他守护进程通信以管理 Docker 服务。

**Docker 客户端 (docker)** 

是许多 Docker 用户与 Docker 交互的主要方式。当您使用诸如 docker run  之类的命令时，客户端会将这些命令发送到 dockerd，后者会执行这些命令。 docker 命令使用 Docker API。 Docker  客户端可以与多个守护进程通信。



**镜像（image）**

镜像是一个只读模板，包含创建 Docker 容器的说明。通常，一个镜像基于另一个镜像，并带有一些额外的自定义配置。例如，可以构建一个基于 ubuntu 的镜像，然后安装 Apache Web 服务器和应用程序，产生应用程序运行所需的环境。

**容器（container）**

容器是图像的可运行实例。您可以使用 Docker API 或 CLI 创建、启动、停止、移动或删除容器。您可以将容器连接到一个或多个网络，为其附加存储，甚至可以根据其当前状态创建新镜像。

默认情况下，容器与其他容器及其主机相对隔离。可以控制容器的网络、存储或其他底层子系统与其他容器或主机之间的隔离程度。当容器被移除时，未存储在持久存储中的对其状态的任何更改都会消失。

**仓库（repository）**

存放镜像的地方



## 镜像原理

**UnionFS（联合文件系统）**：分层，轻量级，高性能的文件系统。镜像可以通过分层来继承。

**bootfs（boot file system）**：包含boot加载器（bootloader）和内核（kernel），在镜像最低层，当boot加载完成后整个内核都在内存中，此时内存使用权移交给内核，卸载bootfs

**rootfs（root file system）**：在bootfs之上，包含典型linux系统目录 /dev，/bin 等，rootfs就是各个不同操作系统的发行版



镜像创建成容器后，包含bootfs和rootfs基础镜像，以及若干个上层父镜像（jdk，tomcat等），都是只读。在镜像中的所有操作会加到容器中，形成一个新的镜像层。

![u=348641656,2996583845&fm=26&fmt=auto](http://mdimg.sofice.top/202112151623470.png)



# 使用

安装

```bash
sudo yum install docker-ce docker-ce-cli containerd.io --allowerasing
```

启动

```bash
sudo systemctl start docker
docker run hello-world
```

配置镜像加速器

https://cr.console.aliyun.com/cn-hangzhou/instances/mirrors

```bash
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://1gddto4h.mirror.aliyuncs.com"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```

docker目录：`/var/lib/docker`

## 命令

```bash
# 系统
docker -v				查看版本
docker info 			查看信息
docker ps				列出所有运行的容器
	-a					历史运行过的
	-q					只显示编号

# 镜像
docker images 			查看本地镜像 -a所有 -q只显示id
docker search 			在仓库里搜索镜像
docker pull     		镜像名[:版本号] 下载镜像
docker rmi 镜像名		  删除镜像
# 容器
docker run image		创建并运行容器
	--name="tomcat"		指定名字
	-d					后台
	-it					交互方式
	-p 主机端口:容器端口   指定端口
	-rm					用完即删，测试用
	-v 容器目录[:ro]   匿名挂载；指定容器权限只读
	-v 卷名:容器目录 		具名挂载
	-v 主机目录:容器目录   指定挂载
	--volumes-from 数据卷容器 挂载数据卷容器
	
docker start tomcat		运行容器
docker restart tomcat	重启容器
docker stop tomcat		停止容器
docker kill tomcat		强制停止容器
docker rm 容器名		  删除容器

docker exec	-it 容器id /bin/bash   进入容器，开启新的终端，可以操作
docker attach 容器id	   进入容器正在执行的终端
exit 					直接退出
ctrl+P+Q				不停止退出
	
docker logs -tf 容器id	容器日志
docker top 容器id			容器进程信息
docker inspect 容器id		容器元数据

docker cp 容器id:容器内路径 目的主机路径		从容器拷贝文件到主机

docker commit -m="描述信息" -a="作者" 容器id 目标镜像名:[tag]

# 数据卷
docker volume			查看数据卷
	ls 					展示卷名
	inspect 卷名		   查看数据卷详细信息
```

![image-20211213140811280](http://mdimg.sofice.top/202112131408380.png)

==注意==

- docker使用后台运行，必须有个前台进程，如果没有提供服务就会停止后台进程。
- 挂载数据卷：容器未运行也可同步；容器删除数据卷不丢失



## Portainer

Docker图形化界面管理工具

```bash
docker run -d -p 8088:9000 \
--restart=always -v /var/run/docker.sock:/var/run/docker.sock --privileged=true portainer/portainer
```







# Dockerfile

用来构建镜像

1. 创建dockerfile

    ```bash
    FROM centos
    MAINTAINER sofice<773508803@qq.com>
    
    COPY readme.txt /usr/local/readme.txt
    
    ADD jdk-8u11-linux-x64.tar.gz /usr/local/
    ADD apache-tomcat-9.0.22.tar.gz /usr/local/
    
    ENV MYPATH /usr/local
    ENV JAVA_HOME /usr/local/jdk1.8.0_11
    ENV CLASSPATH $JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
    ENV CATALINA_HOME /usr/local/apache-tomcat-9.0.22
    ENV CATALINA_BASH /usr/local/apache-tomcat-9.0.22
    ENV PATH $PATH:$JAVA_HOME/bin:$CATALINA_HOME/lib:$CATALINA_HOME/bin
    
    WORKDIR $MYPATH
    
    RUN yum -y install vim
    
    EXPOSE 8080
    
    VOLUME ["volume01","volume02"] # 匿名挂载
    
    CMD echo "---end---"
    CMD /bin/bash
    CMD /usr/local/apache-tomcat-9.0.22/bin/startup.sh && tail -F /usr/local/apache-tomcat-9.0.22/bin/logs/catalina.out
    ```

    dockerfile指令：

    ```bash
    FROM		# 基础镜像
    MAINTAINER	# 作者姓名+邮箱
    RUN			# 镜像构建时需要的命令
    ADD			# 添加上层镜像
    WORKDIR		# 镜像工作目录
    VOLUME		# 挂载目录
    EXPOSE		# 端口配置
    CMD			# 指定容器启动的时候要运行的命令，只有最后一个会生效
    ENTRYPOINT	# 指定容器启动的时候要运行的命令，追加命令
    ONBUILD		# 被继承时触发
    COPY		# 将文件拷贝到镜像中
    ENV 		# 设置环境变量
    ```

    

2. 构建镜像

    ```bash
    docker build -f /home/dockerfile -t szy/centos:1.0 .
    ```

3. 运行镜像

    `docker run`

4. 发布镜像

    `docker push`









# 数据管理

进行持久化和容器数据共享的方法





## 数据卷（Data Volumes）

**容器数据直接映射到本地**

创建数据卷

```bash
docker volume create volumename
```

挂载

`-mount`支持三种类型数据卷：

- volume：普通数据卷，映射到主机 `/var/lib/docker/volumes` 下，可用匿名或具名方式
- bind：绑定数据卷，映射到主机指定目录下，又称指定挂载
- tmpfs：临时数据卷，只存在于内存

```bash
# 新的-mount方法
docker run --mount type=bind,source=/webapp,destination=/opt/webapp centos
# 旧的-v方法
docker run -v /webapp:/opt/webapp centos	
```





## 数据卷容器（Data Volumes Containers）

**使用特定容器维护数据卷**

以一个容器为数据卷容器，其他容器可以挂载此容器，实现数据同步复制，并且是硬链接

```bash
docker run --name c2 --volume-from c1 centos
```

要删除时，必须在删除最后一个还挂载着它的容器时显示使用 `docker rm -v`



## 备份与恢复

备份

```sh
docker run --volume-from dbdata -v $(pwd):/backup --name worker ubuntu tar cvf /backup/backup.tar /dbdata
```

恢复

```sh
docker run -v /dbdata --name dbdata2 ubuntu /bin/bash

docker run --volume-from dbdata2 -v $(pwd):/backup --name worker ubuntu tar xvf /backup/backup.tar
```





# 部署软件

## 部署 MySQL

```sh
docker run -it -d --name mysql -p 3306:3306 -v /home/mysql/conf:/etc/mysql/conf.d -v /home/mysql:/var/lib/mysql -e MYSQL_ROOT_PASSWORD=martin123 --restart=always mysql:latest bash
```





## 部署 Redis





























