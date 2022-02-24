Spring Boot 已经建立在现有 spring 框架之上。使用 spring 启动，我们避免了之前我们必须做的所有样板代码和配置。因此，Spring Boot 可以帮助我们以最少的工作量，更加健壮地使用现有的 Spring功能。

# YAML（application.yaml）赋值

支持**松散绑定**（last-name -> laseName），**JSR303数据校验**，**复杂类型封装**

语法：

```yaml
# 普通key-value
key: value
# 对象
student:
  name: szy
  age: 23
# 行内写法
teacher: {name: szy,age: 23}
# 数组：
arraya:
  - 0
  - 1
  - 2
# 行内写法
arrayb: [0,1,2] 
```

## SpringBoot使用yaml

```java
@Configuration
public class DruidConfig {
    @ConfigurationProperties(prefix = "spring.datasource")
    @Bean
    public DataSource druidDataSource(){
        return new DruidDataSource();
    }
}
```



```java
@ConfigurationProperties(prefix = "person")
public class Person {
    private String name;
    private Integer age;
    private Boolean happy;
    private Date birth;
    private Map<String,Object> maps;
    private List<Object> lists;
    private Dog dog;
}
```

```yaml
person:
  name: 司展宇
  age: 23
  happy: true
  birth: 1998/05/01
  maps: {k1: v1,k2: v2}
  lists: [code,music,girl]
  dog:
    name: 彭坤迪
    age: 22
```

```java
@Autowired
private Person person;
@Test
void contextLoads() {
    System.out.println(person);
}
```



**JSR303数据校验**

```java
@Validated
public class Person {
    @Email
    pripublic class Order {
    // 必须不为 null, 大小是 10
    @NotNull
    @Size(min = 10, max = 10)
    private String orderId;
    // 必须不为空
    @NotEmpty
    private String customer;
    // 必须是一个电子信箱地址
    @Email
    private String email;
    // 必须不为空
    @NotEmpty
    private String address;
    // 必须不为 null, 必须是下面四个字符串'created', 'paid', 'shipped', 'closed'其中之一
    // @Status 是一个定制化的 contraint
    @NotNull
    @Status
    private String status;
    // 必须不为 null
    @NotNull
    private Date createDate;
    // 嵌套验证
    @Valid
    private Product product;
}
```

