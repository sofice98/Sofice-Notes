 Spring 是分层的 Java SE/EE应用 full-stack 轻量级开源框架，<strong>以 IoC（Inverse Of Control： 控制反转）和 AOP（Aspect Oriented Programming：面向切面编程）为内核</strong>，提供了展现层 Spring MVC 和持久层 Spring JDBC 以及业务层事务管理等众多的企业级应用技术，还能整合开源世界众多著名的第三方框架和类库，逐渐成为使用最多的Java EE 企业应用开源框架。

<img src="http://mdimg.sofice.top/202112111339305.png" alt="img" style="zoom:75%;" />

- **Spring Core：** 基础,可以说 Spring 其他所有的功能都需要依赖于该类库。主要提供 IoC 依赖注入功能。
- **Spring Aspects** ： 该模块为与 AspectJ 的集成提供支持。
- **Spring AOP** ：提供了面向切面的编程实现。
- **Spring JDBC** : Java 数据库连接。
- **Spring JMS** ：Java 消息服务。
- **Spring ORM** : 用于支持 Hibernate 等 ORM 工具。
- **Spring Web** : 为创建 Web 应用程序提供支持。
- **Spring Test** : 提供了对 JUnit 和 TestNG 测试的支持。

# IoC（Inverse of Control，控制反转）

IoC 是一种**设计思想**，就是将原本在程序中手动创建对象的控制权，交由Spring框架来管理。**不使用IoC时，程序员把调用写死，修改业务涉及到更改许多代码；而IoC把主动权交给用户，可以让程序员专注于修改业务，对象动态的变化交给框架，耦合性大大降低。**

**IoC 容器**是 Spring 用来实现 IoC 的**载体**，实现的**方法**时依赖注入（Dependency Injection，DI）。IoC 容器实际上就是个**Map（key，value）**,Map 中存放的是各种对象。

loC 容器就像是一个工厂一样，当我们需要创建一个对象的时候**，只需要配置好配置文件/注解即可**

优点：完全不用考虑对象是如何被创建出来的，共享一个组件非常简单

主要作用为：将组件的创建+配置与组件的使用相分离，并且，由IoC容器负责管理组件的生命周期

**无侵入容器**

在设计上，Spring的IoC容器是一个高度可扩展的无侵入容器。所谓无侵入，是指应用程序的组件无需实现Spring的特定接口，或者说，组件根本不知道自己在Spring的容器中运行。这种无侵入的设计有以下好处：

1. 应用程序组件既可以在Spring的IoC容器中运行，也可以自己编写代码自行组装配置；
2. 测试的时候并不依赖Spring容器，可单独进行测试，大大提高了开发效率。

<img src="http://mdimg.sofice.top/202112111339448.png" alt="image-20211126162812986" style="zoom:50%;" />

**依赖注入**

依赖注入，是 IOC 的一个方面。即不用创建对象，而只需要描述它如何被创建，之后一个容器（IOC 容器）负责把他们组装起来。

**依赖注入方式**

- **构造器依赖注入：**构造器依赖注入通过容器触发一个类的构造器来实现的，该类有一系列参数，每个参数代表一个对其他类的依赖。

- **Setter 方法注入：**Setter 方法注入是容器通过调用无参构造器或无参 static 工厂方法实例化 bean 之后，调用该 bean 的 setter 方法，即实现了基于 setter 的依赖注入。

用构造器参数实现强制依赖，setter 方法实现可选依赖。



# ApplicationContext

寻找Bean，加载Bean的配置文件

实现方法：

- **FileSystemXmlApplicationContext：**此容器从一个 XML 文件中加载 beans 的定义，XMLBean 配置文件的全路径名必须提供给它的构造函数。

- **ClassPathXmlApplicationContext：**此容器也从一个 XML 文件中加载 beans 的定义，这里，你需要正确设置 classpath 因为这个容器将在 classpath 里找 bean 配置。

- **WebXmlApplicationContext：**此容器加载一个 XML 文件，此文件定义了一个 WEB 应用的所有 bean。

```java
// 从类路径ClassPath中寻找
// 装载单个配置文件
ApplicationContext cxt = new ClassPathXmlApplicationContext("applicationContext.xml");
// 装载多个配置文件
String configs = {"bean1.xml","bean2.xml","bean3.xml"};
ApplicationContext cxt = new ClassPathXmlApplicationContext(configs);

// 从指定的文件系统路径中寻找
// 装载单个配置文件
ApplicationContext cxt = new FileSystemXmlApplicationContext("c:/applicationContext.xml");
// 装载多个配置文件
String configs = {"c:/bean1.xml","c:/bean2.xml","c:/bean3.xml"};
ApplicationContext cxt = new FileSystemXmlApplicationContext(configs);

// 读取注解创建容器
AnnotationConfigApplicationContext
```

alias：别名

import：导入其他配置文件



:question: Bean 工厂和 Applicationcontexts 有什么区别

Applicationcontexts 提供一种方法处理文本消息，一个通常的做法是加载文件资源（比如镜像），它们可以向注册为监听器的 bean 发布事件。另外，在容器或容器内的对象上执行的那些不得不由 bean 工厂以程序化方式处理的操作，可以在 Applicationcontexts 中以声明的方式处理。Applicationcontexts 实现了MessageSource 接口，该接口的实现以可插拔的方式提供获取本地化消息的方法。

# Bean

自动创建对象并赋值

注解注入在 XML 注入之前执行。

注解与xml：注解编写方便， 但维护相对复杂；xml编写复杂，但更加万能，维护简单。

一般xml管理Bean，注解配置其他。

## 装配

**Xml 配置**

1. **使用默认无参构造函数**

   在 Spring 的配置文件中使用 bean 标签，配以 id 和 class 属性后，且没有其他属性和标签时。采用的就是默认构造函数创建 bean 对象；此时如果 bean 中没有默认无参构造函数，将会创建失败

   ```xml
   <bean id="dataSource" class="com.zaxxer.hikari.HikariDataSource">
       <property name="jdbcUrl" value="jdbc:mysql://localhost:3306/test" />
       <property name="username" value="root" />
       <property name="password" value="password" />
       <property name="maximumPoolSize" value="10" />
       <property name="autoCommit" value="true" />
   </bean>
   ```

