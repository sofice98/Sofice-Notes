```
mvn package -Dmaven.test.skip=true
```

# 构建工具的作用

构建一个项目通常包含了依赖管理、测试、编译、打包、发布等流程，构建工具可以自动化进行这些操作，从而为我们减少这些繁琐的工作。



**Java 主流构建工具**

Ant 具有编译、测试和打包功能，其后出现的 Maven 在 Ant 的功能基础上又新增了依赖管理功能，而最新的 Gradle 又在 Maven 的功能基础上新增了对 Groovy 语言的支持。

<img src="http://mdimg.sofice.top/202112111338032.png" alt="img" style="zoom:67%;" />



# Maven

**Maven 主要用处一：相同的项目结构**

使用Maven管理的Java 项目都有着相同的项目结构

1. 有一个pom.xml 用于维护当前项目都用了哪些jar包
2. 所有的java代码都放在 src/main/java 下面
3. 所有的测试代码都放在src/test/java 下面

**Maven 主要用处二：统一维护jar包**

maven风格的项目，首先把所有的jar包都放在【仓库】里，然后哪个项目需要用到这个jar包，只需要给出jar包的名称和版本号就行了。 这样jar包就实现了共享



配置：https://how2j.cn/k/idea/idea-maven-config/1353.html

## 仓库

Maven 仓库能帮助我们管理构件（主要是JAR），它就是放置所有JAR文件（WAR，ZIP，POM等等）的地方。

Maven 仓库有三种类型：

- **本地（local）**

  运行 Maven 的时候，Maven 所需要的任何构件都是直接从本地仓库获取的。如果本地仓库没有，它会首先尝试从远程仓库下载构件至本地仓库，然后再使用本地仓库的构件。

- **中央（central）**

  由 Maven 社区提供的仓库，其中包含了大量常用的库。要浏览中央仓库的内容，maven 社区提供了一个 URL：https://search.maven.org/#browse

- **远程（remote）**

  如果 Maven 在中央仓库中也找不到依赖的文件，它会停止构建过程并输出错误信息到控制台。为避免这种情况，Maven 提供了远程仓库的概念，它是开发人员自己定制仓库，包含了所需要的代码库或者其他工程中用到的 jar 文件。



## POM

POM( Project Object Model，项目对象模型 ) 是 Maven 工程的基本工作单元，是一个XML文件，保存在项目根目录的 pom.xml 文件中，包含了项目的基本信息，用于描述项目如何构建，声明项目依赖，等等。

执行任务或目标时，Maven 会在当前目录中查找 POM。它读取 POM，获取所需的配置信息，然后执行目标。

```xml
<dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.12</version>
    <scope>test</scope>
</dependency>
```

[groupId, artifactId, version, packaging,  classifier] 称为一个项目的坐标，其中 groupId、artifactId、version 必须定义，packaging  可选（默认为 Jar），classifier 不能直接定义的，需要结合插件使用。

| 节点         | 描述                                                         |
| ------------ | ------------------------------------------------------------ |
| project      | 工程的根标签                                                 |
| modelVersion | 模型版本，需要设置为 4.0                                     |
| groupId      | 工程组的标识。它在一个组织或者项目中通常是唯一的。例如，一个银行组织 com.companyname.project-group 拥有所有的和银行相关的项目 |
| artifactId   | 工程的标识。它通常是工程的名称。例如，消费者银行。groupId 和 artifactId 一起定义了 artifact 在仓库中的位置 |
| version      | 工程的版本号。在 artifact 的仓库中，它用来区分不同的版本。例如： `com.company.bank:consumer-banking:1.0 com.company.bank:consumer-banking:1.1` |
| packaging    | 项目打包方式。默认 jar                                       |





## 依赖

**依赖原则**

1. **依赖路径最短优先原则**

    ```html
    A -> B -> C -> X(1.0)
    A -> D -> X(2.0)
    ```

	由于 X(2.0) 路径最短，所以使用 X(2.0)。

2. **声明顺序优先原则**

    ```html
    A -> B -> X(1.0)
    A -> C -> X(2.0)
    ```

	在 POM 中最先声明的优先，上面的两个依赖如果先声明 B，那么最后使用 X(1.0)。

3. **覆写优先原则**

   子 POM 内声明的依赖优先于父 POM 中声明的依赖。



**依赖关系**

Maven定义了几种依赖关系，分别是`compile`、`test`、`runtime`和`provided`：

| scope    | 说明                                          | 示例            |
| -------- | --------------------------------------------- | --------------- |
| compile  | 编译时需要用到该jar包（默认）                 | commons-logging |
| test     | 编译Test时需要用到该jar包                     | junit           |
| runtime  | 编译时不需要，但运行时需要用到                | mysql           |
| provided | 编译时需要用到，但运行时由JDK或某个服务器提供 | servlet-api     |

在`<dependency>`下的`<scope>`中体现

## 构建流程

Maven不但有标准化的项目结构，而且还有一套标准化的构建流程，可以自动化实现编译，打包，发布，等等



Maven的**【生命周期(lifecycle)】**由一系列**【阶段(phase)】**构成，

内置的生命周期 **【default】** 包含以下 phase：

