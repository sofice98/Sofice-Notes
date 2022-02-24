# RPC（Remote Procedure Call Protocol，远程过程调用协议）

一种通过网络从远程计算机程序上请求服务，而不需要了解底层网络技术的协议。即客户端在不知道调用细节的情况下，调用存在于远程计算机上的某个对象，就像调用本地应用程序中的对象一样。

RPC=通信+序列化

- **RPC是协议**：既然是协议就只是一套规范，那么就需要有人遵循这套规范来进行实现。目前典型的RPC实现包括：Dubbo、Thrift、GRPC、Hetty等。

- **网络协议和网络IO模型透明**：既然RPC的客户端认为自己是在调用本地对象。那么传输层使用的是TCP/UDP还是HTTP协议，又或者是一些其他的网络协议它就不需要关心了。既然网络协议对其透明，那么调用过程中，使用的是哪一种网络IO模型调用者也不需要关心。
- **信息格式透明**：我们知道在本地应用程序中，对于某个对象的调用需要传递一些参数，并且会返回一个调用结果。至于被调用的对象内部是如何使用这些参数，并计算出处理结果的，调用方是不需要关心的。那么对于远程调用来说，这些参数会以某种信息格式传递给网络上的另外一台计算机，这个信息格式是怎样构成的，调用方是不需要关心的。
- **语言透明**：因为调用方实际上也不清楚远程服务器的应用程序是使用什么语言运行的。那么对于调用方来说，无论服务器方使用的是什么语言，本次调用都应该成功，并且返回值也应该按照调用方程序语言所能理解的形式进行描述。

<img src="http://mdimg.sofice.top/202112111339912.png" alt="这里写图片描述" style="zoom:80%;" />

- **Client**：RPC协议的调用方。最理想的情况是RPC Client在完全不知道有RPC框架存在的情况下发起对远程服务的调用。但实际情况来说Client或多或少的都需要指定RPC框架的一些细节。

- **Server**：在RPC规范中，这个Server并不是提供RPC服务器IP、端口监听的模块。而是远程服务方法的具体实现（在JAVA中就是RPC服务接口的具体实现）。其中的代码是最普通的和业务相关的代码，甚至其接口实现类本身都不知道将被某一个RPC远程客户端调用。

- **Stub/Proxy**：RPC代理存在于客户端，因为要实现客户端对RPC框架“透明”调用，那么客户端不可能自行去管理消息格式、不可能自己去管理网络传输协议，也不可能自己去判断调用过程是否有异常。这一切工作在客户端都是交给RPC框架中的“代理”层来处理的。

- **Message Protocol**：RPC的消息管理层专门对网络传输所承载的消息信息进行编码和解码操作。目前流行的技术趋势是不同的RPC实现，为了加强自身框架的效率都有一套私有的消息格式。

- **Transfer/Network Protocol**：传输协议层负责管理RPC框架所使用的网络协议、网络IO模型。例如Hessian的传输协议基于HTTP（应用层协议）；而Thrift的传输协议基于TCP（传输层协议）。传输层还需要统一RPC客户端和RPC服务端所使用的IO模型
- **Selector/Processor**：存在于RPC服务端，用于服务器端某一个RPC接口的实现的特性。所以在RPC框架中应该有一种“负责执行RPC接口实现”的角色。包括：管理RPC接口的注册、判断客户端的请求权限、控制接口实现类的执行在内的各种工作
- **IDL（接口定义语言）**：实际上IDL并不是RPC实现中所必须的。但是需要跨语言的RPC框架一定会有IDL部分的存在。这是因为要找到一个各种语言能够理解的消息结构、接口定义的描述形式。如果您的RPC实现没有考虑跨语言性，那么IDL部分就不需要包括，例如JAVA RMI因为就是为了在JAVA语言间进行使用，所以JAVA RMI就没有相应的IDL。

在物理服务器性能相同的情况下，以下几个因素会对一款RPC框架的性能产生直接影响：

- **使用的网络IO模型**：RPC服务器可以只支持传统的阻塞式同步IO，也可以做一些改进让RPC服务器支持非阻塞式同步IO，或者在服务器上实现对多路IO模型的支持。这样的RPC服务器的性能在高并发状态下，会有很大的差别。特别是单位处理性能下对内存、CPU资源的使用率。

