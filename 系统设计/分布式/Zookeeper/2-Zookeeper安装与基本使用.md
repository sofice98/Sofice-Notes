# ð Zookeeper å®è£ä¸åºæ¬ä½¿ç¨

---

## 1. Zookeeper å®è£

åè§ ð [Zookeeper å®è£éç½® | èé¸æç¨ (runoob.com)](https://www.runoob.com/w3cnote/zookeeper-setup.html)

æ³¨æä¸è½½çä¸å®æ¯ **bin**.tar.gz æä»¶ï¼ä¸ç¶ä¼åºé

è¿æ¥ Zookeeper æå¡ï¼è¿è¡ `zkServer.cmd`

åè¿è¡å®¢æ·ç«¯ `zkCli.cmd`ï¼å¯å¨ `zkCli.cmd` è¾å¥å½ä»¤

## 2. Zookeeper å¸¸ç¨å½ä»¤

### æ¥ç ZooKeeper  å¸¸ç¨å½ä»¤ (help)

éè¿ `help` å½ä»¤æ¥ç ZooKeeper å¸¸ç¨å½ä»¤

### åå»ºèç¹ (create)

éè¿ `create` å½ä»¤å¨æ ¹ç®å½åå»ºäº node1 èç¹ï¼ä¸å®å³èçå­ç¬¦ä¸²æ¯ "hello"

```shell
[zk: 127.0.0.1:2181(CONNECTED) 34] create /node1 âhelloâ
```

éè¿ `create` å½ä»¤å¨æ ¹ç®å½åå»ºäº node1 èç¹ï¼ä¸å®å³èçåå®¹æ¯æ°å­ 123

```shell
[zk: 127.0.0.1:2181(CONNECTED) 1] create /node1/node1.1 123
Created /node1/node1.1
```

### æ´æ°èç¹æ°æ®åå®¹ (set)

```shell
[zk: 127.0.0.1:2181(CONNECTED) 11] set /node1 "good"
```

### è·åèç¹çæ°æ® (get)

`get` å½ä»¤å¯ä»¥è·åæå®èç¹çæ°æ®åå®¹åèç¹çç¶æ,å¯ä»¥çåºæä»¬éè¿ `set` å½ä»¤å·²ç»å°èç¹æ°æ®åå®¹æ¹ä¸º "good"ã

```shell
good
cZxid = 0x47
ctime = Sun Jan 20 10:22:59 CST 2019
mZxid = 0x4b
mtime = Sun Jan 20 10:41:10 CST 2019
pZxid = 0x4a
cversion = 1
dataVersion = 1
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 9
numChildren = 1
```

### æ¥çæä¸ªç®å½ä¸çå­èç¹ (ls)

éè¿ `ls` å½ä»¤æ¥çæ ¹ç®å½ä¸çèç¹

```shell
[zk: 127.0.0.1:2181(CONNECTED) 37] ls /
[dubbo, ZooKeeper, node1]
```

éè¿ `ls` å½ä»¤æ¥ç node1 ç®å½ä¸çèç¹

```shell
[zk: 127.0.0.1:2181(CONNECTED) 5] ls /node1
[node1.1]
```

ZooKeeper ä¸­ç ls å½ä»¤å linux å½ä»¤ä¸­ç ls ç±»ä¼¼ï¼ è¿ä¸ªå½ä»¤å°ååºç»å¯¹è·¯å¾ path ä¸çææå­èç¹ä¿¡æ¯ï¼ååº 1 çº§ï¼å¹¶ä¸éå½ï¼

### æ¥çèç¹ç¶æ (stat)

éè¿ `stat` å½ä»¤æ¥çèç¹ç¶æ

```shell
[zk: 127.0.0.1:2181(CONNECTED) 10] stat /node1
cZxid = 0x47
ctime = Sun Jan 20 10:22:59 CST 2019
mZxid = 0x47
mtime = Sun Jan 20 10:22:59 CST 2019
pZxid = 0x4a
cversion = 1
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 11
numChildren = 1
```

### æ¥çèç¹ç¶æåå­èç¹åè¡¨ (ls2)

`ls2` å½ä»¤æ´åæ¯ `ls` å½ä»¤å `stat` å½ä»¤çç»åã `ls2` å½ä»¤è¿åçä¿¡æ¯åæ¬ 2 é¨åï¼

1. å­èç¹åè¡¨
2. å½åèç¹ç stat ä¿¡æ¯ã

```shell
[zk: 127.0.0.1:2181(CONNECTED) 7] ls2 /node1
[node1.1]
cZxid = 0x47
ctime = Sun Jan 20 10:22:59 CST 2019
mZxid = 0x47
mtime = Sun Jan 20 10:22:59 CST 2019
pZxid = 0x4a
cversion = 1
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 11
numChildren = 1
```

### å é¤èç¹ (delete)

è¿ä¸ªå½ä»¤å¾ç®åï¼ä½æ¯éè¦æ³¨æçä¸ç¹æ¯å¦æä½ è¦å é¤æä¸ä¸ªèç¹ï¼é£ä¹è¿ä¸ªèç¹å¿é¡»æ å­èç¹æè¡ã

```shell
[zk: 127.0.0.1:2181(CONNECTED) 3] delete /node1/node1.1
```

## 3. ZooKeeper Java å®¢æ·ç«¯ Curator ç®åä½¿ç¨

> ð¡ Zookeeper å®¢æ·ç«¯æä¾äºåºæ¬çæä½ï¼æ¯å¦ï¼åå»ºä¼è¯ãåå»ºèç¹ãè¯»åèç¹ãæ´æ°æ°æ®ãå é¤èç¹åæ£æ¥èç¹æ¯å¦å­å¨ç­ãä½å¯¹äºå¼åäººåæ¥è¯´ï¼Zookeeper æä¾çåºæ¬æçºµè¿æ¯æä¸äºä¸è¶³ä¹å¤ãæ¥ä¸æ¥æä»¬å°±ä»ç»ä¸ä¸ Zookeeper å®¢æ·ç«¯çä¸¤æ¬¾å¼æºæ¡æ¶ **ZKClient** å **Curator**ã

Curator æ¯ Netflix å¬å¸å¼æºçä¸å¥ ZooKeeper Java å®¢æ·ç«¯æ¡æ¶ï¼**ç¸æ¯äº Zookeeper èªå¸¦çå®¢æ·ç«¯ zookeeper æ¥è¯´ï¼Curator çå°è£æ´å å®åï¼åç§ API é½å¯ä»¥æ¯è¾æ¹ä¾¿å°ä½¿ç¨**ã

Curator 4.0+çæ¬å¯¹ ZooKeeper 3.5.x æ¯ææ¯è¾å¥½ãå¼å§ä¹åï¼è¯·åå°ä¸é¢çä¾èµæ·»å è¿ä½ çé¡¹ç®ã

```xml
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
```

### â  è¿æ¥ ZooKeeper å®¢æ·ç«¯

éè¿ `CuratorFrameworkFactory` åå»º `CuratorFramework` å¯¹è±¡ï¼ç¶ååè°ç¨ `CuratorFramework` å¯¹è±¡ç `start()` æ¹æ³å³å¯

```java
private static final int BASE_SLEEP_TIME = 1000; // éè¯ä¹é´ç­å¾çåå§æ¶é´
private static final int MAX_RETRIES = 3; // æå¤§éè¯æ¬¡æ°

// Retry strategy. Retry 3 times, and will increase the sleep time between retries.
RetryPolicy retryPolicy = new ExponentialBackoffRetry(BASE_SLEEP_TIME, MAX_RETRIES);
CuratorFramework zkClient = CuratorFrameworkFactory.builder()
     // è¦è¿æ¥çæå¡å¨åè¡¨
    .connectString("127.0.0.1:2181")
    // éè¯ç­ç¥
    .retryPolicy(retryPolicy)
    .build();
zkClient.start();
```

å¯¹äºä¸äºåºæ¬åæ°çè¯´æï¼

- `baseSleepTimeMs`ï¼éè¯ä¹é´ç­å¾çåå§æ¶é´
- `maxRetries` ï¼æå¤§éè¯æ¬¡æ°
- `connectString` ï¼è¦è¿æ¥çæå¡å¨åè¡¨
- `retryPolicy` ï¼éè¯ç­ç¥

### â¡ æ°æ®èç¹çå¢å æ¹æ¥

#### åå»ºèç¹

ä¸ç« æä»¬æå°è¿ï¼éå¸¸æ¯å° znode åä¸º 4 å¤§ç±»ï¼

- **æä¹ï¼PERSISTENTï¼èç¹** ï¼ä¸æ¦åå»ºå°±ä¸ç´å­å¨å³ä½¿ ZooKeeper éç¾¤å®æºï¼ç´å°å°å¶å é¤ã
- **ä¸´æ¶ï¼EPHEMERALï¼èç¹** ï¼ä¸´æ¶èç¹ççå½å¨ææ¯ä¸ **å®¢æ·ç«¯ä¼è¯ï¼sessionï¼** ç»å®çï¼**ä¼è¯æ¶å¤±åèç¹æ¶å¤±** ãå¹¶ä¸ï¼ä¸´æ¶èç¹ **åªè½åå¶å­èç¹** ï¼ä¸è½åå»ºå­èç¹ã
- **æä¹é¡ºåºï¼PERSISTENT_SEQUENTIALï¼èç¹** ï¼é¤äºå·ææä¹ï¼PERSISTENTï¼èç¹çç¹æ§ä¹å¤ï¼ å­èç¹çåç§°è¿å·æé¡ºåºæ§ãæ¯å¦ `/node1/app0000000001` ã`/node1/app0000000002` ã
- **ä¸´æ¶é¡ºåºï¼EPHEMERAL_SEQUENTIALï¼èç¹** ï¼é¤äºå·å¤ä¸´æ¶ï¼EPHEMERALï¼èç¹çç¹æ§ä¹å¤ï¼å­èç¹çåç§°è¿å·æé¡ºåºæ§ã

å¶å®å¨ä½¿ç¨çZooKeeper çæ¶åï¼ä¼åç° `CreateMode` ç±»ä¸­å®éæ 7ç§ znode ç±»å ï¼ä½æ¯ç¨çæå¤çè¿æ¯ä¸é¢ä»ç»ç 4 ç§ã

ð¸ **a.åå»ºæä¹åèç¹**

ä½ å¯ä»¥éè¿ä¸é¢ä¸¤ç§æ¹å¼åå»ºæä¹åçèç¹ã

```java
//æ³¨æ:ä¸é¢çä»£ç ä¼æ¥éï¼ä¸æè¯´äºå·ä½åå 
zkClient.create().forPath("/node1/00001");
zkClient.create().withMode(CreateMode.PERSISTENT).forPath("/node1/00002");
```

ä½æ¯ï¼ä½ è¿è¡ä¸é¢çä»£ç ä¼æ¥éï¼è¿æ¯å ä¸ºçç¶èç¹`node1`è¿æªåå»ºã

ä½ å¯ä»¥ååå»ºç¶èç¹ `node1` ï¼ç¶ååæ§è¡ä¸é¢çä»£ç å°±ä¸ä¼æ¥éäºã

```java
zkClient.create().forPath("/node1");
```

æ´æ¨èçæ¹å¼æ¯éè¿ä¸é¢è¿è¡ä»£ç ï¼ **`creatingParentsIfNeeded()` å¯ä»¥ä¿è¯ç¶èç¹ä¸å­å¨çæ¶åèªå¨åå»ºç¶èç¹ï¼è¿æ¯éå¸¸æç¨çã**

```java
zkClient.create().creatingParentsIfNeeded().withMode(CreateMode.PERSISTENT).forPath("/node1/00001");
```

ð¸ **b.åå»ºä¸´æ¶èç¹**

```java
zkClient.create().creatingParentsIfNeeded().withMode(CreateMode.EPHEMERAL).forPath("/node1/00001");
```

ð¸ **c.åå»ºèç¹å¹¶æå®æ°æ®åå®¹**

```java
zkClient.create().creatingParentsIfNeeded().withMode(CreateMode.EPHEMERAL).forPath("/node1/00001", "java".getBytes());
zkClient.getData().forPath("/node1/00001");// è·åèç¹çæ°æ®åå®¹ï¼è·åå°çæ¯ byte æ°ç»
```

ð¸ **d.æ£æµèç¹æ¯å¦åå»ºæå**

```java
zkClient.checkExists().forPath("/node1/00001");// ä¸ä¸º null çè¯ï¼è¯´æèç¹åå»ºæå
```

#### å é¤èç¹

ð¸ **a.å é¤ä¸ä¸ªå­èç¹**

```java
zkClient.delete().forPath("/node1/00001");
```

ð¸ **b.å é¤ä¸ä¸ªèç¹ä»¥åå¶ä¸çææå­èç¹**

```java
zkClient.delete().deletingChildrenIfNeeded().forPath("/node1");
```

#### è·å/æ´æ°èç¹æ°æ®åå®¹

```java
zkClient.create().creatingParentsIfNeeded().withMode(CreateMode.EPHEMERAL).forPath("/node1/00001","java".getBytes());
zkClient.getData().forPath("/node1/00001");//è·åèç¹çæ°æ®åå®¹
zkClient.setData().forPath("/node1/00001","c++".getBytes());//æ´æ°èç¹æ°æ®åå®¹
```

#### è·åæä¸ªèç¹çææå­èç¹è·¯å¾

```java
List<String> childrenPaths = zkClient.getChildren().forPath("/node1");
```

## 4. Zookeeper Java å®¢æ·ç«¯ ZkClient ç®åä½¿ç¨

[ZkClient](https://github.com/sgroschupf/zkclient) ç®åãé«æç Zookeeper Javaå®¢æ·ç«¯ã

- è®© Zookeeper API ä½¿ç¨èµ·æ¥æ´ç®å
- éå¸¸æ¹ä¾¿è®¢éåç§äºä»¶å¹¶èªå¨éæ°ç»å®äºä»¶ï¼ä¼è¯å»ºç«ãèç¹ä¿®æ¹ãèç¹å é¤ãå­èç¹åæ´ç­ï¼
- session è¿æèªå¨éè¿ãæºå¶

å¼å§ä¹åï¼è¯·åå°ä¸é¢çä¾èµæ·»å è¿ä½ çé¡¹ç®ï¼

```xml
<dependency>
    <groupId>com.101tec</groupId>
    <artifactId>zkclient</artifactId>
    <version>0.10</version>
</dependency>
```

### â  è¿æ¥ ZooKeeper å®¢æ·ç«¯

å¨ä½¿ç¨ ZkClient æä½ Zookeeper æ¶ï¼**åºæ¬çæä½é½å°è£å¨ `ZkClient` ç±»ä¸­**ï¼ä½¿ç¨æ¶ç´æ¥åå»º `ZkClient` å¯¹è±¡ï¼è°ç¨å¶ç¸åºçæ¹æ³å³å¯ã

å¨ `ZkClient` çæé å½æ°ä¸­æå®è¿æ¥åæ°ï¼å®æå¯¹è±¡åå»ºåï¼ä¸ ZooKeeper çè¿æ¥ä¹å°±å·²ç»åå»ºå¥½ã`ZkClient` ä¸­æä¾äºä»¥ä¸å ä¸ªæé å½æ°ï¼

```java
public ZkClient(String serverstring)

public ZkClient(String zkServers, int connectionTimeout)

public ZkClient(String zkServers, int sessionTimeout, int connectionTimeout)

public ZkClient(String zkServers, int sessionTimeout, int connectionTimeout, ZkSerializer zkSerializer)

public ZkClient(final String zkServers, final int sessionTimeout, final int connectionTimeout, final ZkSerializer zkSerializer, final long operationRetryTimeout)

public ZkClient(IZkConnection connection)

public ZkClient(IZkConnection connection, int connectionTimeout)

public ZkClient(IZkConnection zkConnection, int connectionTimeout, ZkSerializer zkSerializer)

public ZkClient(final IZkConnection zkConnection, final int connectionTimeout, final ZkSerializer zkSerializer, final long operationRetryTimeout)
```

æé å¨åæ°çå«ä¹å¦ä¸ï¼

- `serverstring`ï¼æå®åä¸ªæå¤ä¸ªæå¡å¨å°å
- `connectionTimeout`ï¼`sessionTimeout`ï¼è¿æ¥è¶æ¶æ¶é´åä¼è¯è¶æ¶æ¶é´ãåä½é½æ¯æ¯«ç§ï¼å¶ä¸­ä¼è¯é»è®¤æ¯ 30000 æ¯«ç§ï¼ä¹å°±æ¯ 30 ç§ã
- `connection`ï¼`IZkConnection` çæ¥å£å®ç°ç±»
- `zkSerializer`ï¼èªå®ä¹çåºååå¨
- `operationRetryTimeout`ï¼å¨ä¸æå¡è¿æ¥æ­å¼åï¼è¿è¡éè¯æä½çæé¿æ¶é´ãä¹å°±æ¯è¯´ï¼å¦ææ­å¼æ¶é´æªè¶è¿``operationRetryTimeout`ï¼åæææä½è¿è¡éè¯ã`operationRetryTimeout` åä½ä¹æ¯æ¯«ç§ï¼å¦æä¼ å¥å°äº 0 çå¼ï¼åä¸ç´è¿è¡æä½éè¯ï¼ç´è³ä¸æå¡çè¿æ¥æ¢å¤

ä¸¾ä¸ªä¾å­ï¼

```java
public class TestZkClient {
    public static void main(String[] args) {
        ZkClient zkClient = new ZkClient("127.0.0.1:2181", 5000);
        System.out.println("æåå»ºç«è¿æ¥");
    }
}
```

### â¡ æ°æ®èç¹çå¢å æ¹æ¥

#### åå»ºèç¹

```java
public void createPersistent(String path)

public void createPersistent(String path, boolean createParents)

public void createPersistent(String path, boolean createParents, List<ACL> acl)

public void createPersistent(String path, Object data)

public void createPersistent(String path, Object data, List<ACL> acl)

public String createPersistentSequential(String path, Object data)

public String createPersistentSequential(String path, Object data, List<ACL> acl) 

public void createEphemeral(final String path)

public void createEphemeral(final String path, final List<ACL> acl)

public String create(final String path, Object data, final CreateMode mode)

public String create(final String path, Object data, final List<ACL> acl, final CreateMode mode) 

public void createEphemeral(final String path, final Object data)

public void createEphemeral(final String path, final Object data, final List<ACL> acl)

public String createEphemeralSequential(final String path, final Object data)

public String createEphemeralSequential(final String path, final Object data, final List<ACL> acl)
```

`createParents` åæ°å³å®äºæ¯å¦**éå½åå»ºç¶èç¹**ã`true` è¡¨ç¤ºéå½åå»ºï¼`false` è¡¨ç¤ºä¸ä½¿ç¨éå½åå»ºãæä»¥è¯´ ZkClient å¸®å¼åäººåçå»äºä¸å°ç¹ççæ£æ¥ååå»ºç¶èç¹çè¿ç¨ã

#### å é¤èç¹

å é¤èç¹æä¾äºä»¥ä¸æ¹æ³ï¼

```java
public boolean delete(final String path)

public boolean delete(final String path, final int version)

public boolean deleteRecursive(String path)12345
```

å é¤ API å¶å®å¾ç®åï¼éç¹è¯´ä¸ä¸ `deleteRecursive` æ¥å£ï¼è¿ä¸ªæ¥å£æä¾äº**éå½å é¤**çåè½ãå¨åç API ä¸­ï¼å¦æä¸ä¸ªèç¹å­å¨å­èç¹ï¼é£ä¹å®å°æ æ³ç´æ¥å é¤ï¼å¿é¡»ä¸å±å±éååå é¤å¨é¨å­èç¹ï¼ç¶åæè½å°ç®æ èç¹å é¤ã

#### è·å/æ´æ°èç¹æ°æ®åå®¹

ð¸ **è·åèç¹åå®¹**ï¼

```java
public <T extends Object> T readData(String path)

public <T extends Object> T readData(String path, boolean returnNullIfPathNotExists)

public <T extends Object> T readData(String path, Stat stat)12345
```

éè¿æ¹æ³è¿ååæ°çå®ä¹ï¼å°±å¯ä»¥å¾ç¥ï¼**è¿åçç»æï¼èç¹çåå®¹ï¼å·²ç»è¢«ååºååæå¯¹è±¡äº**ã

ð¸**æ´æ°èç¹åå®¹**ï¼

æ´æ°æä½å¯ä»¥éè¿ä»¥ä¸æ¥å£æ¥å®ç°ï¼

```java
public void writeData(String path, Object object)

public void writeData(final String path, Object datat, final int expectedVersion)

public Stat writeDataReturnStat(final String path, Object datat, final int expectedVersion)
```

#### çæµèç¹æ¯å¦å­å¨

æ­¤ API æ¯è¾ç®åï¼è°ç¨ä»¥ä¸æ¹æ³å³å¯ï¼

```java
protected boolean exists(final String path, final boolean watch)
```

#### è·åæä¸ªèç¹çææå­èç¹è·¯å¾

```java
public List<String> getChildren(String path)1
```

æ­¤æ¥å£è¿åå­èç¹çç¸å¯¹è·¯å¾åè¡¨ãæ¯å¦èç¹è·¯å¾ä¸º `/test/a1` å `/test/a2`ï¼é£ä¹å½ path ä¸º `/test` æ¶ï¼è¿åçç»æä¸º `[a1,a2]`ã

## ð References

- [ç¨åºæ°è§ç - Zookeeper ä¹å¼æºå®¢æ·ç«¯ ZkClient](https://blog.csdn.net/wo541075754/article/details/68929512)
- [JavaGuide](https://snailclimb.gitee.io/javaguide/#/docs/system-design/distributed-system/zookeeper/zookeeper-in-action?id=_3-zookeeper-javaå®¢æ·ç«¯-curatorç®åä½¿ç¨)
- [Github - ZKClient](https://github.com/sgroschupf/zkclient)
- [adyliu / ZKClient å¿«éæå](https://github.com/adyliu/zkclient/wiki/tutorial)