validate；initialize；generate-sources；process-sources；generate-resources；process-resources；**compile**；process-classes；generate-test-sources；process-test-sources；generate-test-resources；process-test-resources；test-compile；process-test-classes；**test**；prepare-package；**package**；pre-integration-test；integration-test；post-integration-test；verify；install；deploy

如果我们运行`mvn package`，Maven就会执行`default`生命周期，它会从开始一直运行到`package`这个phase为止



Maven另一个常用的生命周期是**【clean】**，它会执行3个phase：

pre-clean；**clean**；post-clean



更复杂的例子是指定多个phase，例如，运行`mvn clean package`，Maven先执行`clean`生命周期并运行到`clean`这个phase，然后执行`default`生命周期并运行到`package`这个phase



在实际开发过程中，经常使用的命令有：

`mvn clean`：清理所有生成的class和jar；

`mvn clean compile`：先清理，再执行到`compile`；

`mvn clean test`：先清理，再执行到`test`，因为执行`test`前必须执行`compile`，所以这里不必指定`compile`；

`mvn clean package`：先清理，再执行到`package`。



执行一个phase又会触发一个或多个**【goal】**：compile 对应的 goal —— compiler:compile

每个phase会执行自己默认的一个或多个goal，**goal是最小任务单元**



**【插件(plugin)】**

实际上，执行每个phase，都是通过某个 plugin 来执行的，Maven本身其实并不知道如何执行`compile`，它只是负责找到对应的`compiler`插件，然后执行默认的`compiler:compile`这个goal来完成编译。

Maven已经内置了一些常用的标准插件，如果标准插件无法满足需求，我们还可以使用自定义插件。使用自定义插件的时候，需要声明





## 模块管理

在软件开发中，把一个大项目分拆为多个模块是降低软件复杂度的有效方法

对于Maven工程来说，原来是一个大项目：

```ascii
single-project
├── pom.xml
└── src
```

现在可以分拆成3个模块：

```ascii
mutiple-project
├── module-a
│   ├── pom.xml
│   └── src
├── module-b
│   ├── pom.xml
│   └── src
└── module-c
    ├── pom.xml
    └── src
```

Maven可以有效地管理多个模块，我们只需要把每个模块当作一个独立的Maven项目，它们有各自独立的`pom.xml`

例如，模块A的`pom.xml`：

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.itranswarp.learnjava</groupId>
    <!-- diff -->
    <artifactId>module-a</artifactId>
    <version>1.0</version>
    <packaging>jar</packaging>
	<!-- diff -->
    <name>module-a</name>

    <properties>
        ...
    </properties>

    <dependencies>
        ...
    </dependencies>
</project>
```

模块B的`pom.xml`：

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.itranswarp.learnjava</groupId>
    <!-- diff -->
    <artifactId>module-b</artifactId>
    <version>1.0</version>
    <packaging>jar</packaging>
	<!-- diff -->
    <name>module-b</name>

    <properties>
        ...
    </properties>

    <dependencies>
        ...
    </dependencies>
</project>
```

可以看出来，模块A和模块B的`pom.xml`高度相似，因此，我们可以提取出共同部分作为`parent`：

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.itranswarp.learnjava</groupId>
    <artifactId>parent</artifactId>
    <version>1.0</version>
    <!-- attention -->
    <packaging>pom</packaging>

    <name>parent</name>

    <properties>
        ...
    </properties>

    <dependencies>
        ...
    </dependencies>
</project>
```

注意到parent的`<packaging>`是`pom`而不是`jar`，因为`parent`本身不含任何Java代码。编写`parent`的`pom.xml`只是为了在各个模块中减少重复的配置。现在我们的整个工程结构如下：

```ascii
multiple-project
├── pom.xml
├── parent
│   └── pom.xml
├── module-a
│   ├── pom.xml
│   └── src
├── module-b
│   ├── pom.xml
│   └── src
└── module-c
    ├── pom.xml
    └── src
```

这样模块A就可以简化为：

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
 	<!-- attention -->
    <parent>
        <groupId>com.itranswarp.learnjava</groupId>
        <artifactId>parent</artifactId>
        <version>1.0</version>
        <relativePath>../parent/pom.xml</relativePath>
    </parent>

    <artifactId>module-a</artifactId>
    <packaging>jar</packaging>
    <name>module-a</name>
</project>
```

如果模块A依赖模块B，则模块A需要模块B的jar包才能正常编译，我们需要在模块A中引入模块B：

```xml
    ...
    <dependencies>
        <dependency>
            <groupId>com.itranswarp.learnjava</groupId>
            <artifactId>module-b</artifactId>
            <version>1.0</version>
        </dependency>
    </dependencies>
```

最后，在编译的时候，需要在根目录创建一个`pom.xml`统一编译：

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">

    <modelVersion>4.0.0</modelVersion>
    <groupId>com.itranswarp.learnjava</groupId>
    <artifactId>build</artifactId>
    <version>1.0</version>
    <packaging>pom</packaging>
    <name>build</name>

    <modules>
        <module>parent</module>
        <module>module-a</module>
        <module>module-b</module>
        <module>module-c</module>
    </modules>
</project>
```

这样，在根目录执行`mvn clean package`时，Maven根据根目录的`pom.xml`找到包括`parent`在内的共4个`<module>`，一次性全部编译。































