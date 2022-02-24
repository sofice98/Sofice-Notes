# Nginx 概述

port：80

Nginx 是高性能的 HTTP 和[反向代理](https://so.csdn.net/so/search?q=反向代理)的web服务器，处理高并发能力是十分强大的，能经受高负 载的考验,有报告表明能支持高达 50,000 个并发连接数。

其特点是占有内存少，并发能力强



作用：

1. **作为 web 服务器**

2. **正向代理**：通过代理服务器来访问服务器

3. **反向代理： **需要将请求发送到反向代理服务器，由反向代理服务器去选择目标服务器获取数据后，在返回给客户端。好处是 **暴露的是代理服务器地址，隐藏了真实服务器 IP 地址**

4. **负载均衡**
5. **动静分离**：为了加快网站的解析速度，可以把动态页面和静态页面由不同的服务器来解析，加快解析速度。降低原来单个服务器的压力。



# Nginx 的安装

```sh
# 通过 yum 命令快速下载并安装 Nginx
yum install -y nginx.x86_64  
# 配置代理
vim /etc/nginx/nginx.conf
# 启动 Nginx
systemctl start nginx
# 重新加载配置文件
nginx -s reload
```

配置文件：【/etc/nginx/nginx.conf】





# Nginx 的配置文件

```
worker_processes  1;

events {
    worker_connections  1024;
}

http {
    include       mime.types;
    default_type  application/octet-stream;
    sendfile        on;
    keepalive_timeout  65;

    server {
        listen       80;
        server_name  localhost;

        location / {
            root   html;
            proxy_pass   http://myserver;
            #proxy_pass   http://127.0.0.1:8081;
            index  index.html index.htm;
        }
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }
    }
}
```

**第一部分：全局块**

从配置文件开始到 events 块之间的内容，主要会设置一些影响nginx 服务器整体运行的配置指令，主要包括配 置运行 Nginx 服务器的用户（组）、允许生成的 worker process 数，进程 PID 存放路径、日志存放路径和类型以 及配置文件的引入等。

worker_processes：值越大，可以支持的并发处理量也越多，但是 会受到硬件、软件等设备的制约。



**第二部分：events块**

主要影响 Nginx 服务器与用户的网络连接，常用的设置包括是否开启对多 work_process 下的网络连接进行序列化，是否 允许同时接收多个网络连接，选取哪种事件驱动模型来处理连接请求，每个 word_process 可以同时支持的最大连接数等。

worker_connections：work process 支持的最大连接数



**第三部分：**

Nginx 服务器配置中最频繁的部分，代理、缓存和日志定义等绝大多数功能和第三方模块的配置都在这里。

**http全局块**

http全局块配置的指令包括文件引入、MIME-TYPE 定义、日志自定义、连接超时时间、单链接请求数上限等。

**server 块**

这块和虚拟主机有密切关系，虚拟主机从用户角度看，和一台独立的硬件主机是完全一样的，该技术的产生是为了 节省互联网服务器硬件成本。每个 http 块可以包括多个 server 块，而每个 server 块就相当于一个虚拟主机。而每个 server 块也分为全局 server 块，以及可以同时包含多个 locaton 块。

- 全局 server 块

  最常见的配置是本虚拟机主机的监听配置和本虚拟主机的名称或IP配置。

- location 块

  一个 server 块可以配置多个 location 块，**实现不同地址映射到不同虚拟主机**。
  这块的主要作用是基于 Nginx 服务器接收到的请求字符串（例如 server_name/uri-string），对虚拟主机名称 （也可以是IP 别名）之外的字符串（例如 前面的 /uri-string）进行匹配，对特定的请求进行处理。 地址定向、数据缓 存和应答控制等功能，还有许多第三方模块的配置也在这里进行。

  

## **location 指令说明**

1、= ：用于不含正则表达式的 uri 前，要求请求字符串与 uri 严格匹配，如果匹配 成功，就停止继续向下搜索并立即处理该请求。
2、~：用于表示 uri 包含正则表达式，并且区分大小写。
3、~*：用于表示 uri 包含正则表达式，并且不区分大小写。
4、^~：用于不含正则表达式的 uri 前，要求 Nginx 服务器找到标识 uri 和请求字 符串匹配度最高的 location 后，立即使用此 location 处理请求，而不再使用 location 块中的正则 uri 和请求字符串做匹配。



## 负载均衡配置

upstream 允许Nginx定义一组节点服务器，通过 proxy_pass 代理网站请求。

upstream 参数：

- down：当前 server 暂时不参与负载
- weight：越大，负载的权重就越大。
- max_fails：允许 Nginx 尝试连接服务器的最大失败次数，默认为1。当超过最大次数时，返回proxy_next_upstream模块定义的错误
- fail_timeout：max_fails 次失败后，暂停的时间。
- backup： 其它所有的非backup机器down或者忙的时候，请求backup机器。所以这台机器压力会最轻。

```
upstream myserver {
    server 127.0.0.1:8080 weight=1 max_fails=3 fail_timeout=30s;
    server 127.0.0.1:8081 weight=3;
}
server {
    listen       80;
    server_name  208.208.128.122;

    location / {
        root   html;
        proxy_pass   http://myserver;
        index  index.html index.htm;
}
```



# Nginx 的高可用集群

配置主从nginx

需要多台nginx 服务器，keepalived，虚拟IP





# Nginx 的原理

## mater 和 worker

nginx 启动后，是由两个进程组成的。master（管理者）和worker（工作者）。一个nginx 只有一个master。但可以有多个worker。

![image-20220104184218343](http://mdimg.sofice.top/202201041842382.png)

过来的请求由master管理，worker进行争抢式的方式去获取请求。



**master-workers 的机制的好处**

- 对于每个 worker 进程来说，独立的进程，不需要加锁，所以省掉了锁带来的开销， 同时在编程以及问题查找时，也会方便很多。
- 可以使用 `nginx –s reload` 热部署
- 采用独立的进程，可以让互相之间不会 影响，一个进程退出后，其它进程还在工作，服务不会中断，master 进程则很快启动新的 worker 进程。



:question: 设置多少个 worker

Nginx 同 redis 类似都采用了 io 多路复用机制，每个 worker 都是一个独立的进程，但每个进程里只有一个主线程，通过异步非阻塞的方式来处理请求， 即使是千上万个请求也不在话下。每个 worker 的线程可以把一个 cpu 的性能发挥到极致。所以 worker 数和服务器的 cpu 数相等是最为适宜的。设少了会浪费 cpu，设多了会造成 cpu 频繁切换上下文带来的损耗。