2. **自动装配**

    ```xml
    <bean id="cat" class="com.szy.pojo.Cat" />
    <bean id="dog" class="com.szy.pojo.Dog" />
    
    <bean id="people" class="com.szy.pojo.People" autowire="byName">
        <property name="name" value="司展宇"/>
    </bean>
    ```

3. **使用简单工厂模式的方法创建**（使用某个类中的方法创建对象，并存入 Spring 容器）

   ```java
     /** 
      * 模拟一个工厂类
      * 该类可能是存在于jar包中的，我们无法通过修改源码的方式来提供默认构造函数
      * 此工厂创建对象，必须先有工厂实例对象，再调用方法  
      */ 
     public class InstanceFactory {   
         public IAccountService createAccountService(){   
             return new AccountServiceImpl();  
         }
     }
   ```

   ```xml
   <bean id = "InstanceFactory" class = "com.smallbeef.factory.InstanceFactory"></bean>
   
   <bean id="accountService"  
         factory-bean="InstanceFactory"     
         factory-method="createAccountService">
   </bean>
   ```

4. **使用静态工厂的方法创建对象**（使用某个类中的**静态方法**创建对象，并存入 Spring 容器）

    ```java
    /** 
     * 模拟一个静态工厂类
     * 该类可能是存在于jar包中的，我们无法通过修改源码的方式来提供默认构造函数
     */ 
    public class StaticFactory {   
        public static IAccountService createAccountService(){   
            return new AccountServiceImpl();  
        } 
    }
    ```

    ```xml
    <bean id="accountService"  
          class="com.smallbeef.factory.StaticFactory"     
          factory-method="createAccountService">
    </bean>
    ```



**注解配置**

以下注解的作用和在 XML 配置文件中编写一个 bean 标签实现的功能是一样的 , 用于把当前类对象存入 Spring 容器中

使用以下注解的时候，需要在 xml 文件中配置如下:（当然，其他的 bean 注册配置就不用写了，配合下面注解这一行就可以了）

```xml
<context:annotation-config/>
```

然后在pojo里组合的字段上加：`@Autowired`，通过byname方式实现。也可用java原生注解：`@Resource`

**component扫描器**：

```xml
 <!--告知Spirng在创建容器时要扫描的包，配置所需要的标签不是在beans的约束中，而是一个名称为context空间和约束中-->
<context:component-scan base-package="com.smallbeef" />
```

- `@Component`：value属性——用于指定 bean 的 id 。当我们不写时，他的默认值是当前类名，且首字母小写。

- `@Controller`：一般用于【控制层】的注解。

- `@Service`：一般用于【业务层】的注解。

- `@Repository `：一般用于【数据层】的注解。 

上述四个注解可以随意互换, 作用相同,  都是用于用于把当前类对象存入 Spring 容器中, 只不过后面三个注解提供了更具体的语义化

```java
@Service // value 默认值为小写开头的类名
@Scope("prototype") // 多例模式
public class AccountServiceImpl implements IAccountService {
    @Autowired // 自动装配。@Resource的作用相当于@Autowired，只不过@Autowired按byType自动注入，而@Resource默认按 byName自动注入
    @Qualifier("alias") // 别名
    @Value("司展宇") // 简单的初始化
    MailService mailService;
 	// doSomething
}
```



**JavaConfig**

```java
@Configuration // 配置类，相当于xml
public class Config{
    @Bean
    public User getUser(){
        return new User;
    }
}
```





## 获取

**Xml 配置**

通过`getBean`方法来从 Spring 容器中获取 Bean，传入的参数是 Bean 的 name 或者 id 属性

也可以直接通过 Class 去获取一个 Bean，但这种方式存在一个很大的弊端，如果存在多个实例（多个 Bean），这种方式就不可用。所以一般建议通过 name 或者 id 去获取 Bean 的实例

```java
// bean.xml
<bean id = "accountServiceImpl" class = "com.smallbeef.service.impl.AccountServiceImpl"></bean>
// .java
public class Client {
    public static void main(String[] args) {
        ApplicationContext cxt = new ClassPathXmlApplicationContext("bean.xml");
        IAccountService aService = cxt.getBean(accountServiceImpl);
        IAccountService aService = cxt.getBean(IAccountService.class);
    }
}
```

**注解配置**

```java
@Configuration
@ComponentScan
public class AppConfig {
    public static void main(String[] args) {
        ApplicationContext cxt = new AnnotationConfigApplicationContext(AppConfig.class);
        UserService userService = cxt.getBean(UserService.class);
        User user = userService.login("bob@example.com", "password");
        System.out.println(user.getName());
    }
}
```

使用的实现类是`AnnotationConfigApplicationContext`，必须传入一个标注了`@Configuration`的类名。

此外，`AppConfig`还标注了`@ComponentScan`，它告诉容器，自动搜索当前类所在的包以及子包，把所有标注为`@Component`的Bean自动创建出来，并根据`@Autowired`进行装配

## 定制Bean

### 作用范围

从 Spring 容器中多次获取同一个Bean，默认情况下，获取到的实际上是同一个实例，即默认是单例（Singleton）的。当然，我们可以手动配置，使每次调用`getBean(Class)`，容器都返回一个新的实例，这种Bean称为原型（Prototype）

**Xml配置**

```xml
<bean class = "com.smallbeef.dao.useDaoImpl" id = "userDao" scope = "prototype"/>
```

bean 标签的 `scope` 属性就是用来指定 bean 的作用范围的

- singleton：默认值，单例的（bean对象默认是单例模式）
- prototype：多例的
- request：作用于web应用的请求范围。WEB 项目中，Spring 创建一个 Bean 的对象，将对象存入到 request 域中
- session：作用于web应用的会话范围。WEB 项目中，Spring 创建一个 Bean 的对象，将对象存入到 session 域中
- global-session：作用于集群环境的会话范围。WEB 项目中，应用在 Portlet（集群） 环境。如果没有 Portlet 环境那么 global-session 相当于 session

**注解配置**

当然，除了使用 bean 标签在 xml 中进行配置，我们也可以在 Java 代码中使用注解 `@Scope` 来配置Bean的作用范围

```java
@Repository
@Scope("prototype")
public calss UserDao{
    public String hello(){
        return "hello";
    }
}
```



