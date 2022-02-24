# MongoDB

[教程](http://www.runoob.com/mongodb/mongodb-tutorial.html)    [API](https://docs.mongodb.com/?_ga=2.132473102.1488481803.1544703497-901425356.1544703497)    [csdnAPI](https://blog.csdn.net/vbirdbest/article/details/76037827)

## 启动MongoDB服务

mongod -dbpath <dir> 创建/进入指定文件夹下的mongodb数据库

mongod 还能接收一个配置文件：<setting> = <value>



## MongoDB shell

mongo 链接当前开启的MongoDB服务

### 基础命令

- help<option> ：获取帮助

- use <database> ：修改当前数据库句柄

- show <option> ：显示 dbs:数据库，collections:集合，users：用户列表

- exit：退出

### 执行js脚本

+ MongoDB shell中：load("./test.js")
+ 命令行中：mongo test.js

### 数据库

```bash
//数据库参数
db.stats()
//删除数据库
db.dropDatabase()
```



### 集合

```shell
//创建集合
db.createCollection("test") 
//更改集合名
db.renameCollection("test")
//删除集合
db.test.drop()
```

### 文档——crud

#### 增——c

```shell
db.test.insert(json)
```

#### 查——r

```shell
//文档数量
db.test.count()
//查找文档
db.test.find()
db.test.findOne()
//查找某字段所有值集合
db.test.distinct()

```
+ find参数
```shell
//按字段查询
db.test.find({ "":"" })
//$gte大于等于，$gt大于，$lte小于等于，$lte小于，$eq等于，$ne不等于
db.test.find({ "":{$gte:4} })
//正则表达式：/k/含k,/^k/以k开头
db.test.find({ "":/k/ })
//$or或
db.test.find({ $or:[{ "":4 },{ "":"a" }] })
//$in包含某些值，$nin不包含某些值
db.test.find({ "":{ $in:[3,4] } })
//$exists是否存在某字段
db.test.find({ "":{ $exists:true } })
//指定抽出字段
db.test.find({}, { title:true, rank:1 , _id:0})
//sort()排序,1升序，-1降序
db.test.find().sort({rank:1})
//limit()限制输出文档数量
db.test.find().limit(3)
//skip()跳过前几条文档再开始输出
db.test.find().skip(3)
```
+ sort，limit，skip配合使用可以实现换页显示

#### 改——u

```shell
db.test.update(<filter>,<update>,<options>)
db.test.update({}, { "":10 })
//$set:只更新指定字段（！不加时会把所有其他字段删除！）,新增or修改
db.test.update({}, { $set:{"":10} })
//$inc：加，$mul：乘，$rename：重命名查询到的文档的某字段，$unset：删除某字段
db.test.update({}, { $inc:{"":10} })
db.test.update({}, { $mul:{"":10} })
db.test.update({}, { $rename:{"":""} })
db.test.update({}, { $unset:{"":true} })
//multi:需要更新所有文档
db.test.update({}, { "":10 }, { multi:true })
//upsert：有则更新，无则追加
db.test.update({}, { "":10 }, { upsert:true })
```
#### 删——d

```shell
db.test.remove({})
```

### 索引

```html
//获取集合所有索引
db.test.getIndexes()
//建立索引，unique：不能重复
db.test.createIndex({"":1})
db.test.createIndex({"":1},{unique:true})
//删除索引
db.test.dropIndex({})
```



















## 备份

mongodump -d test：备份指定数据库

mongorestore --drop：恢复数据库





# Node.js中使用MongoDB

## MongoClient

```javascript
var MongoClient = require("mongodb").MongoClient;
var MongoServer = require("mongodb").Server;
//var mongo = new MongoClient();//创建实例
//var mongo = new MongoClient(new MongoServer("localhost",27017));
MongoClient.connect("mongodb://localhost/",(err,db)=>{
	console.log('连接成功');
    var myDB = db.db("test")//获取Database对象
})；


```

+ 链接url：`mongodb://username:password@host:port/database?options`
+ 当读写数据库并执行其他操作时，必须在回调函数中进行

### MongoClient对象

| MongoClient对象的方法 | 描述                                                    | callback第二个参数 |
| --------------------- | ------------------------------------------------------- | ------------------ |
| close()               | 关闭连接                                                |                    |
| connect(url,callback) | 根据指定的连接字符串打开链接                            | MongoClient对象    |
| open(callback)        | 根据创建MongoClient对象时使用的Server对象的设置打开连接 | MongoClient对象    |
| db(name)              | 返回一个Database对象                                    |                    |

### Database对象

| Database对象的方法                        | 描述                       | callback第二个参数 |
| ----------------------------------------- | -------------------------- | ------------------ |
| addUser(username,password,callback)       | 在当前数据库中添加用户账户 |                    |
| createCollection(name,[options],callback) | 创建集合                   |                    |
| collections(callback)                     |                            | 所有集合的数组     |
| collection(name,callback)                 | 获取集合                   | Collection对象     |
| dropCollection(name,callback)             | 删除集合                   |                    |
| removeUser(username)                      | 从当前数据库中删除用户账户 |                    |

### Collection对象

| Collection对象的方法                    | 描述                         | callback第二个参数 |
| --------------------------------------- | ---------------------------- | ------------------ |
| insert(documents,[options],callback)    | 插入文档                     | 新文档             |
| find([query],[options],callback)        | 查找文档并返回一个Cursor对象 | Cursor对象         |
| update(query,update,[options],callback) | 更新文档                     |                    |
| remove([query],[options],callback)      | 删除文档                     |                    |
| rename(newName,callback)                | 重命名文档                   |                    |
| count([query],[options],callback)       | 文档计数                     | 数量               |
| drop(callback)                          |                              |                    |

























