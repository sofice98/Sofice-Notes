# 启动项目

```sh
source /etc/profile
# mysql
systemctl start mysqld.service
# redis
systemctl start redis
# zookeeper
cd /opt/kafka_2.13-2.7.2/
./bin/zookeeper-server-start.sh -daemon ./config/zookeeper.properties
# kafka
nohup ./bin/kafka-server-start.sh ./config/server.properties 1>/dev/null 2>&1 &
# elasticsearch
su sofice
cd /opt/elasticsearch-6.4.3/bin/
./elasticsearch -d
# tomcat
startup.sh
# nginx
systemctl start nginx
# 打包
mvn package -Dmaven.test.skip=true
cp ./target/ROOT.war /opt/apache-tomcat-9.0.56/webapps/
```



# 项目简介

Echo 是一套前后端不分离的开源社区系统，基于目前主流 Java Web 技术栈（SpringBoot + MyBatis + MySQL + Redis + Kafka + Elasticsearch + Spring Security +  ...），并提供详细的开发文档和配套教程。包含帖子、评论、私信、系统通知、点赞、关注、搜索、用户设置、数据统计等模块。

|          | username | password |      特殊权限      |
| :------: | :------: | :------: | :----------------: |
|  管理员  |  admin   |  admin   | 数据统计、删除帖子 |
|   版主   |  master  |  master  | 置顶帖子、加精帖子 |
| 普通用户 |   user   |   user   |                    |



# 项目亮点

## mysql

主要维护四张表：用户信息表（用户名，密码，邮箱，头像，激活状态，类型），帖子信息表（发帖人，标题，内容，类型(普通，精华，指定)，状态(正常，拉黑)，评论数，分数），评论信息表（评论作者，类型，目标实体，目标用户，内容，状态），私信信息表（发送方，接收方，类型(关注，点赞，评论，两个用户间对话)，内容，状态）

### 索引建立

每个表有自增的id作为主键，建立主键索引

- user：唯一索引 用户名，唯一索引 邮箱 

- discusspost：发帖用户id，联合索引（状态，类型，创建时间）（1、所有正常帖子的个数，2、所有正常帖子按类型和创建时间排序，最新帖子），联合索引（状态，类型，分数，创建时间）（最热帖子，见定时任务）。mysql的全文索引不好用，帖子标题和内容的搜索使用了es。点赞关注使用了redis。
- comment：发评论用户id，评论目标id，联合索引（状态，类型，目标实体）（见评论设计）
- message：发送方id，接收方id，类型



## 定时任务

搜索最热帖子时，会按照分数排序，因此考虑建立索引，但是频繁的点赞评论等操作会引起索引文件频繁更改，导致数据库消耗过大，因此考虑定时刷新帖子分数。

帖子增删评论，更改点赞，更改加精都会将帖子的id存入redis set里，5分钟的定时任务会定时计算redis set里的帖子分数，更新到数据库和es。







## redis

### 验证码

登陆时，由于这个时候用户还没有登录，我们是没有办法通过用户的 id 来唯一的对应它的验证码的。所以这个时候我们考虑生成一个随机的 id 来暂时的代替这个用户，将其和对应的验证码**暂时**存入 Redis 中（60s）。并且在 Cookie 中暂时存一份为这个用户生成的随机 id（60s）。

这样，当用户点击登录按钮后，就会去 Cookie 中获取这个随机 id，然后去 Redis 中查询对应的验证码，判断用户输入的验证码是否一致。

### 登录验证

