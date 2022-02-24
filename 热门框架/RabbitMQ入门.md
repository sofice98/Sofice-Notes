# RabbitMQ 入门

---

## 1. 安装（Win10）

分为两步

- 安装 erlang
- 安装 RabbitMQ

详见 👉 [windows10环境下的RabbitMQ安装步骤（图文）](https://www.cnblogs.com/saryli/p/9729591.html)

官网下载非常慢，这里给出部分版本的网盘链接 🔗 [RabbitMQ 3.84 + Erlang 23.0 - Windows - 密码 yzi8](https://pan.baidu.com/s/1Bnj5iMKghksQJvkIUvwnng)

## 2. RabbitMQ 简介

**RabbitMQ 是采用 Erlang 语言实现 `AMQP(Advanced Message Queuing Protocol，高级消息队列协议）` 的消息中间件**，它最初起源于金融系统，用于在分布式系统中存储转发消息。

RabbitMQ 发展到今天，被越来越多的人认可，这和它在易用性、扩展性、可靠性和高可用性等方面的卓著表现是分不开的。RabbitMQ 的具体特点可以概括为以下几点：

- **可靠性：** RabbitMQ使用一些机制来保证消息的可靠性，如持久化、传输确认及发布确认等。
- **灵活的路由：** 在消息进入队列之前，通过交换器来路由消息。对于典型的路由功能，RabbitMQ 己经提供了一些内置的交换器来实现。针对更复杂的路由功能，可以将多个交换器绑定在一起，也可以通过插件机制来实现自己的交换器。这个后面会在我们将 RabbitMQ 核心概念的时候详细介绍到。
- **扩展性：** 多个RabbitMQ节点可以组成一个集群，也可以根据实际业务情况动态地扩展集群中节点。
- **高可用性：** 队列可以在集群中的机器上设置镜像，使得在部分节点出现问题的情况下队列仍然可用。
- **支持多种协议：** RabbitMQ 除了原生支持 AMQP 协议，还支持 STOMP、MQTT 等多种消息中间件协议。
- **多语言客户端：** RabbitMQ几乎支持所有常用语言，比如 Java、Python、Ruby、PHP、C#、JavaScript等。
- **易用的管理界面：** RabbitMQ提供了一个易用的用户界面，使得用户可以监控和管理消息、集群中的节点等。<u>安装好 RabbitMQ 就自带管理界面</u>。
- **插件机制：** RabbitMQ 提供了许多插件，以实现从多方面进行扩展，当然也可以编写自己的插件。感觉这个有点类似 Dubbo 的 SPI机制。

## 3. RabbitMQ 核心概念

**RabbitMQ 整体上是一个生产者与消费者模型，主要负责接收、存储和转发消息**。可以把消息传递的过程想象成：当你将一个包裹送到邮局，邮局会暂存并最终将邮件通过邮递员送到收件人的手上，RabbitMQ 就好比由邮局、邮箱和邮递员组成的一个系统。从计算机术语层面来说，RabbitMQ 模型更像是一种交换机模型。

RabbitMQ 的整体模型架构如下：

![](https://gitee.com/veal98/images/raw/master/img/20201124213040.png)

接下来一一介绍上图中的概念：👇

### ① Producer(生产者) 和 Consumer(消费者)

`Producer(生产者)` : 生产消息的一方（邮件投递者）

`Consumer(消费者) `: 消费消息的一方（邮件收件人）

消息一般由 2 部分组成：消息头（或者说是标签 Label）和 消息体。消息体也可以称为 payLoad, 消息体是不透明的，而消息头则由一系列的可选属性组成，这些属性包括 routing-key（路由键）、priority（相对于其他消息的优先权）、delivery-mode（指出该消息可能需要持久性存储）等。生产者把消息交由 RabbitMQ 后，RabbitMQ 会根据消息头把消息发送给感兴趣的 Consumer(消费者)。

### ② Exchange(交换器)

**在 RabbitMQ 中，消息并不是直接被投递到 `Queue(消息队列) `中的，中间还必须经过 `Exchange(交换器) `这一层，`Exchange(交换器) `会把我们的消息分配到对应的 `Queue(消息队列)` 中**。

<u>**Exchange(交换器)** 用来接收生产者发送的消息并将这些消息路由给服务器中的队列中，如果路由不到，或许会返回给 **Producer(生产者)** ，或许会被直接丢弃掉</u> 。这里可以将RabbitMQ中的交换器看作一个简单的实体。

**RabbitMQ 的 Exchange(交换器) 有 4 种类型，不同的类型对应着不同的路由策略**：**`direct`(默认)，`fanout`, `topic `和 `headers`**，不同类型的 Exchange 转发消息的策略有所区别。

Exchange(交换器) 示意图如下：

![](https://gitee.com/veal98/images/raw/master/img/20201124213450.png)

生产者将消息发给交换器的时候，一般会指定一个 `RoutingKey(路由键)`，用来指定这个消息的路由规则，而这个 `RoutingKey ` 需要与交换器类型和`绑定键(BindingKey)`联合使用才能最终生效。

<u>RabbitMQ 中通过 **Binding(绑定)** 将 **Exchange(交换器)** 与 **Queue(消息队列)** 关联起来，在绑定的时候一般会指定一个 **BindingKey(绑定建)** ,这样 RabbitMQ 就知道如何正确将消息路由到队列了</u>。一个绑定就是基于路由键将交换器和消息队列连接起来的路由规则，所以可以将交换器理解成一个由绑定构成的路由表。Exchange 和 Queue 的绑定可以是多对多的关系。

🍉 Binding(绑定) 示意图：

![](https://gitee.com/veal98/images/raw/master/img/20201124213805.png)

⭐ **生产者将消息发送给交换器时，需要一个 `RoutingKey`, 当 `BindingKey `和 `RoutingKey `相匹配时，消息会被路由到对应的队列中**。在绑定多个队列到同一个交换器的时候，这些绑定允许使用相同的 BindingKey。

BindingKey 并不是在所有的情况下都生效，它依赖于交换器类型，比如 `fanout` 类型的交换器就会无视，而是将消息路由到所有绑定到该交换器的队列中。

#### 交换器类型

RabbitMQ 常用的 Exchange Type 有 **fanout**、**direct**、**topic**、**headers** 这四种（AMQP 规范里还提到两种 Exchange Type，分别为 system 与 自定义，这里不予以描述）。

##### Ⅰ fanout

**Fanout Exchange：扇型交换机**

`fanout` 类型的 Exchange 路由规则非常简单，它会**把所有发送到该 Exchange 的消息路由到所有与它绑定的Queue 中，不做任何判断操作**，所以 fanout 类型是所有的交换机类型里面速度最快的。**`fanout `类型常用来广播消息**。

##### Ⅱ direct

**Direct Exchange：直连型交换机**

`direct `类型的Exchange路由规则也很简单，它会**把消息路由到那些 Bindingkey 与 RoutingKey 完全匹配的 Queue 中**。

![](https://gitee.com/veal98/images/raw/master/img/20201124221837.png)

以上图为例:

- 如果发送消息的时候设置路由键为 “warning” , 那么消息会路由到 Queue1 和 Queue2。

- 如果在发送消息的时候设置路由键为"Info”或者"debug”，消息只会路由到 Queue2。如果以其他的路由键发送消息，则消息不会路由到这两个队列中。

direct 类型常用在处理有优先级的任务，根据任务的优先级把消息发送到对应的队列，这样可以指派更多的资源去处理高优先级的队列。

##### Ⅲ topic

**Topic Exchange：主题交换机**

前面讲到 `direct` 类型的交换器路由规则是完全匹配 BindingKey 和 RoutingKey ，但是**这种严格的匹配方式在很多情况下不能满足实际业务的需求**。**`topic `类型的交换器在匹配规则上进行了扩展**，它与 `direct `类型的交换器相似，也是将消息路由到 BindingKey 和 RoutingKey 相匹配的队列中，但这里的匹配规则有些不同，它约定：

- RoutingKey 为一个点号 “`．`” 分隔的字符串（被点号 “`．`” 分隔开的每一段独立的字符串称为一个单词），如 “com.rabbitmq.client”、“java.util.concurrent”、“com.hidden.client”;
- BindingKey 和 RoutingKey 一样也是点号 “`．`” 分隔的字符串；
- **BindingKey 中可以存在两种特殊字符串 “`*`” 和 “ `#`”，用于做模糊匹配**，其中 “`*`” 用于匹配一个单词，“`#`” 用于匹配多个单词(可以是零个)。

![](https://gitee.com/veal98/images/raw/master/img/20201124222245.png)

以上图为例：

- 路由键为 “com.rabbitmq.client” 的消息会同时路由到 Queuel 和 Queue2;
- 路由键为 “com.hidden.client” 的消息只会路由到 Queue2 中；
- 路由键为 “com.hidden.demo” 的消息只会路由到 Queue2 中；
- 路由键为 “java.rabbitmq.demo” 的消息只会路由到Queuel中；
- 路由键为 “java.util.concurrent” 的消息将会被丢弃或者返回给生产者（需要设置 mandatory 参数），因为它没有匹配任何路由键。

##### Ⅳ headers(不推荐)

`headers `类型的交换器不依赖于路由键的匹配规则来路由消息，而是根据发送的消息内容中的 `headers `属性进行匹配。

在绑定队列和交换器时制定一组键值对，当发送消息到交换器时，RabbitMQ 会获取到该消息的 `headers`（也是一个键值对的形式)，对比其中的键值对是否完全匹配队列和交换器绑定时指定的键值对，如果完全匹配则消息会路由到该队列，否则不会路由到该队列。

headers 类型的交换器性能会很差，而且也不实用，基本上不会看到它的存在。

### ③ Queue(消息队列)

**Queue(消息队列)** 用来保存消息直到发送给消费者。它是消息的容器，也是消息的终点。一个消息可投入一个或多个队列。消息一直在队列里面，等待消费者连接到这个队列将其取走。

**RabbitMQ** 中消息只能存储在 **队列** 中，这一点和 **Kafka** 这种消息中间件相反。Kafka 将消息存储在 **topic（主题）** 这个逻辑层面，而相对应的队列逻辑只是 topic 实际存储文件中的位移标识。 RabbitMQ 的生产者生产消息并最终投递到队列中，消费者可以从队列中获取消息并消费。

<u>**多个消费者可以订阅同一个队列**，这时队列中的消息会被平均分摊（Round-Robin，即**轮询**）给多个消费者进行处理，而不是每个消费者都收到所有的消息并处理，这样避免的消息被重复消费。</u>

**RabbitMQ** 不支持队列层面的广播消费,如果有广播消费的需求，需要在其上进行二次开发,这样会很麻烦，不建议这样做。

### ④ Broker(消息中间件的服务节点)

对于 RabbitMQ 来说，**一个 RabbitMQ Broker 可以简单地看作一个 RabbitMQ 服务节点，或者RabbitMQ服务实例。大多数情况下也可以将一个 RabbitMQ Broker 看作一台 RabbitMQ 服务器。**

下图展示了生产者将消息存入 RabbitMQ Broker,以及消费者从Broker中消费数据的整个流程：

![](https://gitee.com/veal98/images/raw/master/img/20201124221531.png)



# 👝 SpringBoot + RabbitMQ 简单实例

---

## 1. 使用 Direct 交换机

💡 `Dierct` 交换机要求 Bindingkey 与 RoutingKey 完全匹配

本实例需要创建 2 个springboot 项目，一个 rabbitmq-provider （生产者），一个rabbitmq-consumer（消费者）。

### ① Provider

首先创建 rabbitmq-provider，pom.xml 里用到的 jar 依赖：

```xml
<!--rabbitmq-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-amqp</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```

添加全局配置文件 `application.yml`：

```yml
server:
  port: 8021
spring:
  # 给项目来个名字
  application:
    name: rabbitmq-provider
  # 配置 rabbitMq 服务器
  rabbitmq:
    port: 5672
    # rabbitMq 用户名和密码，默认会有个管理员角色 guest
    username: guest
    password: guest
```

接着我们先使用下 direct exchange(直连型交换机), 创建 `DirectRabbitConfig.java`（对于队列和交换机持久化以及连接使用设置：

```java
package com.smallbeef.rabbitmqprovider.config;

import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.DirectExchange;
import org.springframework.amqp.core.Queue;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class DirectRabbitConfig {

    // 队列 起名：DirectQueue
    @Bean
    public Queue TestDirectQueue() {

        // public Queue(String name, boolean durable, boolean exclusive, boolean autoDelete)
        //一般设置一下队列的持久化就好,其余两个就是默认false
        return new Queue("DirectQueue",true);
    }

    // Direct交换机 起名：TestDirectExchange
    @Bean
    DirectExchange TestDirectExchange() {
        // public DirectExchange(String name, boolean durable, boolean autoDelete)
        return new DirectExchange("DirectExchange",true,false);
    }

    // 绑定 将队列和交换机绑定, 并设置绑定键：BindingKey
    @Bean
    Binding bindingDirect() {
        return BindingBuilder.bind(TestDirectQueue()).to(TestDirectExchange()).with("key");
    }

}
```

其中：

```java
public Queue(String name, boolean durable, boolean exclusive, boolean autoDelete){
    
}
```

- `durable`: 是否持久化,默认是 false

  持久化队列：会被存储在磁盘上，当消息代理重启时仍然存在

  暂存队列：当前连接有效

- `exclusive`: 默认也是 false，只能被当前创建的连接使用，而且当连接关闭后队列即被删除。此参考优先级高于 durable

- `autoDelete`: 是否自动删除，当没有生产者或者消费者使用此队列，该队列会自动删除。

然后写个简单的接口进行消息推送 `SendMessageController.java`：

```java
@RestController
public class SendMessageController {

    @Autowired
    RabbitTemplate rabbitTemplate;  //使用 RabbitTemplate,这提供了接收/发送等等方法

    @GetMapping("/sendDirectMessage")
    public String sendDirectMessage() {
        String messageId = String.valueOf(UUID.randomUUID());
        String messageData = "test message, hello!";
        String createTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        Map<String,Object> map=new HashMap<>();
        map.put("messageId",messageId);
        map.put("messageData",messageData);
        map.put("createTime",createTime);
        // 将消息携带绑定路由键值 key 发送到交换机 DirectExchange
        // Direct 交换机要求路由键与绑定键完全一致
        rabbitTemplate.convertAndSend("DirectExchange", "key", map);
        return "Send Successfully";
    }

}
```

运行 rabbitmq-provider 项目，并访问 [localhost:8021/sendDirectMessage](http://localhost:8021/sendDirectMessage)

因为我们目前还没弄消费者 rabbitmq-consumer，消息没有被消费的，我们 去 rabbitMq 管理页面看看 [http://localhost:15672/#/](http://localhost:15672/#/)，是否推送成功：

<img src="https://gitee.com/veal98/images/raw/master/img/20201124231653.png" style="zoom:50%;" />

再看看队列：

<img src="https://gitee.com/veal98/images/raw/master/img/20201124231754.png" style="zoom:50%;" />

OK，消息已经推送到 rabbitMq 服务器上面了。

### ② Consumer

接下来，创建 rabbitmq-consumer 项目，添加的依赖同上

全局配置文件，注意修改端口：

```yml
server:
  port: 8022
spring:
  # 给项目来个名字
  application:
    name: rabbitmq-consumer
  # 配置 rabbitMq 服务器
  rabbitmq:
    port: 5672
    # rabbitMq 用户名和密码，默认会有个管理员角色 guest
    username: guest
    password: guest
```

由于消费者只需要使用消息即可，不需要发送消息，所以此处我们就不添加配置类了。

创建**消息接收监听类**：

```java
@Component
@RabbitListener(queues = "DirectQueue") //监听的队列名称 DirectQueue
public class DirectReceiver {
    @RabbitHandler
    public void process(Map message){
        System.out.println("DirectReceiver消费者收到消息  : " + message.toString());
    }
}
```

然后将 rabbitmq-consumer 项目运行起来，可以看到把之前推送的那条消息消费下来了：

![](http://mdimg.sofice.top/202201071755578.png)

<img src="https://gitee.com/veal98/images/raw/master/img/20201125125201.png" style="zoom:50%;" />

然后可以再继续调用 rabbitmq-provider 项目的推送消息接口，可以看到消费者即时消费消息

![](http://mdimg.sofice.top/202201071755804.png)

既然直连交换机是一对一，那如果配置多台监听绑定到同一个直连交互的同一个队列，会怎么样？

![](https://gitee.com/veal98/images/raw/master/img/20201125130825.png)

可以看到是实现了轮询的方式对消息进行消费，而且不存在重复消费。

## 2. 使用 Topic 交换机

💡 `Topic` 交换机支持 Bindingkey 与 RoutingKey 的模糊匹配

### ① Provider

在 rabbitmq-provider 项目里面创建 `TopicRabbitConfig.java`：

```java
import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.core.TopicExchange;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
 
@Configuration
public class TopicRabbitConfig {
 	
    // 第一个队列
    @Bean
    public Queue firstQueue() {
        return new Queue("Queue1");
    }
    
 	// 第二个队列
    @Bean
    public Queue secondQueue() {
        return new Queue("Queue2");
    }
 	
    // Topic 交换机 起名：topicExchange
    @Bean
    TopicExchange exchange() {
        return new TopicExchange("topicExchange");
    }
 
 
    // 将 firstQueue 和 topicExchange 绑定,而且绑定的键值为 topic.man
    // 这样只有消息携带的路由键是 topic.man, 才会分发到该队列
    @Bean
    Binding bindingExchangeMessage() {
        return BindingBuilder.bind(firstQueue()).to(exchange()).with("topic.man");
    }
 
    // 将 secondQueue 和 topicExchange 绑定,而且绑定的键值为用上通配路由键规则 topic.#
    // 这样只要是消息携带的路由键是以 topic. 开头,都会分发到该队列
    @Bean
    Binding bindingExchangeMessage2() {
        return BindingBuilder.bind(secondQueue()).to(exchange()).with("topic.#");
    }
}
```

- 队列 1：绑定键为 `topic.man`。只有消息携带的路由键是 `topic.man`, 才会分发到该队列
- 队列 2：绑定键为 `topic.#`。只要是消息携带的路由键是以 `topic.` 开头, 都会分发到该队列

然后添加 2 个接口，用于推送消息到主题交换机：

```java
    @GetMapping("/sendTopicMessage1")
    public String sendTopicMessage1() {
        String messageId = String.valueOf(UUID.randomUUID());
        String messageData = "message: M A N ";
        String createTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        Map<String, Object> manMap = new HashMap<>();
        manMap.put("messageId", messageId);
        manMap.put("messageData", messageData);
        manMap.put("createTime", createTime);
        // 推送消息，路由键为 topic.man
        rabbitTemplate.convertAndSend("topicExchange", "topic.man", manMap);
        return "Send Successfully";
    }
 
    @GetMapping("/sendTopicMessage2")
    public String sendTopicMessage2() {
        String messageId = String.valueOf(UUID.randomUUID());
        String messageData = "message: woman is all ";
        String createTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        Map<String, Object> womanMap = new HashMap<>();
        womanMap.put("messageId", messageId);
        womanMap.put("messageData", messageData);
        womanMap.put("createTime", createTime);
        // 推送消息，路由键为 topic.woman
        rabbitTemplate.convertAndSend("topicExchange", "topic.woman", womanMap);
        return "Send Successfully";
    }
}
```

生产者这边已经完事，先不急着运行

### ② Consumer

在 rabbitmq-consumer 项目上，创建 `TopicManReceiver.java`：

```java
@Component
@RabbitListener(queues = "Queu1") // 监听队列 1
public class TopicManReceiver {

    @RabbitHandler
    public void process(Map message) {
        System.out.println("TopicManReceiver消费者收到消息  : " + message.toString());
    }
    
}
```

再创建一个 `TopicTotalReceiver.java`：

```java
@Component
@RabbitListener(queues = "Queue2") // 监听队列 2
public class TopicTotalReceiver {
 
    @RabbitHandler
    public void process(Map message) {
        System.out.println("TopicTotalReceiver消费者收到消息  : " + message.toString());
    }
}

```

然后把 rabbitmq-provider，rabbitmq-consumer 两个项目都跑起来，先调用 `/sendTopicMessage1` 接口，推送消息 `topic.man`。可以看到两个监听消费者 receiver 都成功消费到了消息，因为这两个 recevier 监听的队列的绑定键都能与这条消息携带的路由键匹配上：

![](http://mdimg.sofice.top/202201071755582.png)

接下来调用接口 `/sendTopicMessage2`，推送消息 `topic.woman`。可以看到两个监听消费者只有 TopicTotalReceiver 成功消费到了消息：

![](http://mdimg.sofice.top/202201071755545.png)

## 3. 使用 Fanout 交换机

💡 `Fanout ` 交换机其实就是广播，无需配置路由键

### ① Provider

同样地，先在 rabbitmq-provider 项目上创建 `FanoutRabbitConfig.java`：

```java
import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.FanoutExchange;
import org.springframework.amqp.core.Queue;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class FanoutRabbitConfig {
 
    /**
     *  创建三个队列 ：fanout.A   fanout.B  fanout.C
     *  将三个队列都绑定在交换机 fanoutExchange 上
     *  因为是扇型交换机, 路由键无需配置,配置也不起作用
     */
    @Bean
    public Queue queueA() {
        return new Queue("fanout.A");
    }
 
    @Bean
    public Queue queueB() {
        return new Queue("fanout.B");
    }
 
    @Bean
    public Queue queueC() {
        return new Queue("fanout.C");
    }
 
    @Bean
    FanoutExchange fanoutExchange() {
        return new FanoutExchange("fanoutExchange");
    }
 
    @Bean
    Binding bindingExchangeA() {
        return BindingBuilder.bind(queueA()).to(fanoutExchange());
    }
 
    @Bean
    Binding bindingExchangeB() {
        return BindingBuilder.bind(queueB()).to(fanoutExchange());
    }
 
    @Bean
    Binding bindingExchangeC() {
        return BindingBuilder.bind(queueC()).to(fanoutExchange());
    }

```

写一个接口用于推送消息：

```java
    @GetMapping("/sendFanoutMessage")
    public String sendFanoutMessage() {
        String messageId = String.valueOf(UUID.randomUUID());
        String messageData = "message: testFanoutMessage ";
        String createTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        Map<String, Object> map = new HashMap<>();
        map.put("messageId", messageId);
        map.put("messageData", messageData);
        map.put("createTime", createTime);
        // 推送消息，无需设置路由键
        rabbitTemplate.convertAndSend("fanoutExchange", null, map);
        return "Send Successfully";
    }
```

### ② Consumer

```java
@Component
@RabbitListener(queues = "fanout.A") // 监听队列 fanout.A
public class FanoutReceiverA {
 
    @RabbitHandler
    public void process(Map message) {
        System.out.println("FanoutReceiverA消费者收到消息  : " +message.toString());
    }
 
}
```

```java
@Component
@RabbitListener(queues = "fanout.B") // 监听队列 fanout.B
public class FanoutReceiverB {
 
    @RabbitHandler
    public void process(Map message) {
        System.out.println("FanoutReceiverB消费者收到消息  : " + message.toString());
    }
 
}
```

```java
@Component
@RabbitListener(queues = "fanout.C") // 监听队列 fanout.C
public class FanoutReceiverC {
 
    @RabbitHandler
    public void process(Map message) {
        System.out.println("FanoutReceiverC消费者收到消息  : " + message.toString());
    }
 
}
```

最后将 rabbitmq-provider 和 rabbitmq-consumer 项目都跑起来，调用下接口 `/sendFanoutMessage` , 看看 rabbitmq-consumer 项目的控制台情况：

![](http://mdimg.sofice.top/202201071755478.png)

由于三个队列都绑定这个扇形交换机，所以三个消息接收类都监听到了这条消息。

## 4. 消息确认

以上三个常用的交换机的使用我们已经完毕了，那么接下来我们继续讲讲消息的回调，其实就是**消息确认（生产者推送消息成功，消费者接收消息成功）**。

### ① 生产者推送消息的消息确认机制

首先在 rabbitmq-provider 项目的 `application.yml` 文件上，加上消息确认的配置项：

<img src="https://gitee.com/veal98/images/raw/master/img/20201125140412.png" style="zoom:67%;" />

然后是配置相关的**消息确认回调函数**，`RabbitConfig.java`：

```java
import org.springframework.context.annotation.Configuration;
import org.springframework.amqp.core.Message;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.connection.CorrelationData;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.context.annotation.Bean;


@Configuration
public class RabbitConfig {

    @Bean
    public RabbitTemplate createRabbitTemplate(ConnectionFactory connectionFactory){
        RabbitTemplate rabbitTemplate = new RabbitTemplate();
        rabbitTemplate.setConnectionFactory(connectionFactory);
        // 设置开启 Mandatory,才能触发回调函数,无论消息推送结果怎么样都强制调用回调函数
        rabbitTemplate.setMandatory(true);

        rabbitTemplate.setConfirmCallback(new RabbitTemplate.ConfirmCallback() {
            @Override
            public void confirm(CorrelationData correlationData, boolean ack, String cause) {
                System.out.println("ConfirmCallback:     " + "相关数据：" + correlationData);
                System.out.println("ConfirmCallback:     " + "确认情况：" + ack);
                System.out.println("ConfirmCallback:     " + "原因：" + cause);
            }
        });

        rabbitTemplate.setReturnCallback(new RabbitTemplate.ReturnCallback() {
            @Override
            public void returnedMessage(Message message, int replyCode, String replyText, String exchange, String routingKey) {
                System.out.println("ReturnCallback:     " + "消息："+message);
                System.out.println("ReturnCallback:     " + "回应码："+replyCode);
                System.out.println("ReturnCallback:     " + "回应信息："+replyText);
                System.out.println("ReturnCallback:     " + "交换机："+exchange);
                System.out.println("ReturnCallback:     " + "路由键："+routingKey);
            }
        });

        return rabbitTemplate;
    }

}
```

可以看到上面写了两个回调函数，一个叫 `ConfirmCallback` ，一个叫 `RetrunCallback`；

❓ 那么以上这两种回调函数都是在什么情况会触发呢？

⭐ 先从总体的情况分析，**推送消息存在四种情况**：

- ① 消息推送到 server，但是在 server 里找不到交换机
- ② 消息推送到 server，找到交换机了，但是没找到队列
- ③ 消息推送到 sever，交换机和队列啥都没找到
- ④ 消息推送成功

那么我先写几个接口来分别测试和认证下以上4种情况，消息确认触发回调函数的情况：

#### Ⅰ 消息推送到 server，但是在 server 里找不到交换机

写个测试接口，把消息推送到名为 ‘`non-existent-exchange`’ 的交换机上（**这个交换机是没有创建没有配置的**）：

```java
    @GetMapping("/TestMessageAck")
    public String TestMessageAck() {
        String messageId = String.valueOf(UUID.randomUUID());
        String messageData = "message: non-existent-exchange test message ";
        String createTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        Map<String, Object> map = new HashMap<>();
        map.put("messageId", messageId);
        map.put("messageData", messageData);
        map.put("createTime", createTime);
        rabbitTemplate.convertAndSend("non-existent-exchange", "TestDirectRouting", map);
        return "ok";
    }
```

调用接口，查看 rabbitmq-provider项目的控制台输出情况：

```java
ConfirmCallback:     相关数据：null
ConfirmCallback:     确认情况：false
ConfirmCallback:     原因：channel error; protocol method: #method<channel.close>(reply-code=404, reply-text=NOT_FOUND - no exchange 'non-existent-exchange' in vhost 'JCcccHost', class-id=60, method-id=40)
```

😄 **结论： ① 这种情况触发的是 `ConfirmCallback` 回调函数。**

#### Ⅱ 消息推送到 server，找到交换机了，但是没找到队列 

我们**新增一个交换机，但是不给这个交换机绑定队列**，我来简单地在 DirectRabitConfig 里面新增一个直连交换机，名叫 ‘`lonelyDirectExchange`’，但没给它做任何绑定配置操作：

```java
    @Bean
    DirectExchange lonelyDirectExchange() {
        return new DirectExchange("lonelyDirectExchange");
    }
```

然后写个测试接口，把消息推送到名为‘`lonelyDirectExchange`’的交换机上（这个交换机是没有任何队列配置的）：

```java
    @GetMapping("/TestMessageAck2")
    public String TestMessageAck2() {
        String messageId = String.valueOf(UUID.randomUUID());
        String messageData = "message: lonelyDirectExchange test message ";
        String createTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        Map<String, Object> map = new HashMap<>();
        map.put("messageId", messageId);
        map.put("messageData", messageData);
        map.put("createTime", createTime);
        rabbitTemplate.convertAndSend("lonelyDirectExchange", "TestDirectRouting", map);
        return "ok";
    }
```

调用接口，查看 rabbitmq-provider 项目的控制台输出情况：

```java
ReturnCallback:     回应码：312
ReturnCallback:     回应信息：NO_ROUTE
ReturnCallback:     交换机：lonelyDirectExchange
ReturnCallback:     路由键：TestDirectRouting
    
ConfirmCallback:     相关数据：null
ConfirmCallback:     确认情况：true
ConfirmCallback:     原因：null
```

可以看到这种情况，两个函数都被调用了；

这种情况下，消息是推送成功到服务器了的，所以 `ConfirmCallback` 对消息确认情况是 true；

而在 `RetrunCallback` 回调函数的打印参数里面可以看到，消息是推送到了交换机成功了，但是在路由分发给队列的时候，找不到队列，所以报了错误 NO_ROUTE 。

**😄 结论：② 这种情况触发的是 `ConfirmCallback` 和 `RetrunCallback` 两个回调函数。**

#### Ⅲ 消息推送到 sever，交换机和队列啥都没找到 

这种情况其实一看就觉得跟 ① 很像，没错 ，**③ 和 ① 情况回调是一致的**，所以不做结果说明了。

**😄 结论： ③ 这种情况触发的是 `ConfirmCallback` 回调函数。**

#### Ⅳ 消息推送成功

按照正常调用之前消息推送的接口就行，就调用下 /`sendFanoutMessage` 接口，可以看到控制台输出：

```java
ConfirmCallback:     相关数据：null
ConfirmCallback:     确认情况：true
ConfirmCallback:     原因：null
```

**😄 结论： ④ 这种情况触发的是 `ConfirmCallback` 回调函数。**

### ② 消费者收到消息的消息确认机制

和生产者的消息确认机制不同，因为消息接收本来就是在监听消息，符合条件的消息就会消费下来。所以，消息接收的确认机制主要存在**三种**模式：

- 💥 **自动确认 `AcknowledgeMode.NONE`**， 这也是**默认**的消息确认情况。 

  **RabbitMQ 成功将消息发出后立即认为本次投递已经被正确处理，不管消费者端是否成功处理本次投递。**

  <u>所以这种情况如果消费端消费逻辑抛出异常，也就是消费端没有处理成功这条消息，那么就相当于丢失了消息。一般这种情况我们都是使用 try catch 捕捉异常后，打印日志用于追踪数据，这样找出对应数据再做后续处理。</u>

- 💥 **根据情况确认**， 这个不做介绍

- 💥 **手动确认 `AcknowledgeMode.MANUAL`** ， 这个比较关键，也是我们配置接收消息确认机制时，多数选择的模式。

  消费者收到消息后，手动调用 `basic.ack/basic.nack/basic.reject` ，RabbitMQ 收到这些消息后，才认为本次投递成功。

  - `basic.ack` 用于肯定确认 

  - `basic.nack` 用于否定确认（注意：这是AMQP 0-9-1的RabbitMQ扩展） 

    `channel.basicNack(deliveryTag, false, true)`：

    - 第一个参数依然是当前消息到的数据的唯一 id

    - 第二个参数是指是否针对多条消息；如果是 true，也就是说一次性针对当前通道的消息的 tagID 小于当前这条消息的，都拒绝确认

    - 第三个参数是指是否重新入列，也就是指不确认的消息是否重新丢回到队列里面去。

      **使用拒绝后重新入列这个确认模式要谨**慎，因为一般都是出现异常的时候，catch异常再拒绝入列。如果使用不当会导致一些每次都被你重入列的消息一直 消费-入列-消费-入列 这样循环，会导致消息积压。

  - `basic.reject` 用于否定确认，但与 `basic.nack` 相比有一个限制，即一次只能拒绝单条消息 

    `channel.basicReject(deliveryTag, true)`：拒绝消费当前消息。

    - 如果第二参数传入 true：就是将数据重新丢回队列里，那么下次还会消费这消息

      同样使用拒绝后重新入列这个确认模式要谨慎

    - 如果第二参数设置 false，就是告诉服务器，我已经知道这条消息数据了，因为一些原因拒绝它，而且服务器也把这个消息丢掉就行。 下次不想再消费这条消息了

💧 消费者端以上的 3 个方法都表示消息已经被正确投递，但是**只有 `basic.ack` 表示消息已经被正确处理。而 `basic.nack` , `basic.reject` 表示没有被正确处理**

<br>

接下来我们一起配置下，看看一般的消息接收 手动确认是怎么样的。

在消费者项目里，新建 `MessageListenerConfig.java`，添加相关的配置代码：

```java
import com.elegant.rabbitmqconsumer.receiver.MyAckReceiver;
import org.springframework.amqp.core.AcknowledgeMode;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.rabbit.connection.CachingConnectionFactory;
import org.springframework.amqp.rabbit.listener.SimpleMessageListenerContainer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
 
@Configuration
public class MessageListenerConfig {
 
    @Autowired
    private CachingConnectionFactory connectionFactory;
    @Autowired
    private MyAckReceiver myAckReceiver; //消息接收处理类
 
    @Bean
    public SimpleMessageListenerContainer simpleMessageListenerContainer() {
        SimpleMessageListenerContainer container = new SimpleMessageListenerContainer(connectionFactory);
        container.setConcurrentConsumers(1);
        container.setMaxConcurrentConsumers(1);
        container.setAcknowledgeMode(AcknowledgeMode.MANUAL); // RabbitMQ 默认是自动确认，这里改为手动确认消息
        // 设置一个队列
        container.setQueueNames("DirectQueue");
        
        container.setMessageListener(myAckReceiver);
 
        return container;
    }
 
 
}
```

其中，对应的**手动确认消息监听类** `MyAckReceiver.java`（手动确认模式需要实现 `ChannelAwareMessageListener`）：

> 🚨 之前的相关监听器可以先注释掉，以免造成多个同类型监听器都监听同一个队列。

这里的获取消息转换，只作参考，如果报数组越界可以自己根据格式去调整

```java
import com.rabbitmq.client.Channel;
import org.springframework.amqp.core.Message;
import org.springframework.amqp.rabbit.listener.api.ChannelAwareMessageListener;
import org.springframework.stereotype.Component;
import java.util.HashMap;
import java.util.Map;
 
@Component
public class MyAckReceiver implements ChannelAwareMessageListener {
 
    @Override
    public void onMessage(Message message, Channel channel) throws Exception {
        long deliveryTag = message.getMessageProperties().getDeliveryTag();
        try {
            // 因为传递消息的时候用的map传递,所以将Map从Message内取出需要做些处理
            String msg = message.toString();
            String[] msgArray = msg.split("'");//可以点进Message里面看源码,单引号之间的数据就是我们的map消息数据
            Map<String, String> msgMap = mapStringToMap(msgArray[1].trim(),3);
            String messageId=msgMap.get("messageId");
            String messageData=msgMap.get("messageData");
            String createTime=msgMap.get("createTime");
            System.out.println("  MyAckReceiver  messageId:" + messageId+"  messageData:" + messageData + "  createTime:" + createTime);
            System.out.println("消费的主题消息来自："+message.getMessageProperties().getConsumerQueue());
            channel.basicAck(deliveryTag, true); // 第二个参数，手动确认可以被批处理，当该参数为 true 时，则可以一次性确认 delivery_tag 小于等于传入值的所有消息
//			channel.basicReject(deliveryTag, true);// 第二个参数 true 消息会重新放回队列，所以需要自己根据业务逻辑判断什么时候使用拒绝
        } catch (Exception e) {
            channel.basicReject(deliveryTag, false);
            e.printStackTrace();
        }
    }
 
    // {key=value,key=value,key=value} 格式转换成map
    private Map<String, String> mapStringToMap(String str,int entryNum ) {
        str = str.substring(1, str.length() - 1);
        String[] strs = str.split(",",entryNum);
        Map<String, String> map = new HashMap<String, String>();
        for (String string : strs) {
            String key = string.split("=")[0].trim();
            String value = string.split("=")[1];
            map.put(key, value);
        }
        return map;
    }
}
```

这时，先调用接口` /sendDirectMessage`， 给直连交换机 `DirectExchange` 的队列 `DirectQueue` 推送一条消息，就可以看到监听器正常消费了下来

#### 多队列的手动确认

上述代码中，我们仅仅将直连交换机的队列 DirectQueue 变成手动确认了，接下来我们将多个队列也改成手动确认模式，而且不同队列实现不同的业务处理。

第一步就是往 `SimpleMessageListenerContainer` 里添加多个队列：

```java
// 设置一个队列
// container.setQueueNames("DirectQueue");

// 同时设置多个队列： 前提是队列都是必须已经创建存在的
container.setQueueNames("DirectQueue","DirectQueue2","DirectQueue3");

// 另一种设置多个队列的方法，使用 addQueues
container.setQueues(new Queue("DirectQueue",true));
container.addQueues(new Queue("DirectQueue2",true));
container.addQueues(new Queue("DirectQueue3",true));
```

然后我们的手动确认消息监听类 `MyAckReceiver.java` 就可以同时将上面设置到的队列的消息都消费下来。

**如果我们需要做不同的业务逻辑处理**，那么只需要 **根据消息来自的队列名进行区分处理 **即可，如：

```java
@Component
public class MyAckReceiver implements ChannelAwareMessageListener {
 
    @Override
    public void onMessage(Message message, Channel channel) throws Exception {
        long deliveryTag = message.getMessageProperties().getDeliveryTag();
        try {
            ..........
            
            if ("DirectQueue".equals(message.getMessageProperties().getConsumerQueue())){
                System.out.println("消费的消息来自的队列名为："+message.getMessageProperties().getConsumerQueue());
                System.out.println("消息成功消费到  messageId:"+messageId+"  messageData:"+messageData+"  createTime:"+createTime);
                System.out.println("执行DirectQueue中的消息的业务处理流程......");
                
            }
 
            if ("fanout.A".equals(message.getMessageProperties().getConsumerQueue())){
                System.out.println("消费的消息来自的队列名为："+message.getMessageProperties().getConsumerQueue());
                System.out.println("消息成功消费到  messageId:"+messageId+"  messageData:"+messageData+"  createTime:"+createTime);
                System.out.println("执行fanout.A中的消息的业务处理流程......");
 
            }
            
            channel.basicAck(deliveryTag, true);
            
        } catch (Exception e) {
            ..........
        }
    }
 
    // {key=value,key=value,key=value} 格式转换成map
    private Map<String, String> mapStringToMap(String str,int enNum) {
        ......
    }
}
```

OK，我们调用接口 `/sendDirectMessage` 和 `/sendFanoutMessage` 分别往不同队列推送消息，看看效果。

## 📚 References

- [Springboot 整合 RabbitMq ，用心看完这一篇就够了](https://blog.csdn.net/qq_35387940/article/details/100514134)