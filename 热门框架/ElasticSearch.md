# 大数据工具发展史

**Lucene**是**Doug Cutting**用java写成，用来做**全文检索功能**，2001年成为Apache的jakarta项目的一个子项目，包含索引结构，读写索引的工具，排序、搜索规则等等。

2004年，Doug Cutting在Lucene的基础上开发了**Nutch**，基于Lucene增加了爬虫等相关功能，目的是将站内检索推广到全球搜索，使低成本的普通计算机可以取代高价的web服务器。但大数据时代下，效率不行。

2003年，Google公开了自己的谷歌文件系统 **GFS**（Google File System），专门为了存储海量搜索数据。2004年，Doug Cutting基于GFS实现了分布式文件存储系统 **NDFS**（Nutch Distributed File System）。

![image-20211227160707470](http://mdimg.sofice.top/202112271607537.png)

2004年，Google发表了 **MapReduce** 模型，用于大规模数据集的并行分析运算。2005年，Doug Cutting基于MapReduce，在Nutch搜索引擎实现了该功能。

![image-20211227160916963](http://mdimg.sofice.top/202112271609003.png)

2006年，Doug Cutting加入Yahoo公司，将NDFS和MapReduce进行了升级改造，重新命名为 Hadoop，NDFS改名为HDFS（Hadoop Distributed File System）。

![image-20211227161247437](http://mdimg.sofice.top/202112271612480.png)

2006年，Google发表 BigTable，一种用来处理海量数据的非关系型数据库。Doug Cutting在Hadoop引入BigTable，命名为HBase。

![image-20211227161404500](http://mdimg.sofice.top/202112271614537.png)

# ElasticSearch概述

Port：9200

ElasticSearch基于Lucene做了封装和增强，通过RESTful隐藏Lucene的复杂性，是一个**高扩展的分布式全文搜索引擎**。可以近乎实时存储、检索数据。处理PB级别的数据。

用作搜索，数据分析，管理数据，日志数据分析（ELK，elasticsearch + logstash + kibana）。



**Solr**

基于Lucene的全文搜索引擎，可独立运行，也可运行在Servlet 容器中。

Solr索引实现方法：用POST方法向Solr服务器发送一个描述 Field 及其内容的 XML 文档，Solr根据 XML 文档添加、删除、更新索引。

Solr搜索实现方法：发送GET请求，对返回的 XML、json 进行解析。



**比较ElasticSearch与Solr**

- **单纯对已有数据进行搜索**时，Solr更快
- 实时**建立索引**时，Solr会产生IO阻塞，ElasticSearch更快
- 随着数据量增加，Solr搜索效率会变得很低，而ElasticSearch没有明显变化
- Solr基于ZooKeeper，而ElasticSearch自带分布式协调管理
- Solr支持JSON，XML，CSV等，而ElasticSearch只支持JSON





## 核心原理

**面向文档**的非关系型数据库，单个就是。

![image-20211227164116208](http://mdimg.sofice.top/202112271641272.png)

字段类型可以自动填充，也可提前做好映射。

**底层设计**

把每个索引划分成分片，每个分片可以在集群中不同服务器间迁移。

一个集群至少有一个节点（elasticsearch进程）。

默认一个索引有5个分片（主分片），每个主分片有一个副本（复制分片）。多节点会将分片和副本分布在不同节点上，保证一直有备份。

![image-20211227165216301](http://mdimg.sofice.top/202112271652355.png)

### 倒排索引

ES采用Lucene倒排作为底层，适用于快速的全文搜索。

倒排索引中，对于每个词，都有一个包含它的文档列表，用来统计每个词出现在了哪个文档中。

搜索倒排索引，即可获取文档相关度得分。



## 安装

【elasticsearch.yml】

```yaml
network.host: 0.0.0.0
cluster.initial_master_nodes: ["node-1", "node-2"]
# 跨域请求问题
http.cors.enabled: true
http.cors.allow-origin: "*"
```

【/etc/sysctl.conf】

```
vm.max_map_count=655360
```



# Kibana

Port：5601

汉化：kibana.yml，`i18n.locale: "zh-CN"`



# Logstash



# ELK

![ELK-基础系列(一)-简介](http://mdimg.sofice.top/202112271632688.jpeg)



https://zhuanlan.zhihu.com/p/121099453



# Rest风格基本命令

![image-20211229170758935](http://mdimg.sofice.top/202112291707432.png)

绑定类型，默认类型名为 _doc（`/test/_doc/1`）

```json
PUT /test1
{
  "mappings": {
    "properties": {
      "name":{
        "type": "text"
      },
      "age":{
        "type": "long"
      }
    }
  }
}
```

查看系统信息

```
GET /_cat/indices?v
```

查询：

term：精确查询

match：分词器解析	

```json
GET /test1/_doc/_search
{
  "query": {
    "match": {
      "name": "szy"
    }
  },
  "_source": ["name"],
  "sort": [
    {
      "age": {
        "order": "asc"
      }
    }
  ],
  "filter": {
    "range": {
      "age": {
        "gte": 30,
        "lte": 20
      }
    }
  },
  "from": 0,
  "size": 2,
}
```

must（and），should（or）



# IK分词器

下载：https://github.com/medcl/elasticsearch-analysis-ik/releases

解压后放入es下的 plugins/ik 中

![image-20211227200442819](http://mdimg.sofice.top/202112272004875.png)

ik_smart为最少切分，ik_max_word为最细粒度切分

**自定义字典**

【ik/config/IKAnalyzer.cfg.xml】

将自己写dic文件放进去即可

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE properties SYSTEM "http://java.sun.com/dtd/properties.dtd">
<properties>
	<comment>IK Analyzer 扩展配置</comment>
	<!--用户可以在这里配置自己的扩展字典 -->
	<entry key="ext_dict">sofice.dic</entry>
	 <!--用户可以在这里配置自己的扩展停止词字典-->
	<entry key="ext_stopwords"></entry>
	<!--用户可以在这里配置远程扩展字典 -->
	<!-- <entry key="remote_ext_dict">words_location</entry> -->
	<!--用户可以在这里配置远程扩展停止词字典-->
	<!-- <entry key="remote_ext_stopwords">words_location</entry> -->
</properties>
```

测试，使用kibana开发工具

```
GET _analyze
{
	"analyzer": "ik_smart",
	"test": "中华人民共和国万岁"
}
GET _analyze
{
	"analyzer": "ik_max_word",
	"test": "中华人民共和国万岁"
}
```