###  生命周期 

- **单例对象**  `scope="singleton"`

  一个应用只有一个对象的实例。它的作用范围就是整个引用。

  生命周期：

  - 对象出生：当应用加载，创建容器时，对象就被创建了

  - 对象活着：只要容器在，对象一直活着。

  - 对象死亡：当应用卸载，销毁容器时，对象就被销毁了


  总结： **单例对象的生命周期和容器相同**

- **多例对象**  `scope="prototype"`

  每次访问对象时，都会重新创建对象实例。

  生命周期：

  - 对象出生：当使用对象时，才会创建新的对象实例

  - 对象活着：只要对象在使用中，就一直活着。

  - 对象死亡：**当对象长时间不用，且没有别的对象引用时，由 java 的垃圾回收器进行回收。**



**Xml 配置**

bean 标签：

- `init-method`：指定类中的初始化方法名称。
- `destroy-method`：指定类中销毁方法名称。

```xml
<bean class = "com.smallbeef.dao.useDaoImpl" id = "userDao" scope = "prototype" init-method = "" destroy-method = ""/>
```

**注解配置**

```xml
<dependency>
    <groupId>javax.annotation</groupId>
    <artifactId>javax.annotation-api</artifactId>
    <version>1.3.2</version>
</dependency>
```

- @PreDestroy：指定销毁方法

- @PostConstruct：指定初始化方法




### 注入List

有些时候，我们会有一系列接口相同，不同实现类的Bean。例如，注册用户时，我们要对email、password和name这3个变量进行验证。为了便于扩展，我们先定义验证接口：

```java
public interface Validator {
    void validate(String email, String password, String name);
}
```

然后，分别使用3个`Validator`对用户参数进行验证：

```java
@Component
@Order(1)
public class EmailValidator implements Validator {
    public void validate(String email, String password, String name) {
        if (!email.matches("^[a-z0-9]+\\@[a-z0-9]+\\.[a-z]{2,10}$")) {
            throw new IllegalArgumentException("invalid email: " + email);
        }
    }
}

@Component
@Order(2)
public class PasswordValidator implements Validator {
    public void validate(String email, String password, String name) {
        if (!password.matches("^.{6,20}$")) {
            throw new IllegalArgumentException("invalid password");
        }
    }
}

@Component
@Order(3)
public class NameValidator implements Validator {
    public void validate(String email, String password, String name) {
        if (name == null || name.isBlank() || name.length() > 20) {
            throw new IllegalArgumentException("invalid name: " + name);
        }
    }
}
```

最后，我们通过一个`Validators`作为入口进行验证：

```java
@Component
public class Validators {
    @Autowired
    List<Validator> validators;

    public void validate(String email, String password, String name) {
        for (var validator : this.validators) {
            validator.validate(email, password, name);
        }
    }
}
```





### 可选注入

默认情况下，当我们标记了一个`@Autowired`后，Spring如果没有找到对应类型的Bean，它会抛出`NoSuchBeanDefinitionException`异常。

可以给`@Autowired`增加一个`required = false`的参数：

```java
@Component
public class MailService {
    @Autowired(required = false)
    ZoneId zoneId = ZoneId.systemDefault();
    ...
}
```

适合有定义就使用定义，没有就使用默认值的情况



### 创建第三方Bean

如果一个Bean不在我们自己的package管理之内，例如`ZoneId`，如何创建它？

答案是我们自己在`@Configuration`类中编写一个Java方法创建并返回它，注意给方法标记一个`@Bean`注解：

```java
@Configuration
@ComponentScan
public class AppConfig {
    // 创建一个Bean并指定别名
    @Bean("z")
    // 也可用@Qualifier指定别名
    @Qualifier("z")
    // 将主（默认）数据源定义为@Primary
    @Primary
    ZoneId createZoneId() {
        return ZoneId.of("Z");
    }
}

@Autowired(required = false)
// 指定注入名称为"z"的ZoneId
@Qualifier("z") 
ZoneId zoneId = ZoneId.systemDefault();
```

Spring对标记为`@Bean`的方法只调用一次，因此返回的Bean仍然是单例



### FactoryBean

用工厂模式创建Bean需要实现`FactoryBean`接口。我们观察下面的代码：

```java
@Component
public class ZoneIdFactoryBean implements FactoryBean<ZoneId> {

    String zone = "Z";

    @Override
    public ZoneId getObject() throws Exception {
        return ZoneId.of(zone);
    }

    @Override
    public Class<?> getObjectType() {
        return ZoneId.class;
    }
}
```

当一个Bean实现了`FactoryBean`接口后，Spring会先实例化这个工厂，然后调用`getObject()`创建真正的Bean。`getObjectType()`可以指定创建的Bean的类型，因为指定类型不一定与实际类型一致，可以是接口或抽象类。

因此，如果定义了一个`FactoryBean`，要注意Spring创建的Bean实际上是这个`FactoryBean`的`getObject()`方法返回的Bean。为了和普通Bean区分，我们通常都以`XxxFactoryBean`命名。



## 使用Resource

```java
@Component
public class AppService {
    // 在resources中搜索logo.txt文件，也可以直接指定文件的路径
    @Value("classpath:/logo.txt")
    private Resource resource;

    private String logo;

    @PostConstruct
    public void init() throws IOException {
        // 使用resource.getInputStream()获得输入流
        try (var reader = new BufferedReader(
                new InputStreamReader(resource.getInputStream(), StandardCharsets.UTF_8))) {
            this.logo = reader.lines().collect(Collectors.joining("\n"));
        }
    }
}
```



## 注入配置

Spring容器还提供了一个更简单的`@PropertySource`来自动读取配置文件。我们只需要在`@Configuration`配置类上再添加一个注解：

```java
@Configuration
@ComponentScan
@PropertySource("app.properties") // 表示读取classpath的app.properties
public class AppConfig {
    @Value("${app.zone:Z}")
    String zoneId;

    @Bean
    ZoneId createZoneId() {
        return ZoneId.of(zoneId);
    }
}
```

注意注入的字符串语法，它的格式如下：

- `"${app.zone}"`表示读取key为`app.zone`的value，如果key不存在，启动将报错
- `"${app.zone:Z}"`表示读取key为`app.zone`的value，但如果key不存在，就使用默认值`Z`