- **基于的网络协议**：一般来说您可以选择让您的RPC使用应用层协议，例如HTTP或者HTTP/2协议，或者使用TCP协议，让您的RPC框架工作在传输层。工作在哪一层网络上会对RPC框架的工作性能产生一定的影响，但是对RPC最终的性能影响并不大。但是至少从各种主流的RPC实现来看，没有采用UDP协议做为主要的传输协议的。

- **消息封装格式**：选择或者定义一种消息格式的封装，要考虑的问题包括：消息的易读性、描述单位内容时的消息体大小、编码难度、解码难度、解决半包/粘包问题的难易度。当然如果您只是想定义一种RPC专用的消息格式，那么消息的易读性可能不是最需要考虑的。消息封装格式的设计是目前各种RPC框架性能差异的最重要原因，这就是为什么几乎所有主流的RPC框架都会设计私有的消息封装格式的原因。dubbo中消息体数据包含dubbo版本号、接口名称、接口版本、方法名称、参数类型列表、参数、附加信息

- **Schema 和序列化（Schema & Data Serialization）**：序列化和反序列化，是对象到二进制数据的转换，程序是可以理解对象的，对象一般含有 schema 或者结构，基于这些语义来做特定的业务逻辑处理。考察一个序列化框架一般会关注以下几点：

  - Encoding format ：是否 human readable（是否能直观看懂 json） 还是 binary(二进制)。
  - Schema declaration：也叫作契约声明，基于 IDL，比如 Protocol Buffers/Thrift，还是自描述的，比如 JSON、XML。另外还需要看是否是强类型的。
  - 语言平台的中立性 ：比如 Java 的 Native Serialization 就只能自己玩，而 Protocol Buffers 可以跨各种语言和平台。
  - 新老契约的兼容性：比如 IDL 加了一个字段，老数据是否还可以反序列化成功。
    和压缩算法的契合度：跑 benchmark (基准)和实际应用都会结合各种压缩算法，例如 gzip、snappy。
  - 性能：这是最重要的，序列化、反序列化的时间，序列化后数据的字节大小是考察重点。

  序列化方式非常多，常见的有 Protocol Buffers， Avro，Thrift，XML，JSON，MessagePack，Kyro，Hessian，Protostuff，Java Native Serialize，FST 。

- **实现的服务处理管理方式**：在高并发请求下，如何管理注册的服务也是一个性能影响点。您可以让RPC的Selector/Processor使用单个线程运行服务的具体实现（这意味着上一个客户端的请求没有处理完，下一个客户端的请求就需要等待）、您也可以为每一个RPC具体服务的实现开启一个独立的线程运行（可以一次处理多个请求，但是操作系统对于“可运行的最大线程数”是有限制的）、您也可以线程池来运行RPC具体的服务实现（目前看来，在单个服务节点的情况下，这种方式是比较好的）、您还可以通过注册代理的方式让多个服务节点来运行具体的RPC服务实现。



# Dubbo

**服务发现**

服务发现，即消费端自动发现服务地址列表的能力，是微服务框架需要具备的关键能力，借助于自动化的服务发现，微服务之间可以在无需感知对端部署位置与 IP 地址的情况下实现通信。

实现服务发现的方式有很多种，Dubbo 提供的是一种 Client-Based  的服务发现机制，通常还需要部署额外的第三方注册中心组件来协调服务发现过程，如常用的 Nacos、Consul、Zookeeper 等，Dubbo 自身也提供了对多种注册中心组件的对接，用户可以灵活选择。

Dubbo 基于消费端的自动服务发现能力，其基本工作原理如下图：

<img src="http://mdimg.sofice.top/202112111339375.png" alt="dubbo" style="zoom: 50%;" />

服务发现的一个核心组件是注册中心，Provider 注册地址到注册中心，Consumer 从注册中心读取和订阅 Provider 地址列表。 因此，要启用服务发现，需要为 Dubbo 增加注册中心配置

Dubbo3 引入应用级服务发现，主要有以下优势