![image-20211130230820301](http://mdimg.sofice.top/202112111340121.png)

**多环境配置**：

```yaml
server:
  port: 8081
spring:
  profiles:
    active: test
---
server:
  port: 8082
spring:
  config:
    activate:
      on-profile: test
---
server:
  port: 8083
spring:
  config:
    activate:
      on-profile: dev
```







# SpringBoot原理与配置

banner.txt 修改启动图片

SpringApplication：推断应用类型（普通、web）；查找并加载所有可用的初始化器（initializers属性）；查找所有的应用程序监听器（listeners属性）；推断并设置main方法的定义类，找到运行的主类





# Web开发

@Controller会视图解析，返回页面；@RestController=@Controller+@ResponseBody，返回的是json

如果一般前后端没有分离，后端需要控制页面的跳转则需要使用@Controller；如果前后端做了分离，即页面的跳转都放在了前端，此时一般使用@RestController。

## 配置

```xml
<!--springboot-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-log4j</artifactId>
    <version>1.3.2.RELEASE</version>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-configuration-processor</artifactId>
    <optional>true</optional>
</dependency>
```





```properties
# 时间格式化
spring.mvc.format.date=yyyy-MM-dd
```



## 导入静态资源

WebMvcAutoConfiguration.java

1. 导入外部资源

   ![image-20211201185428924](http://mdimg.sofice.top/202112111340200.png)

2. 本地资源访问

   ```java
   /**
   classpath:/META-INF/resources/
   classpath:/resources/	文件
   classpath:/static/  	图片
   classpath:/public/  	公共资源
   ```

   也可自定义资源路径使默认路径失效

   ```properties
   spring.mvc.static-path-pattern: /myresources
   ```
   
   



## 国际化

【application.properties】

```properties
spring.messages.basename=i18n.login
```

【classpath: i18n/】

![image-20211203135451443](http://mdimg.sofice.top/202112111340233.png)

![image-20211203135558866](http://mdimg.sofice.top/202112111340872.png)

【html】

```html
<h1 class="sign-title" th:text="#{login.tip}">Sign In</h1>
<div style="text-align: center;">
    <a class="btn btn-sm" th:href="@{/index.html(lang='zh_CN')}">中文</a>
    <a class="btn btn-sm" th:href="@{/index.html(lang='en_US')}">English</a>
</div>
```

【config/MyLocaleResolver.java】自定义locale解析器

```java
public class MyLocaleResolver implements LocaleResolver {
    @Override
    public Locale resolveLocale(HttpServletRequest request) {
        String language = request.getParameter("lang");
        Locale locale = Locale.getDefault();
        if(!StringUtils.isEmpty(language)){
            String[] split = language.split("_");
            locale = new Locale(split[0], split[1]);
        }
        return locale;
    }
}
```



## 拦截器

【MyMvcConfig】

```java
public class MyMvcConfig implements WebMvcConfigurer {
    @Resource
    private LoginHandlerInterceptor loginHandlerInterceptor;
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(loginHandlerInterceptor)
                .excludePathPatterns("/login","/css/**", "/js/**", "/images/**", "/fonts/**");
    }

}
```

【LoginHandlerInterceptor】

```java
@Component
public class LoginHandlerInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        if(request.getSession().getAttribute("loginUser") == null){
            request.setAttribute("msg","请先登录");
            response.sendRedirect("/login");
            return false;
        }
        return true;
    }
}
```



### 404 & 500

/templates/error/404.html

/templates/error/500.html







# 安全认证

Spring Security与Shiro不同：

- Spring Security是一个重量级的安全管理框架；Shiro则是一个轻量级的安全管理框架
- Spring Security 基于Spring开发，项目若使用Spring作为基础，配合Spring Security 做权限更便捷，而Shiro需要和Spring 进行整合开发；
- Spring Security 功能比Shiro更加丰富些，例如安全维护方面；
- Spring Security 社区资源相对于Shiro更加丰富；
- Shiro 的配置和使用比较简单，Spring Security 上手复杂些；
- Shiro 依赖性低，不需要任何框架和容器，可以独立运行， Spring Security依赖Spring容器；
- Shiro 不仅仅可以使用在web中，它可以工作在任何应用环境中。在集群会话时Shiro最重要的一个好处或许就是它的会话是独立于容器的；



## SpringSecurity

针对Spring的安全框架，实现认证（Authentication）和授权（Authorization）

- WebSecurityConfigurerAdapter：自定义Security策略
- AuthenticationManagerBuilder：自定义认证策略
- @EnableWebSecurity：开启WebSecurity



自定义Security策略【SecurityConfig】

```java
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // 授权规则
        http.authorizeRequests()
                .antMatchers("/").permitAll()
                .antMatchers("/student/**").hasRole("student")
                .antMatchers("/teacher/**").hasRole("teacher")
                .antMatchers("/admin/**").hasRole("admin");
        // 没有权限就会重定向到/login
        http.formLogin().loginPage("/login");
        // 注销并重定向
        http.logout().logoutSuccessUrl("/");
        // 关闭csrf防攻击，使get方法生效
        http.csrf().disable();
        // 开启认证cookie
        http.rememberMe().rememberMeParameter("isRememberMe");
    }
    // 认证
    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth.inMemoryAuthentication().passwordEncoder(new BCryptPasswordEncoder())
                .withUser("sizhanyu").password(new BCryptPasswordEncoder().encode("123456")).roles("student").and()
                .withUser("admin").password(new BCryptPasswordEncoder().encode("123456")).roles("admin");

    }
}
```

```java
@Configuration
public class SecurityConfig extends WebSecurityConfigurerAdapter implements CommunityConstant {

    /**
     * 静态资源
     * @param web
     * @throws Exception
     */
    @Override
    public void configure(WebSecurity web) throws Exception {
        web.ignoring().antMatchers("/resources/**");
    }

    // 认证环节我们使用自己的代码 LoginController，绕过 Spring Security 的


    /**
     * 授权
     * @param http
     * @throws Exception
     */
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests()
                .antMatchers(
                    "/user/setting",
                        "/user/upload",
                        "/discuss/add",
                        "/discuss/publish",
                        "/comment/add/**",
                        "/letter/**",
                        "/notice/**",
                        "/like",
                        "/follow",
                        "/unfollow"
                )
                .hasAnyAuthority(
                        AUTHORITY_USER,
                        AUTHORITY_ADMIN,
                        AUTHORITY_MODERATOR
                )

                .antMatchers(
                    "/discuss/top",
                        "/discuss/wonderful"
                )
                .hasAnyAuthority(
                        AUTHORITY_MODERATOR
                )

                .antMatchers(
                        "/discuss/delete",
                        "/discuss/delete/",
                        "/data/**"
                )
                .hasAnyAuthority(
                        AUTHORITY_ADMIN
                )

                .anyRequest().permitAll()

                .and().csrf().disable();

        // 权限不够时的处理
        http.exceptionHandling()
                // 1. 未登录时的处理
                .authenticationEntryPoint(new AuthenticationEntryPoint() {
                    @Override
                    public void commence(HttpServletRequest request, HttpServletResponse response, AuthenticationException e) throws IOException, ServletException {
                        String xRequestedWith = request.getHeader("x-requested-with");
                        if ("XMLHttpRequest".equals(xRequestedWith)) {
                            // 异步请求
                            response.setContentType("application/plain;charset=utf-8");
                            PrintWriter writer = response.getWriter();
                            writer.write(CommunityUtil.getJSONString(403, "你还没有登录"));
                        }
                        else {
                            // 普通请求
                            response.sendRedirect(request.getContextPath() + "/login");
                        }
                    }
                })
                // 2. 权限不够时的处理
                .accessDeniedHandler(new AccessDeniedHandler() {
                    @Override
                    public void handle(HttpServletRequest request, HttpServletResponse response, AccessDeniedException e) throws IOException, ServletException {
                        String xRequestedWith = request.getHeader("x-requested-with");
                        if ("XMLHttpRequest".equals(xRequestedWith)) {
                            // 异步请求
                            response.setContentType("application/plain;charset=utf-8");
                            PrintWriter writer = response.getWriter();
                            writer.write(CommunityUtil.getJSONString(403, "你没有访问该功能的权限"));
                        }
                        else {
                            // 普通请求
                            response.sendRedirect(request.getContextPath() + "/denied");
                        }
                    }
                });

        // Security 底层会默认拦截 /logout 请求，进行退出处理
        // 此处赋予它一个根本不存在的退出路径，使得程序能够执行到我们自己编写的退出代码
        http.logout().logoutUrl("/securitylogout");

        http.headers().frameOptions().sameOrigin();
    }
}
```

**整合thymeleaf**

```xml
<dependency>
    <groupId>org.thymeleaf.extras</groupId>
    <artifactId>thymeleaf-extras-springsecurity5</artifactId>
</dependency>
```

thymeleaf

```html
<html lang="en" xmlns:sec="http://www.thymeleaf.org/thymeleaf-extras-springsecurity5"></html>

<div sec:authorize="isAuthenticated()">
    如果登录
    用户名：<div sec:authentication="name"></div>
</div>
```







## Shiro









# Swagger API 框架

https://swagger.io/

API 框架

支持RestFul；API文档与定义同步更新；直接运行，可在线测试API接口；支持多种语言

```xml
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger2</artifactId>
    <version>2.9.2</version>
</dependency>
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger-ui</artifactId>
    <version>2.9.2</version>
</dependency>
```

访问：/swagger-ui.html

```java
@Configuration
@EnableSwagger2
@ConditionalOnExpression("${swagger.enable}")//开启访问接口文档的权限  swagger.enable是在yml配置文件中配置为true
public class SwaggerConfig {
    @Bean
    public Docket userRestApi() {
        return new Docket(DocumentationType.SWAGGER_2)
                .groupName("用户模块")  //模块名称
                .apiInfo(apiInfo())
                .select()
                .apis(RequestHandlerSelectors.basePackage("com.example.controller"))  //扫描的控制器路径
                .paths(PathSelectors.any())
                .build();
    }
    
    private ApiInfo apiInfo() {
        return new ApiInfoBuilder()
                .title("xxx项目开发接口文档")    //接口文档标题
                .description("此文档仅供开发技术组领导、开发人员使用")   //描述
                .termsOfServiceUrl("http://www.baidu.com/")   //相关的网址
                .contact(new Contact("后端开发","http://www.xxx.com/","XXXXXX7805@qq.com"))    //作者  邮箱等
                .version("1.0")  //版本号
                .build();
    }
}
```

使用

```java
@RestController
@Api(tags = "用户管理相关接口")
@RequestMapping("/user")
public class UserController {

    @PostMapping("/")
    @ApiOperation("添加用户的接口")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "username", value = "用户名", defaultValue = "李四"),
            @ApiImplicitParam(name = "address", value = "用户地址", defaultValue = "深圳", required = true)
    }
    )
    public boolean addUser(String username, @RequestParam(required = true) String address) {
        return true;
    }
    
    @GetMapping("/")
    @ApiOperation("根据id查询用户的接口")
    @ApiImplicitParam(name = "id", value = "用户id", defaultValue = "99", required = true)
    public User getUserById(@PathVariable Integer id) {
        User user = new User();
        user.setId(id);
        return user;
    }
    @PutMapping("/{id}")
    @ApiOperation("根据id更新用户的接口")
    public User updateUserById(@RequestBody User user) {
        return user;
    }
}
```

- @Api注解可以用来标记当前Controller的功能。
- @ApiOperation注解用来标记一个方法的作用。
- @ApiImplicitParam注解用来描述一个参数，可以配置参数的中文含义，也可以给参数设置默认值，这样在接口测试的时候可以避免手动输入。如果有多个参数，则需要使用多个@ApiImplicitParam注解来描述，多个@ApiImplicitParam注解需要放在一个@ApiImplicitParams注解中。
- 需要注意的是，@ApiImplicitParam注解中虽然可以指定参数是必填的，但是却不能代替@RequestParam(required = true)，前者的必填只是在Swagger2框架内必填，抛弃了Swagger2，这个限制就没用了，所以假如开发者需要指定一个参数必填，@RequestParam(required = true)注解还是不能省略。
- 如果参数是一个对象（例如上文的更新接口），对于参数的描述也可以放在实体类中。例如下面一段代码：

    ```java
    @ApiModel
    public class User {
        @ApiModelProperty(value = "用户id")
        private Integer id;
        @ApiModelProperty(value = "用户名")
        private String username;
        @ApiModelProperty(value = "用户地址")
        private String address;
        //getter/setter
    }
    ```



**在Security中的配置**

如果我们的Spring Boot项目中集成了Spring Security，那么如果不做额外配置，Swagger2文档可能会被拦截，此时只需要在Spring Security的配置类中重写configure方法，添加如下过滤即可：

```java
@Override
public void configure(WebSecurity web) throws Exception {
    web.ignoring()
            .antMatchers("/swagger-ui.html")
            .antMatchers("/v2/**")
            .antMatchers("/swagger-resources/**");
}
```





# 任务

## 异步任务

```java
@EnableAsync
@SpringBootApplication
public class SpringbootstudySwaggerApplication {
    public static void main(String[] args) {
        SpringApplication.run(SpringbootstudySwaggerApplication.class, args);
    }
}
```

在方法上使用：@Async

## 邮件任务

```xml
<dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-starter-mail</artifactId>
</dependency>
<dependency>
    <groupId>com.sun.mail</groupId>
    <artifactId>jakarta.mail</artifactId>
</dependency>
```

```properties
spring.mail.username=773508803@qq.com
spring.mail.password=martin123
spring.mail.host=smtp.qq.com
# 开启加密验证
spring.mail.properties.mail.smtp.ssl.enable=true
```



## 定时执行任务





# 集成Mybatis

```xml
<!--database-->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
</dependency>
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>2.1.3</version>
</dependency>
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>druid</artifactId>
    <version>1.2.8</version>
</dependency>
```

【application.yaml】

```yaml
# jdbc
spring:
  datasource:
    driver-class-name: com.mysql.cj.jdbc.Drive
    url: jdbc:mysql://127.0.0.1:3306/learnsql?serverTimezone=UTC&useSSL=false&useUnicode=true&characterEncoding=utf8&allowPublicKeyRetrieval=true
    username: root
    password: root
    type: com.alibaba.druid.pool.DruidDataSource
    filters: stat,wall,log4j
# mybatis
mybatis:
  type-aliases-package: com.szy.dao
  mapper-locations: classpath:mybatis/mapper/*.xml
```

【dao】

```java
@Mapper
@Repository
public interface UserMapper{
    
}
```



## Druid

```java
@Configuration
public class DruidConfig {
    @ConfigurationProperties(prefix = "spring.datasource")
    @Bean
    public DataSource druidDataSource(){
        return new DruidDataSource();
    }
    // 后台监控 使用 '/druid' 访问
    @Bean
    public ServletRegistrationBean statViewServlet(){
        ServletRegistrationBean<StatViewServlet> bean = new ServletRegistrationBean<>(new StatViewServlet(), "/druid/*");
        HashMap<String,String> initParameters = new HashMap<>();
        initParameters.put("loginUsername", "admin"); //登录名
        initParameters.put("loginPassword", "123456");//密码
        initParameters.put("allow","");
        bean.setInitParameters(initParameters);
        return bean;
    }
}
```



# 集成Thymeleaf

导入依赖

```xml
<!--thymeleaf-->
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

使用

``` html
<html lang="en" xmlns:th="http://www.thymeleaf.org">
```

属性内部写或者中括号转义：`[[${}]]`

- 链接：@{}

- 变量：${} 

  导入html片段：`th:utext`

  遍历：`th:each="user:${users}" th:text="${user}"`

  遍历map：

  ```html
  <tr th:each="item:${map}">
      <td th:text="${item.key}"></td>
      <td th:text="${item.value}"></td>
  </tr>
  ```

  对象：`${user.name}`

- 选择变量：*{}

  对选定对象而不是整个上下文评估表达式。使用`th:object`就可以选定对象

  ``` html
  <div th:object="${user}">
      <p>Name: <span th:text="*{name}">赛</span>.</p>
      <p>Age: <span th:text="*{age}">18</span>.</p>
      <p>Detail: <span th:text="*{detail}">好好学习</span>.</p>
  </div>
  ```

- 消息：#{}

  用来读取配置文件中数据

- 导入片段：~{}

  导入外部的 `th:fragment`

  ```html
  common.html
  <div th:fragment="sidebar"></div>
  <a th:class="${activate=='main.html'?'':'active'}"></a>
  其他html
  <div th:replace="~{common/common::sidebar(active='main.html')}"></div>
  ```

  

  

传参

```html
<a class="btn btn-sm" th:href="@{/index.html(lang='zh_CN')}">中文</a>
<a class="btn btn-sm" th:href="@{|/student/student.getId()(lang='en_US')|}">English</a>
```

变量名的后面加上 `Stat` 可用于表示每次的循环对象，而 `xxxStat.count` 就表示当前是第几次循环

```html
<!-- 楼数 -->
第 <i th:text="${page.offset + cvoStat.count}"></i> 楼
```

# 集成Dubbo+ZooKeeper

```xml
<!--Dubbo+ZooKeeper-->
<dependency>
   <groupId>org.apache.dubbo</groupId>
   <artifactId>dubbo-spring-boot-starter</artifactId>
   <version>3.0.4</version>
</dependency>
<dependency>
   <groupId>com.github.sgroschupf</groupId>
   <artifactId>zkclient</artifactId>
   <version>0.1</version>
</dependency>
<dependency>
   <groupId>org.apache.curator</groupId>
   <artifactId>curator-framework</artifactId>
   <version>4.2.0</version>
</dependency>
<dependency>
   <groupId>org.apache.curator</groupId>
   <artifactId>curator-recipes</artifactId>
   <version>4.2.0</version>
</dependency>
<dependency>
   <groupId>org.apache.zookeeper</groupId>
   <artifactId>zookeeper</artifactId>
   <version>3.4.14</version>
   <exclusions>
      <exclusion>
         <groupId>org.slf4j</groupId>
         <artifactId>slf4j-log4j12</artifactId>
      </exclusion>
   </exclusions>
</dependency>
```

provider

```properties
server.port=8001

# 服务器应用名字
dubbo.application.name=provider-server
# 注册中心地址
dubbo.registry.address=zookeeper://127.0.0.1:2181
# 扫描需要注册的服务包
dubbo.scan.base-packages=com.szy.service
```

```java
@Service
@DubboService // 可以被扫描到，项目启动自动注册
public class TicketServiceImpl implements TicketService{

    @Override
    public String getTicket() {
        return "《肖邦音乐剧》";
    }
}
```

consumer

```properties
server.port=8002

# 服务器应用名字
dubbo.application.name=consumer-server
# 注册中心地址
dubbo.registry.address=zookeeper://127.0.0.1:2181
# 扫描需要注册的服务包
dubbo.scan.base-packages=com.szy.service
```

```java
@Service
public class UserService {
    // 想拿到provider提供的票
    @Reference
    TicketService ticketService;// 在与provider的相同目录下新建文件TicketService
    
    public void buyTicket(){
        String ticket = ticketService.getTicket();
    }
}
```



# 集成Redis（Lettuce）

**Jedis**  和 **Lettuce** 是 Java 操作 Redis 的客户端。在 Spring Boot 1.x 版本默认使用的是 jedis ，而在 **Spring Boot 2.x 版本默认使用的就是 Lettuce**。关于 Jedis 跟 Lettuce 的区别如下：

- Jedis在实现上是直接连接的 redis server，如果在多线程环境下是非线程安全的，这个时候只有使用连接池，为每个Jedis实例增加物理连接
- Lettuce的连接是基于 Netty 的，连接实例（`StatefulRedisConnection`）可以在多个线程间并发访问，应为`StatefulRedisConnection `是线程安全的，所以一个连接实例就可以满足多线程环境下的并发访问，当然这个也是可伸缩的设计，一个连接实例不够的情况也可以按需增加连接实例。

## RedisTemplate 类

SpringBoot 中用来操作 Redis 的类是 `RedisTemplate `类：

```java
@Bean
@ConditionalOnMissingBean(name = {"redisTemplate"}) // 我们可以自己定义一个 redisTemplate来替换这个默认的
public RedisTemplate<Object, Object> redisTemplate(RedisConnectionFactory redisConnectionFactory) throws UnknownHostException {
    // 默认的 RedisTemplate 没有过多的设置，redis 对象都是需要序列化！
	// 两个泛型都是 Object, Object 的类型，我们使用需要强制转换 <String, Object>
    RedisTemplate<Object, Object> template = new RedisTemplate();
    template.setConnectionFactory(redisConnectionFactory);
    return template;
}

@Bean
@ConditionalOnMissingBean // 由于 String 是redis中最常使用的类型，所以单独提出来了一个bean
public StringRedisTemplate stringRedisTemplate(RedisConnectionFactory redisConnectionFactory) throws UnknownHostException {
    StringRedisTemplate template = new StringRedisTemplate();
    template.setConnectionFactory(redisConnectionFactory);
    return template;
}
```

`RedisTemplate `提供了以下方法分别用于对 Redis 的各个数据结构进行操作：

- `opsForValue`： 对应 String（字符串）
- `opsForZSet`： 对应 ZSet（有序集合）
- `opsForHash`： 对应 Hash（哈希）
- `opsForList`： 对应 List（列表）
- `opsForSet`： 对应 Set（集合）
- `opsForGeo`： 对应 GEO（地理位置）

## 整合测试流程

① 导入依赖

<img src="http://mdimg.sofice.top/202112201418733.png" style="zoom: 67%;" />

或者手动导入依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
```

SpringBoot2.x 底层访问默认使用 Lettuce

② 配置文件

```properties
# 配置redis
spring.redis.host=127.0.0.1
spring.redis.port=6379
```

③ 测试

```java
@SpringBootTest
class RedisDemoApplicationTests {

    @Autowired
    private RedisTemplate redisTemplate;

    @Test
    void contextLoads() {
        redisTemplate.opsForValue().set("mykey","hello");
        System.out.println(redisTemplate.opsForValue().get("mykey"));
    }

}
```

## 测试对象的保存

我们编写一个实体类 User，测试一下对象的保存：

```java
@Test
void contextLoads() {
    User user = new User("小牛肉","20");
    redisTemplate.opsForValue().set("user",user);
    System.out.println(redisTemplate.opsForValue().get("user"));
}
```

![](http://mdimg.sofice.top/202112201418774.png)

🚨 报错：所有的对象都需要序列化。

将实体类序列化：

```java
public class User implements Serializable
```



## 自定义 RedisTemplate

![](http://mdimg.sofice.top/202112201418736.png)

上示代码中 `RedisTemplate<Object,Object>` 泛型选用的是两个 `Object `类，通常情况下，对于 `key `值我们一般会选用 `String `类型，使得我们每次都要进行强制类型转换。而且 `RedisTemplate `类默认采用的是 jdk 的序列化方式，但在真实的开发中，我们一般使用 Json 来传递对象，接下来我们自定义一个 `RedisTemplate<String,Object>`（新建一个 configuration.`RedisConfig`类）：

```java
@Configuration
public class RedisConfig {
    @Bean
    @SuppressWarnings("all")
    public RedisTemplate<String, Object> redisTemplate(RedisConnectionFactory factory) {
        // 为了开发方便，一般直接使用 <String, Object>
        RedisTemplate<String, Object> template = new RedisTemplate<String, Object>();
        template.setConnectionFactory(factory);
        
        // 默认是的用jdk序列化的，需要改成 Json 序列化
        Jackson2JsonRedisSerializer jackson2JsonRedisSerializer = new Jackson2JsonRedisSerializer(Object.class);
        ObjectMapper om = new ObjectMapper();
        om.setVisibility(PropertyAccessor.ALL, JsonAutoDetect.Visibility.ANY);
        om.enableDefaultTyping(ObjectMapper.DefaultTyping.NON_FINAL);
        jackson2JsonRedisSerializer.setObjectMapper(om);
        
        // String 的序列化
        StringRedisSerializer stringRedisSerializer = new StringRedisSerializer();
        // key采用String的序列化方式
        template.setKeySerializer(stringRedisSerializer);
        // hash的key也采用String的序列化方式
        template.setHashKeySerializer(stringRedisSerializer);
        // value序列化方式采用jackson
        template.setValueSerializer(jackson2JsonRedisSerializer);
        // hash的value序列化方式采用jackson
        template.setHashValueSerializer(jackson2JsonRedisSerializer);
        
        template.afterPropertiesSet();
        return template;
    }
}
```

测试：

```java
@Test
void contextLoads() {
    User user = new User("小牛肉","20");
    redisTemplate.opsForValue().set("user",user);
    System.out.println(redisTemplate.opsForValue().get("user"));
}
```

## 事务管理

```java
redisTemplate.execute(new SessionCallback() {
    @Override
    public Object execute(RedisOperations redisOperations) throws DataAccessException {
        redisOperations.multi(); // 开启事务

        redisOperations.opsForValue().decrement(userLikeKey);

        return redisOperations.exec(); // 提交事务
    }
});
```

## Redis 集群

```properties
# 数据库索引
spring.redis.database=0
# Redis的服务器地址
spring.redis.host=127.0.0.1
# Redis的服务器连接端口
spring.redis.port=7000
# Redis的服务器连接密码（默认为空）
spring.redis.password=
# 连接池的最大连接数（使用负值表示没有限制）
spring.redis.jedis.pool.max-active=2000
# 连接池的最大阻塞等待时间（使用负值表示没有限制）
spring.redis.jedis.pool.max-wait=-1
# 连接池的最大空闲连接
spring.redis.jedis.pool.max-idle=100
# 连接池的最小空闲连接
spring.redis.jedis.pool.min-idle=50
# 连接超时时间（毫秒）
spring.redis.timeout=1000
#哨兵模式配置
spring.redis.sentinel.master=mymaster
spring.redis.sentinel.nodes=127.0.0.1:9000
#集群模式配置
spring.redis.cluster.nodes=127.0.0.1:7000,127.0.0.1:7001,127.0.0.1:7002,127.0.0.1:7003,127.0.0.1:7004,127.0.0.1:7005
```

单机模式：spring.redis.host + spring.redis.port 

主从模式：将spring.redis.cluster.nodes 地址设置为主从节点的服务地址

哨兵模式：spring.redis.sentinel.master + spring.redis.sentinel.nodes

集群模式：spring.redis.cluster.nodes





# 集成ElasticSearch

修改版本

```xml
<elasticsearch.version>7.16.2</elasticsearch.version>
```

