还可以把注入的注解写到方法参数中



另一种注入配置的方式是先通过一个简单的JavaBean持有所有的配置，例如，一个`SmtpConfig`：

```java
@Component
public class SmtpConfig {
    @Value("${smtp.host}")
    private String host;

    @Value("${smtp.port:25}")
    private int port;

    public String getHost() {
        return host;
    }

    public int getPort() {
        return port;
    }
}
```

然后，在需要读取的地方，使用`#{smtpConfig.host}`注入：

```java
@Component
public class MailService {
    @Value("#{smtpConfig.host}")
    private String smtpHost;

    @Value("#{smtpConfig.port}")
    private int smtpPort;
}
```

使用一个独立的JavaBean持有所有属性，然后在其他Bean中以`#{bean.property}`注入的好处是，多个Bean都可以引用同一个Bean的某个属性。例如，如果`SmtpConfig`决定从数据库中读取相关配置项，那么`MailService`注入的`@Value("#{smtpConfig.host}")`仍然可以不修改正常运行



## 条件装配

开发应用程序时，我们会使用开发环境，例如，使用内存数据库以便快速启动。而运行在生产环境时，我们会使用生产环境，例如，使用MySQL数据库。如果应用程序可以根据自身的环境做一些适配，无疑会更加灵活。

Spring为应用程序准备了Profile这一概念，用来表示不同的环境。例如，我们分别定义开发、测试和生产这3个环境：

- native
- test
- production

创建某个Bean时，Spring容器可以根据注解`@Profile`来决定是否创建。例如，以下配置：

```java
@Configuration
@ComponentScan
public class AppConfig {
    @Bean
    @Profile("!test")
    ZoneId createZoneId() {
        return ZoneId.systemDefault();
    }

    @Bean
    @Profile("test")
    ZoneId createZoneIdForTest() {
        return ZoneId.of("America/New_York");
    }
}
```

如果当前的Profile设置为`test`，则Spring容器会调用`createZoneIdForTest()`创建`ZoneId`，否则，调用`createZoneId()`创建`ZoneId`。注意到`@Profile("!test")`表示非test环境。

在运行程序时，加上JVM参数`-Dspring.profiles.active=test`就可以指定以`test`环境启动。

实际上，Spring允许指定多个Profile，例如：

```
-Dspring.profiles.active=test,master
```

可以表示`test`环境，并使用`master`分支代码。

要满足多个Profile条件，可以这样写：

```java
@Bean
@Profile({ "test", "master" }) // 同时满足test和master
ZoneId createZoneId() {
    ...
}
```





# AOP（Aspect Oriented Programming，面向切面编程）

纵向开发：dao-service-controller-前端。在纵向开发结束后，需要横向的，面向切面的，不改变原有代码的开发，如加入日志等

**Xml 配置**

```xml
<dependency>
    <groupId>org.aspectj</groupId>
    <artifactId>aspectjweaver</artifactId>
    <version>1.9.6</version>
</dependency>
```

```java
// 前缀日志
public class Log implements MethodBeforeAdvice {
    public void before(Method method, Object[] objects, Object o) throws Throwable {
        System.out.println("before:"+o.getClass().getName()+" method:"+method.getName());
    }
}
```

```xml
<!--配置aop-->
<aop:config>
    <!--切入点 execution表达式匹配，execution(返回类型 包.类.方法(参数))-->
    <aop:pointcut id="pointcut" expression="execution(* com.szy.service.UserServiceImpl.*(..))"/>
    <!--执行前缀增加-->
    <aop:advisor advice-ref="log" pointcut-ref="pointcut" />
</aop:config>
```

**自定义AOP**

```java
// 自定义log类
public class DiyLog {
    public void before(){
        System.out.println("before");
    }
    public void after(){
        System.out.println("after");
    }
}
```

```xml
<bean id="diyLog" class="com.szy.log.DiyLog"/>
<!--配置aop-->
<aop:config>
    <!--自定义切面-->
    <aop:aspect ref="diyLog">
        <aop:pointcut id="pointcut" expression="execution(* com.szy.service.UserServiceImpl.*(..))"/>
        <aop:before method="before" pointcut-ref="pointcut"/>
        <aop:after method="after" pointcut-ref="pointcut"/>
    </aop:aspect>
</aop:config>
```

**注解配置**

```xml
<!--开启注解支持-->
<aop:aspectj-autoproxy/>
```

```java
@Aspect
public class DiyLog {
    @Before("execution(* com.szy.service.UserServiceImpl.*(..))")
    public void before(){
        System.out.println("before");
    }
    @After("execution(* com.szy.service.UserServiceImpl.*(..))")
    public void after(){
        System.out.println("after");
    }
}
```



# 事务管理

Spring 中支持两种方式事务管理：

1）基于 `TransactionTemplate` 的**编程式事务**，实际中很少使用

2）基于 xml 配置或者注解 `@Transactional` 的**声明式事务**。



**声明式事务**

通过 AOP 实现的，其本质是对方法前后进行拦截，然后在目标方法开始之前创建或者加入一个事务，在执行完目标方法之后根据执行情况提交或者回滚事务。

- 优：非侵入式编程，业务逻辑不受污染。

- 缺：最细粒度只能作用到方法级别。

```java
// isolation 隔离级别, propagation 传播行为。
@Transactional(isolation = Isolation.READ_COMMITTED, propagation = Propagation.REQUIRED)
```

隔离级别主要定义了如下 5 种：

```java
public enum Isolation {
    DEFAULT(-1),			// 使用底层数据库的默认隔离级别
    READ_UNCOMMITTED(1), 	// 读取未提交
    READ_COMMITTED(2), 		// 读取已提交
    REPEATABLE_READ(4),		// 可重复读
    SERIALIZABLE(8);		// 可序列化
}
```

传播行为主要有 7 种，意思就是说如果在开始当前事务之前，一个事务上下文已经存在了，那么你有这 7 种选择可以指定当前事务接下来的执行行为：