- 适配云原生微服务变革。云原生时代的基础设施能力不断向上释放，像 Kubernetes 等平台都集成了微服务概念抽象，Dubbo3 的应用级服务发现是适配各种微服务体系的通用模型。
- 提升性能与可伸缩性。支持超大规模集群的服务治理一直以来都是 Dubbo  的优势，通过引入应用级服务发现模型，从本质上解决了注册中心地址数据的存储与推送压力，相应的 Consumer  侧的地址计算压力也成数量级下降；集群规模也开始变得可预测、可评估（与 RPC 接口数量无关，只与实例部署规模相关）。









# Zookeeper

分布式服务框架，主要是用来实现==服务注册与发现==，解决分布式应用中经常遇到的一些数据管理问题，如：统一命名服务、状态同步服务、集群管理、分布式应用配置项的管理等。

zookeeper=文件系统+监听通知机制

<img src="http://mdimg.sofice.top/202112111339063.png" alt="img" style="zoom: 80%;" />

1. **文件系统**

   Zookeeper维护一个类似文件系统的数据结构，每个子目录项如 NameService 都被称作为 znode(目录节点)，和文件系统一样，我们能够自由的增加、删除znode，在一个znode下增加、删除子znode，唯一的不同在于znode是可以存储数据的。

   有四种类型的znode：

    - **PERSISTENT：持久化目录节点**

      客户端与zookeeper断开连接后，该节点依旧存在

    - **PERSISTENT_SEQUENTIAL：持久化顺序编号目录节点**

      客户端与zookeeper断开连接后，该节点依旧存在，只是Zookeeper给该节点名称进行顺序编号

    - **EPHEMERAL：临时目录节点**

      客户端与zookeeper断开连接后，该节点被删除

    - **EPHEMERAL_SEQUENTIAL：临时顺序编号目录节点**

      客户端与zookeeper断开连接后，该节点被删除，只是Zookeeper给该节点名称进行顺序编号

2. **监听通知机制**

   客户端注册监听它关心的目录节点，当目录节点发生变化（数据改变、被删除、子目录节点增加删除）时，zookeeper会通知客户端。

假设我们的程序是分布式部署在多台机器上，如果我们要改变程序的配置文件，需要逐台机器去修改，非常麻烦，现在把这些配置全部放到zookeeper上去，保存在 zookeeper 的某个目录节点中，然后所有相关应用程序对这个目录节点进行监听，一旦配置信息发生变化，每个应用程序就会收到  zookeeper 的通知，然后从 zookeeper 获取新的配置信息应用到系统中。



**安装使用**

下载：apache-zookeeper-3.7.0-bin.tar.gz，重命名配置文件zoo_sample.cfg

```shell
查看目录：ls /
创建节点：create /config myData
删除节点：delete /config
获取值：get /config
设置值：set /config
```

```java
public class ZooKeeperProSync implements Watcher {
    private static CountDownLatch connectedSemaphore = new CountDownLatch(1);
    private static ZooKeeper zk = null;
    private static Stat stat = new Stat();

    public static void main(String[] args) throws Exception {
        //zookeeper配置数据存放路径
        String path = "/username";
        //连接zookeeper并且注册一个默认的监听器
        zk = new ZooKeeper("localhost:2181", 5000, //
                new ZooKeeperProSync());
        //等待zk连接成功的通知
        connectedSemaphore.await();
        //获取path目录节点的配置数据，并注册默认的监听器
        System.out.println(new String(zk.getData(path, true, stat)));

        Thread.sleep(Integer.MAX_VALUE);
    }

    public void process(WatchedEvent event) {
        if (Event.KeeperState.SyncConnected == event.getState()) {  //zk连接成功通知事件
            if (Event.EventType.None == event.getType() && null == event.getPath()) {
                connectedSemaphore.countDown();
            } else if (event.getType() == Event.EventType.NodeDataChanged) {  //zk目录节点数据变化通知事件
                try {
                    System.out.println("配置已修改，新值为：" + new String(zk.getData(event.getPath(), true, stat)));
                } catch (Exception e) {
                }
            }
        }
    }
}
```



**配置说明**

```java
dataDir=/tmp/zookeeper-1
clientPort=2181
server.1=127.0.0.1:2888:3888
server.2=127.0.0.1:2889:3889
server.3=127.0.0.1:2890:3890
```