- 用户登录 —> 生成登录凭证 LoginTicket 存入 Redis，Cookie 中存一份 key
- 每次执行请求拦截器都会通过 Cookie 去 Redis 中查询该用户的登陆凭证是否过期和是否有效。点击记住我可以延长登录凭证的过期时间，用户退出则其登录凭证变为无效状态
- 根据这个登录凭证对应的用户 id，去数据库中查询这个用户信息
- 使用 ThreadLocal 在本次请求中一直持有这个用户信息
- 优化点：每次请求前都需要去数据库查询这个用户信息，访问频率比较高，所以我们考虑把登录成功的用户信息在 Redis 中保存一会，拦截器每次查询前先去 Redis  中查询，然后缓存和数据库的一致性问题的话，使用的是旁路缓存模式，也就是先更新数据库，然后直接删除缓存中的数据。

:question: 为什么不用Session

Session  无法在分布式存储中发挥有效的作用：客户端发送一个请求给服务器，经过负载均衡后该请求会被分发到集群中多个服务器中的其中一个，由于不同的服务器可能含有不同的 Web 服务器，而 Web 服务器之间并不能发现其他 Web 服务器中保存的 Session 信息，这样，它就会再次重新生成一个  JSESSIONID，导致之前的状态丢失。所以这里我们考虑使用 `ThreadLocal` 保存用户信息，`ThreadLocal` 在每个线程中都创建了一个用户信息副本，也就是说每个线程都可以访问自己内部的用户信息副本变量。

:question: 为什么是直接删除缓存，而不是也相应的更新缓存呢

在多线程的环境下，假设线程 A 更新了数据库中的某个字段为 1，如果在线程 A 提交之前，线程 B 又修改了这个字段为 2 并且先于线程 A 做了提交，那么线程 A 接下来提交的数据就是脏数据。直接删除缓存可以避免这个问题。

:question: 如何解决同一个用户发出的两次请求可能被不同的两个线程进行处理

定义一个过滤器，在每次请求前都对用户进行判断（为了避免每次请求都经过过滤器，可以将登录成功的用户信息暂时存储到 Redis 中），然后将已经登录成功的用户信息存到 ThreadLocal 里，从而使得该线程在本次请求中持有该用户信息。



### 点赞信息

包含两步：

- 用户A给用户B的帖子点赞
- 用户B的点赞数加1

需要用到redis事务

### 关注信息



### 网站统计

独立访客uv，hyperloglog

日活跃用户dau，bitmap



### 帖子热度

见定时任务



## 事务管理

### 发布评论 

spring的 @Transactional

1. 增加评论数据（向评论表 `comment` 中添加记录行）

2. 修改帖子的评论数量（帖子表 `discuss_post` 中内置了 comment_count 字段）

### 点赞 

redis的 redisOperations

1. 对帖子/ 回复的点赞列表中添加userId
2. 被赞的user总赞数自增



## kafka

:question: 为什么选kafka

1）Kafka 天生支持分布式，Broker、Producer 和 Consumer 都原生自动支持分布式；

2）Kafka 拥有多分区（Partition）和多副本（Replica）机制，能提供比较好的并发能力（负载均衡）以及较高的可用性和可靠性，理论上支持消息无限堆积；

3）而且，在一众消息队列里，Kafka 的性能是比较高的。点赞、关注、私信等操作都会触发通知，在流量巨大的社交论坛网站中，这个系统通知的需求是非常庞大的，为保证系统的高性能，使用消息队列 Kafka 是个明智的选择。



用在评论，点赞，关注，发帖，删帖事件上

- 评论、点赞、关注事件触发通知
- 发帖事件触发 Elasticsearch 服务器中相应的数据更新
- 删帖事件触发 Elasticsearch 服务器中相应的数据更新



## elasticsearch

用在贴子表上





# 评论设计

评论信息表（评论作者，类型，目标实体，目标用户，内容，状态）

渲染过程：

1. 查找评论信息中所有类型为评论、目标为帖子id 的 评论、作者信息、点赞数、回复数
2. 对于每个评论，查找所有类型为回复、目标为评论id 的 回复、作者信息、目标用户、点赞数



只有对帖子的评论和对评论的回复，没有对回复的回复。在回复别人回复时，类型时对评论的回复，目标用户是被回复的用户id。



