```java
public enum Propagation {
    REQUIRED(0),			// 如果当前存在事务，则加入该事务；如果当前没有事务，则创建一个新的事务。
    SUPPORTS(1),			// 如果当前存在事务，则加入该事务；如果当前没有事务，则以非事务的方式继续运行。
    MANDATORY(2),			// 如果当前存在事务，则加入该事务；如果当前没有事务，则抛出异常。
    REQUIRES_NEW(3),		// 创建一个新的事务，如果当前存在事务，则把当前事务挂起。
    NOT_SUPPORTED(4),		// 以非事务方式运行，如果当前存在事务，则把当前事务挂起。
    NEVER(5),				// 以非事务方式运行，如果当前存在事务，则抛出异常。
    NESTED(6);				// 如果当前存在事务，则创建一个事务作为当前事务的嵌套事务来运行；如果当前没有事务，则该取值等价于REQUIRED。
}
```





# Mybatis

https://mybatis.org/mybatis-3/zh/index.html

**DAO(Data Access Object)**：在传统的多层应用程序中，通常是Web层调用业务层，业务层调用数据访问层。业务层负责处理各种业务逻辑，而数据访问层只负责对数据进行增删改查。编写数据访问层的时候，可以使用DAO(Data Access Object)模式。



- SqlSessionFactoryBuilder：用来创建SqlSessionFactory，使用完后可丢弃，最好为局部作用域，使用建造者模式。
- SqlSessionFactory：用来创建SqlSession，应用运行期间应该一直存在，且不应被创建多次，最好单例模式或静态模式。
- SqlSession：用来创建DAO的mapper实例。每个线程都应该有自己的SqlSession实例，它不是线程安全，不能被共享，且使用完要关闭，最好使用try-catch。



## Mybatis 独立使用

**JDBC参数** jdbc.properties

```properties
driver=com.mysql.cj.jdbc.Driver
url=jdbc:mysql://127.0.0.1:3306/learnsql?\
  serverTimezone=UTC&\
  useSSL=false&\
  useUnicode=true&\
  characterEncoding=utf8&\
  allowPublicKeyRetrieval=true
username=root
password=root
```