- tickTime：这个时间是作为 Zookeeper 服务器之间或客户端与服务器之间维持心跳的时间间隔，也就是每个 tickTime 时间就会发送一个心跳。
- initLimit：这个配置项是用来配置 Zookeeper 接受客户端（这里所说的客户端不是用户连接 Zookeeper 服务器的客户端，而是 Zookeeper 服务器集群中连接到 Leader 的 Follower 服务器）初始化连接时最长能忍受多少个心跳时间间隔数。当已经超过 10个心跳的时间（也就是  tickTime）长度后 Zookeeper 服务器还没有收到客户端的返回信息，那么表明这个客户端连接失败。总的时间长度就是  10*2000=20 秒
- syncLimit：这个配置项标识 Leader 与 Follower 之间发送消息，请求和应答时间长度，最长不能超过多少个 tickTime 的时间长度，总的时间长度就是 5*2000=10秒
- dataDir：顾名思义就是 Zookeeper 保存数据的目录，默认情况下，Zookeeper 将写数据的日志文件也保存在这个目录里。
- clientPort：这个端口就是客户端连接 Zookeeper 服务器的端口，Zookeeper 会监听这个端口，接受客户端的访问请求。
- server.A=B：C：D：其中 A 是一个数字，表示这个是第几号服务器；B 是这个服务器的 ip 地址；C 表示的是这个服务器与集群中的 Leader  服务器交换信息的端口；D 表示的是万一集群中的 Leader 服务器挂了，需要一个端口来重新进行选举，选出一个新的  Leader，而这个端口就是用来执行选举时服务器相互通信的端口。如果是伪集群的配置方式，由于 B 都是一样，所以不同的 Zookeeper  实例通信端口号不能一样，所以要给它们分配不同的端口号。







# Restful（Representational State Transfer，表现层状态转化）

REST描述了一个架构样式的网络系统。

在目前主流的三种 Web 服务交互方案中，REST 相比于 SOAP（Simple Object Access protocol，简单对象访问协议）以及 XML-RPC 更加简单明了，无论是对 URL 的处理还是对 Payload 的编码，REST 都倾向于用更加简单轻量的方法设计和实现。值得注意的是 REST 并没有一个明确的标准，而更像是一种设计的风格。  

优点：结构清晰、符合标准、易于理解、扩展方便

**restful 的特性：** 

- 资源（Resources）：网络上的一个实体，或者说是网络上的一个具体信息。  它可以是一段文本、一张图片、一种服务等，可以用一个 URI 指向它。

- 表现层（Representation）：把资源具体呈现出来的形式，叫做它的表现层。 比如，文本可以用 txt 格式表现，也可以用 HTML 格式、XML 格式、JSON 格式表现，甚至可以采用二进制格式。 

- 状态转化（State Transfer）：每发出一个请求，就代表了客户端和服务器的一次交互过程。 HTTP 协议，是一个无状态协议，即所有的状态都保存在服务器端。因此，如果客户端想要操作服务器，必须通过某种手段，让服务器端发生“状态转化”（State Transfer）。而这种转化是建立在表现层之上的，所以就是 “表现层状态转化”。

  具体说，就是 HTTP 协议里面，四个表示操作方式的动词：GET、POST、PUT、DELETE。它们分别对应四种基本操作：GET 用来获取资源，POST 用来新建资源，PUT 用来更新资源，DELETE 用来删除资源。

一般的 url 路径：每个方法对应不同的 url 路径

```java
@RequeMapping("/user/delete")
public void delete(){
}

@RequeMapping("/user/findAll")
public void findAll(){
}

@RequeMapping("/user/add")
public void add(){
}
```

RESTful 风格的路径

```java
@RequeMapping(value = "/user", method = RequestMethod.DELETE)
public void delete(){  // DELETE
}

@RequeMapping(value = "/user",method = RequestMethod.GET)
public void findAll(){ // GET
}

@RequeMapping(value = "/user/{id}",method = RequestMethod.GET)
public void findById(@PathVariable("id") String id){ // GET
}

@RequeMapping(value = "/user",method = RequestMethod.POST)
public void add(){	// POst
}
```

所有方法的路径都是一样的，通过发送的请求方式 get/post/delete/put 来确定使用哪个方法，如果两个方法的请求方式是相同的，则根据所带参数来判断调用哪个方法，比如上述代码中的 findAll 和 findById 方法