**配置文件** mybatis-config.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <!--导入外部配置-->
    <properties resource="jdbc.properties"/>
	<!--全局设置-->
    <settings>
        <setting name="mapUnderscoreToCamelCase" value="true"/>
        <setting name="logImpl" value="STDOUT_LOGGING"/> <!--日志工厂，或LOG4J-->
    </settings>
	<!--别名-->
    <typeAliases>
        <package name="com.szy.pojo"/>
    </typeAliases>
	<!--环境-->
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="${driver}"/>
                <property name="url" value="${url}"/>
                <property name="username" value="${username}"/>
                <property name="password" value="${password}"/>
            </dataSource>
        </environment>
    </environments>
	<!--指定映射文件-->
    <mappers>
        <!--需写出所有文件，放在resources/mapper/*.xml-->
        <mapper resource="mapper/StudentMapper.xml"/>
    </mappers>

</configuration>
```

**SqlSession工厂**

```java
public class MybatisUtils {
    // 从mybatis-config.xml创建获取SqlSessionFactory
    private static SqlSessionFactory sqlSessionFactory;
    static{
        try {
            String resource = "mybatis-config.xml";
            InputStream inputStream = Resources.getResourceAsStream(resource);
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    // 获取SqlSession
    public static SqlSession getSqlSession(){
        return sqlSessionFactory.openSession(true); // true自动提交
    }

}
```

**映射文件**（或java注解）

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.szy.dao.StudentDao">

    <insert id="addStudent" parameterType="Student">
        insert into student (s_id, s_name, s_birth, s_sex)
        VALUES (#{id},#{name},#{birth},#{sex})
    </insert>

    <select id="getAllStudent" resultType="Student">
        select * from student
    </select>

</mapper>
```

1. 映射POJO类：

    ```xml
    <insert id="addUser" parameterType="User">
            insert into user (username, age)  
            values (#(username),#(age))
    </insert>
    ```

2. 映射map：

    ```xml
    <insert id="addUser" parameterType="map">
            insert into user (username, age)  
            values (#{username},#{age})
    </insert>
    ```

    ```java
    int addUser(Map<String, Object> map);
    ```

    ```java
    map.put("username","szy");
    map.put("age","23");
    ```

3. 模糊查询：

    ```java
    getUser("%司%")
    ```

    ```sql
    select * from user where name like "%"#{value}"%"
    ```
    
4. 结果映射，解决POJO属性与数据库字段名字不统一

    result 字段，association 对象（多对一），collection 集合（一对多）
    
    ```xml
    <resultMap id="StudentMap" type="Student">
        <result column="s_id" property="id"/>
        <result column="s_birth" property="birthDay"/>
        <association property="teacher" javaType="Teacher">
            <result property="name" column="tname"/>
        </association>
        <collection property="students" ofType="Student">
            <result property="name" column="sname"/>
        </collection>
    </resultMap>
    ```

**POJO**

```java
public class Student {
    private String id;
    private String name;
    private String birth;
    private String sex;
}
```

**DAO**

```java
public interface StudentDao {
    int addStudent(Student student);
    List<Student> getAllStudent();
}
```

**测试代码**

```java
public void addStudentTest(){
    SqlSession sqlSession = MybatisUtils.getSqlSession();
    try{
        StudentDao studentDao = sqlSession.getMapper(StudentDao.class);
        studentDao.addStudent(new Student("09","司展宇","1998-05-01","男"));
        sqlSession.commit();// 增删改必须要commit
    }finally {
        sqlSession.close();
    }
}
```

## MyBatis-Spring

添加依赖包

【mysql-connector-java】：MySQL的 JDBC 驱动包

【spring-jdbc】

【druid】：阿里巴巴一个数据库连接池实现，可以很好的监控DB连接池和SQL的执行情况

【mybatis-spring】：将 mybatis 代码无缝整合到 Spring 中

```xml
<!--mybatis start -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>druid</artifactId>
    <version>1.2.8</version>
</dependency>
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-jdbc</artifactId>
    <version>5.3.13</version>
</dependency>
<dependency>
    <groupId>org.mybatis</groupId>
    <artifactId>mybatis</artifactId>
    <version>3.5.7</version>
</dependency>
<dependency>
    <groupId>org.mybatis</groupId>
    <artifactId>mybatis-spring</artifactId>
    <version>2.0.6</version>
</dependency>
<!-- mybatis end -->
```

添加配置 【/resources/jdbc.properties 】

```properties
jdbc.driverClassName=com.mysql.jdbc.Driver
jdbc.url=jdbc:mysql://127.0.0.1:3306/alumni?serverTimezone=GMT&useSSL=true&useUnicode=true&characterEncoding=utf8
jdbc.username=root
jdbc.password=root
```

配置Mybatis 【/resources/mybatis-config.xml】

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    
	<settings>
        <setting name="mapUnderscoreToCamelCase" value="true"/>
        <setting name="logImpl" value="STDOUT_LOGGING"/>
        <setting name="cacheEnabled" value="true"/>
    </settings>
    
    <typeAliases>
        <package name="org.alumni.model"/>
    </typeAliases>
    
</configuration>
```

配置Bean 【/resources/spring-dao.xml】

【context:property-placeholder】：外在化参数配置。location 表示属性文件位置，多个属性文件之间逗号分隔；ignore-unresolvable 表示是否忽略解析不到的属性，如果不忽略，找不到将抛出异常

【DruidDataSource】：阿里巴巴Druid数据源，该数据源会读取 jdbc.properties 配置文件的数据库连接信息和驱动

【SqlSessionFactoryBean】：在 MyBatis-Spring 中，使用 SqlSessionFactoryBean 创建 Session 工厂；在基本的 MyBatis 中，使用 SqlSessionFactoryBuilder

【MapperScannerConfigurer】：查找类路径下的映射器并自动将它们创建成 MapperFactoryBean

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
           http://www.springframework.org/schema/beans/spring-beans-2.5.xsd
           http://www.springframework.org/schema/context
           http://www.springframework.org/schema/context/spring-context-2.5.xsd">

    <!-- 1.配置数据库相关参数 -->
    <context:property-placeholder location="classpath:jdbc.properties" ignore-unresolvable="true"/>

    <!-- 2.数据源 -->
    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource" init-method="init" destroy-method="close">
        <property name="driverClassName" value="${jdbc.driverClassName}"/>
        <property name="url" value="${jdbc.url}"/>
        <property name="username" value="${jdbc.username}"/>
        <property name="password" value="${jdbc.password}"/>
    </bean>

    <!-- 3.配置SqlSessionFactory对象 -->
    <bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <!--注入数据库连接池-->
        <property name="dataSource" ref="dataSource"/>
        <!--扫描mybatis配置文件-->
        <property name="configLocation" value="classpath:mybatis-config.xml"/>
        <!--扫描sql配置文件:mapper需要的xml文件-->
<!--        <property name="mapperLocations" value="classpath:org/alumni/dao/*.xml"/>-->
    </bean>

    <!-- 4.扫描basePackage下所有DAO接口 -->
    <bean id="mapperScannerConfigurer" class="org.mybatis.spring.mapper.MapperScannerConfigurer">
        <property name="sqlSessionFactoryBeanName" value="sqlSessionFactory"/>
        <property name="basePackage" value="org.alumni.dao"/>
    </bean>
</beans>
```

**数据层**

DAO接口 【dao/AyUserDao.java】

```java
@Repository
public interface AyUserDao {
    // 增删改查等接口
    List<AyUser> findAll();
}
```

DAO对应的xml文件【dao/AyUserMapper.xml】

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.ay.dao.AyUserDao">

    <!-- 查询 -->
    <select id="queryById" resultType="User">
        select * from book.user    
        where userID=#{userID}
    </select>
    
    <!-- 增加 -->
    <insert id="addUser" parameterType="User">
        insert into book.user (username, age)  
        values (#(username),#(age))
    </insert>
</mapper>
```

**业务层**

业务层接口【service/AyUserService.java】

```java
package com.ay.service;

import com.ay.model.AyUser;
import java.util.List;

public interface AyUserService {
    List<AyUser> findAll();
}
```

业务层实体【service/AyUserServiceImpl.java】

```java
@Service
public class AyUserServiceImpl implements AyUserService {
    // 调用dao层
    @Resource
    private AyUserDao ayUserDao;

    public List<AyUser> findAll() {
        return ayUserDao.findAll();
    }
}
```

**控制层**

控制层实体，并注入服务层接口

```java
controller/AyUserController.java
@Controller
@RequestMapping("/user")
public class AyUserController {
    @Resource
    private AyUserService ayUserService;

    @GetMapping("/findAll")
    public String findAll(Model model){
        List<AyUser> ayUserList = ayUserService.findAll();
        for(AyUser ayUser : ayUserList){
            System.out.println("id: " + ayUser.getId());
            System.out.println("name: " + ayUser.getName());
        }
        return "hello";
	}
}
```



## 动态SQL

if条件，where

```xml
<select id="getStudentIf" parameterType="map" resultType="Student">
    select * from student
    <where>
        <if test="name != null">
            and s_name=#{name}
        </if>
        <if test="sex != null">
            and s_sex=#{sex}
        </if>
    </where>
</select>
```

choose、when、otherwise（if-else）

foreach：可以将任何可迭代对象（如 List、Set 等）、Map 对象或者数组对象作为集合参数传递给 *foreach*。当使用可迭代对象或者数组时，index 是当前迭代的序号，item 的值是本次迭代获取到的元素。当使用 Map 对象（或者 Map.Entry 对象的集合）时，index 是键，item 是值。

```xml
<foreach item="item" index="index" collection="list" open="(" separator="," close=")">
    #{item}
</foreach>
```

include：

```xml
<sql id = "selectFields">
        id, user_id, title, content, type, status, create_time, comment_count, score
</sql>

select <include refid="selectFields"></include>
from discuss_post
```



## 缓存

默认了两级缓存：一级缓存和二级缓存。先查二级缓存，再查一级缓存，再查数据库。

查询增加缓存，增删改刷新缓存。

- 一级缓存：默认开启，SqlSession 级别的缓存

  ```java
  sqlSession.clearCache();
  ```

- 二级缓存：手动开启，namespace 级别的缓存，可以通过实现 Cache 接口自定义二级缓存

  数据先放到一级缓存中，SqlSession 提交或关闭后，保存二级缓存

  ```xml
  <setting name="cacheEnabled" value="true"/>
  ```

  mapper：

  ```xml
  <cache eviction="FIFO" flushInterval="60000" size="512" readOnly="true"/>
  ```

  POJO：将实体序列化





# SpringMVC

![image-20210417103104550](http://mdimg.sofice.top/202112111340419.png)

有请求过来，DispatcherServlet(web.xml)去问HandlerMapping找对应的Controller（类和方法），找到之后用HandlerAdapter去执行Controller。Controller调用业务层Service（可选），Service再调用Repository进行数据库访问（可选），Controller也会调用相应的Model，返回时把从Service里获得的数据存入Model，并返回相应的View页面名称（即 ModelAndView）。DispatcherServlet根据View名称，进入ViewResolver视图解析器(spring-mvc.xml)进行路径拼接，返回全部路径，使得DispatcherServlet可以找到对应的View文件并把数据存入模板中，返回给浏览器



## Controller

```java
@Controller
public class UserController {
    @PostMapping("/signin")
	public ModelAndView doSignin(
        @RequestParam("email") String email,@RequestParam("password") String password,HttpSession session) {
        ...
	}
}
```

**地址匹配**

@RequestMapping("/user")

@GetMapping，@PostMapping，@PutMapping，@DeleteMapping，@PatchMapping



## 参数绑定

springmvc中，有支持默认类型的绑定，也就是说，直接在controller方法形参上定义默认类型的对象，就可以使用这些对象。

> 1. HttpServletRequest
> 2. HttpServletResponse
> 3. HttpSession
> 4. Model / ModelMap
> 5. ModelAndView

Model是一个接口，ModelMap是一个接口实现 ，作用是将Model数据填充到request域，跟ModelAndView类似。

**注解使用**

```java
// 通过/{id}
@PathVariable("id")
// 通过model
@RequestParam()
// 将请求的 Body 部分数据绑定到参数上
@RequestBody
// cookie
@CookieValue("kaptchaOwner")
```



## 传值和寻址

**Model / ModelMap**

Model 或者 ModelMap 只是传值，springmvc 自动创建，同 request、response、session，它没有寻址的功能，若要寻址，需在 controller 中 return "静态页地址"；Model传值的方法是 addAttribute(key,value)。

**ModelAndView**

ModelAndView 与 Model 最大的区别是它可以寻址，也可以带值，传值方法为addObject(key,value)，寻址方法为 setViewnName("静态页路径")。

**HttpServletRequest / HttpServletResponse**

Web服务器收到一个http请求，会针对每个请求创建一个 HttpServletRequest 和 HttpServletResponse 对象，向客户端发送数据找 HttpServletResponse，从客户端取数据找 HttpServletRequest。



:question: 为什么大多程序在 controller 中给 jsp 传值时使用 model.addAttribute() 而不使用 httpServeletRequest.setAttribute() 

事实上 model 数据，最终 spring 也是写到 HttpServletResponse 属性中，只是用 model 更符合 mvc 设计，减少各层间耦合。



## 返回值

```java
// 默认转发，返回视图，进入视图解析器拼接前后缀形成页面
return "login";
modelAndView.setViewName("login");

// 重定向
return "redirect:/login";
response.sendRedirect("/login");

// 返回各种值，将结果写入ResponseBody中，不解析为路径
@ResponseBody

// 返回模板参数
request.setAttribute("msg","输入有误");
model.addAttribute("msg","输入有误");
modelMap.addAttribute("msg","输入有误");
modelAndView.addObject("msg","输入有误");
```



## Session

```java
// 获取session
session = request.getSession()
// 获取属性
session.getAttribute("loginUser");
// 设置session
session.setAttribute("loginUser", username);
```



## Cookie

```java
Cookie cookie = new Cookie("kaptchaOwner", kaptchaOwner);
cookie.setMaxAge(60);
cookie.setPath(contextPath);
response.addCookie(cookie);

@CookieValue("kaptchaOwner")
```



# 其他

## 乱码过滤

```xml
web.xml
<!-- 配置乱码过滤 -->
<filter>
    <filter-name>encoding</filter-name>
    <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
    <init-param>
        <param-name>encoding</param-name>
        <param-value>utf-8</param-value>
    </init-param>
</filter>
<filter-mapping>
    <filter-name>encoding</filter-name>
    <url-pattern>/</url-pattern>
</filter-mapping>
```



## 整合 Json

**Fastjson**

```xml
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>fastjson</artifactId>
    <version>1.2.58</version>
</dependency>
```

```java
JSONObject json = new JSONObject();
json.put("code", code);
json.put("msg", msg);
return json.toJSONString();
```

**Jackson**

```xml
<dependency>
  <groupId>com.fasterxml.jackson.core</groupId>
  <artifactId>jackson-databind</artifactId>
  <version>2.9.8</version>
</dependency>
```

json乱码配置

```xml
<!--设置配置方案 -->
<mvc:annotation-driven>
    <!--json乱码问题 -->
    <mvc:message-converters register-defaults="true">
        <bean class="org.springframework.http.converter.StringHttpMessageConverter">
            <constructor-arg value="UTF-8"/>
        </bean>
        <bean class="org.springframework.http.converter.json.MappingJackson2HttpMessageConverter">
            <property name="objectMapper">
                <bean class="org.springframework.http.converter.json.Jackson2ObjectMapperFactoryBean">
                    <property name="failOnEmptyBeans" value="false"/>
                </bean>
            </property>
        </bean>
    </mvc:message-converters>
</mvc:annotation-driven>
```



```java
// 在类上配置，使类的所有方法返回body
@RestController
// 在方法上配置，使之返回body
@ResponseBody
public String find(@RequestBody String req, Model model) throws JsonProcessingException {
    ObjectMapper mapper = new ObjectMapper();
    User user = new User(1,"司展宇","123");
    String str = mapper.writeValueAsString(user);
    return str;
}
```





# 示例

## Spring框架运行步骤

添加依赖包

```xml
<!--spring start -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-webmvc</artifactId>
    <version>5.3.13</version>
</dependency>
<!--spring end -->
```

**applicationContext**

【resources/applicationContext.xml】

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/aop https://www.springframework.org/schema/aop/spring-aop.xsd">

    <bean id="userService" class="com.szy.service.UserServiceImpl"/>
    <bean id="log" class="com.szy.log.Log"/>
    <bean id="diyLog" class="com.szy.log.DiyLog"/>
    <!--开启注解支持-->
    <aop:aspectj-autoproxy/>
</beans>
```

测试代码

```java
public static void main(String[] args) {
    ApplicationContext cxt = new ClassPathXmlApplicationContext("applicationContext.xml");
    UserService userService = (UserService) cxt.getBean("userService");
    userService.add();
}
```

## SpringMVC运行步骤

添加依赖包

```xml
<!--springmvc start -->
<dependency>
    <groupId>jstl</groupId>
    <artifactId>jstl</artifactId>
    <version>1.2</version>
</dependency>
<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>4.0.0</version>
</dependency>
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-webmvc</artifactId>
    <version>5.0.4.RELEASE</version>
</dependency>
<!--springmvc end -->
<!-- 静态资源导出 -->
<build>
    <resources>
        <resource>
            <directory>src/main/java</directory>
            <excludes>
                <exclude>**/*.properties</exclude>
                <exclude>**/*.xml</exclude>
            </excludes>
            <filtering>false</filtering>
        </resource>
        <resource>
            <directory>src/main/resources</directory>
            <includes>
                <include>**/*.properties</include>
                <include>**/*.xml</include>
            </includes>
            <filtering>false</filtering>
        </resource>
    </resources>
</build>
```

运行容器，配置servlet，加载SpringMVC的配置文件，监听context配置文件【web.xml】

【DispatcherServlet 类】：前置控制器，用于拦截匹配请求，分发到目标 Controller 处理

【\<init-param\>】：当前\<servlet\>中的局部变量，声明了配置文件目录

【\<load-on-startup\>】：值大于等于0时，表示容器在应用启动时加载并初始化此 servlet；小于0或未指定时，表示容器在该 servlet 被选择时才加载

【\<servlet-mapping\>】：声明了与该 servlet 相应的匹配规则，每个【\<url-pattern\>】标签代表一个匹配规则

```xml
<?xml version="1.0" encoding="UTF-8"?>

<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <!-- 1. 配置乱码过滤 -->
    <filter>
        <filter-name>encoding</filter-name>
        <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
        <init-param>
            <param-name>encoding</param-name>
            <param-value>utf-8</param-value>
        </init-param>
    </filter>
    <filter-mapping>
        <filter-name>encoding</filter-name>
        <url-pattern>/*</url-pattern>
    </filter-mapping>

    <!-- 2. 配置DispatcherServlet -->
    <servlet>
        <servlet-name>spring-dispatcher</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <!-- 配置所有需要加载的配置文件，applicationContext.xml统一管理 -->
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:applicationContext.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
    <servlet-mapping>
        <servlet-name>spring-dispatcher</servlet-name>
        <!-- 默认匹配所有的请求 -->
        <url-pattern>/</url-pattern>
    </servlet-mapping>

    <error-page>
        <error-code>404</error-code>
        <location>/resources/html/404.html</location>
    </error-page>
    <error-page>
        <error-code>500</error-code>
        <location>/resources/html/500.html</location>
    </error-page>

</web-app>
```

配置SpringMVC

【\<mvc:annotation-driven/\>】：自动注册【RequestMappingHandlerAdapter】和【RequestMappingHandlerMapping】，是 SpringMVC 为 @Controller 分发请求所必需的，并提供了多种支持

【InternalResourceViewResolver】：最常用的视图解析器，当 @Controller 返回 ”Hello“ 时，解析器会自动添加前缀和后缀 ”/WEB-INF/views/hello.jsp“

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:mvc="http://www.springframework.org/schema/mvc"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        http://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/mvc
        http://www.springframework.org/schema/mvc/spring-mvc.xsd">

    <!-- 1. 扫描controller(后端控制器),并且扫描其中的注解-->
    <context:component-scan base-package="org.alumni.controller"/>
    <!-- 2. 静态资源过滤 -->
    <mvc:resources mapping="/resources/**" location="/resources/"/>
    <!-- 3. 注解驱动 -->
    <mvc:annotation-driven>
        <!--json乱码问题 -->
        <mvc:message-converters register-defaults="true">
            <bean class="org.springframework.http.converter.StringHttpMessageConverter">
                <constructor-arg value="UTF-8"/>
            </bean>
            <bean class="org.springframework.http.converter.json.MappingJackson2HttpMessageConverter">
                <property name="objectMapper">
                    <bean class="org.springframework.http.converter.json.Jackson2ObjectMapperFactoryBean">
                        <property name="failOnEmptyBeans" value="false"/>
                    </bean>
                </property>
            </bean>
        </mvc:message-converters>
    </mvc:annotation-driven>

    <!-- 4. 视图解析器 -->
    <bean class="org.springframework.web.servlet.view.InternalResourceViewResolver">
        <property name="viewClass" value="org.springframework.web.servlet.view.JstlView"/>
        <property name="prefix" value="/resources/html/"/>
        <property name="suffix" value=".html"/>
    </bean>

    <!--配置拦截器, 多个拦截器, 顺序执行 -->
    <!-- 当设置多个拦截器时，先按顺序调用preHandle方法，然后逆序调用每个拦截器的postHandle和afterCompletion方法  -->
    <mvc:interceptors>
        <!-- 用户登录拦截 -->
        <mvc:interceptor>
            <mvc:mapping path="/**" />
            <mvc:exclude-mapping path="/resources/**"/>
            <mvc:exclude-mapping path="/login"/>
            <mvc:exclude-mapping path="/register"/>
            <bean id="loginInterceptor" class="org.alumni.interceptor.LoginInterceptor"/>
        </mvc:interceptor>
        <!-- 用户身份拦截 -->
        <mvc:interceptor>
            <mvc:mapping path="/admin/**" />
            <mvc:mapping path="/student/**" />
            <mvc:mapping path="/teacher/**" />
            <mvc:mapping path="/schoolmate/**" />
            <bean id="identityInterceptor" class="org.alumni.interceptor.IdentityInterceptor"/>
        </mvc:interceptor>
    </mvc:interceptors>

</beans>
```

将@Controller实例化一个单例对象 AyTestController

```java
ayTestController.java
package com.ay.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping(value = "/test")
public class AyTestController {
    @GetMapping("/sayHello")
    public String sayHello() {
        return "hello";
    }
}
```











































