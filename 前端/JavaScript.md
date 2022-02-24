@Sofice

网页开发学习笔记

# JavaScript

## 基础

### console

```javascript
console.log("hello")//输出
var json1=[			//json对象
		{name:"sizhanyu",age:20},
		{name:"yezhuangzhuang",age:21}
	]
console.dir(js)		//输出一个对象所有属性和方法
```

### function

```javascript
//普通函数
function add(a,b){
    console.log(a+b);
}
add(3+4)//使用
//表达式函数
var add=function(a,b){
    console.log(a+b);
}
//回调函数
function callback(fun,a,b){
	fun(a,b);
}
callback(add,3,4);//使用回调函数（不加括号）
callback(function(a,b){//使用匿名函数参数的回调函数,此时不需定义add
    console.log(a+b);
},3,4);
callback((a,b)=>{//ES6
    console.log(a+b);
},3,4);
```

### 模块

```javascript
//主文件 app.js
var stuff=require('./count.js')//导入模块
console.log(stuff.add(3,4));//取出对象
console.log(stuff.pi);
```

```javascript
//模块文件 count.js,与主文件在同一目录下
var add=(a,b)=>{
	return 'the sum is '+(a+b);
}
var pi=3.14;
module.exports={//导出对象
	add:add,//外部名字：内部名字
	pi:pi,
}
```

### 事件

```javascript
var events=require('events')
var myEmitter = new events.EventEmitter();

myEmitter.on('someEvent',function(message){//定义事件someEvent
	console.log(message);
})
myEmitter.emit('someEvent','the event was emitted')//触发事件someEvent

```





# Node.js

[Node.js官网](http://nodejs.cn/api/)

## 命令

1.npm install xxx -g——安装模块

2.nodemon xxx.js——监测js文件变动然后重新启动（需要安装nodemon模块）



## 模块

[npm官网](https://www.npmjs.com/)

+ 优先从缓存中加载，不会重复加载相同模块

### express模块

——服务器开发

[API](http://expressjs.com/en/4x/api.html)

```javascript
var express = require('express');
var app = express();
```

#### 监听端口

```javascript
app.listen(4321);
```

#### Get

```javascript
app.get('/routine/:a/and/:b',function(req, res，next){	//req：请求 res：回答	next:下一个中间件
	var responseObject1 = [			//传送json数据
		{ name:"sizhanyu",age:20 },
		{ name:"yezhuangzhuang",age:21 }
	];
	var responseObject2 = "Hellow!!!";
	res.send(responseObject1);
	res.json(responseObject2);
    console.log(req.query);//提取\?后的内容
	console.log(req.params);//提取url（路由参数）
    res.send("the url is: /routine/" + req.params.a+"/and/" + req.params.b);
    res.end();//快速响应,一般不带参数
});
```



#### Post

```javascript
app.post('/',function(req, res){
	console.log(req.body);//提取post数据
	res.send("ok");
});
```



#### res.send/json/end

不能send多次！

1.发送buffer：

```javascript
res.set('Content-Type', 'text/html');
res.send(new Buffer('<p>some html</p>'));
```

2.发送string：

```javascript
res.send('<p>some html</p>');
```

3.发送Arrayor 或 Object：

```javascript
res.send(responseObject1);
```

4.发送文件/网页

```javascript
res.sendFile(__dirname+"/01index.html")
```

#### 重定向

```javascript
app.post('/mypost',function(req,res){
	res.redirect(302, '/');//重定向到首页
});
```



### body-parser模块

——中间件

[API](https://www.npmjs.com/package/body-parser)

```javascript
var bodyParser = require('body-Parser');
var app = express();
//处理urlencoded
app.use(bodyParser.urlencoded({ extended: false }));
//或者
var urlencodedParser = bodyParser.urlencoded({ extended: false });
app.post('/ue',urlencodedParser,function(req,res){});
//处理json
app.use(bodyParser.json());
```



### multer模块

——处理文件上传（中间件），用于处理 `multipart/form-data` 类型的表单数据

[API](https://github.com/expressjs/multer/blob/master/doc/README-zh-cn.md)

```javascript
var multer  = require('multer')
var upload = multer({ dest: 'uploads/' })
```

如果你想在上传时进行更多的控制，你可以使用 `storage` 选项替代 `dest`。Multer 具有 `DiskStorage` 和 `MemoryStorage` 两个存储引擎；另外还可以从第三方获得更多可用的引擎。

#### 上传

```javascript
app.post('/profile', upload.single('avatar'), function (req, res, next) {
  // req.file 是 `avatar` 文件的信息
  // req.body 将具有文本域数据，如果存在的话
})
```
#### DiskStorage引擎

```javascript
var storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, './uploads')//文件保存的路径
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname)//文件名
  }
})

var upload = multer({ storage: storage })
```



### fs模块

——处理文件

[API](http://nodejs.cn/api/fs.html)

```javascript
var fs = require('fs');

var file = fs.readFileSync('readme.txt', "utf8");//同步读取文件,返回文件中的字符串
var file = fs.readFile('readme.txt', "utf8"，function(err,data){//异步读取文件
    console.log(data);
});

fs.writeFileSync('writeme.txt', "this string will be written in file");//同步写文件

fs.mkdirSync('stuff');//新建文件夹
fs.rmdirSync('stuff');//删除文件夹
```

#### 流和管道

读写流：

```javascript
var myReadStream = fs.createReadStream('./readMe.txt');//创建读取流，分块处理
//var myReadStream = fs.createReadStream('./readMe.txt', 'utf8');//utf8格式
myReadStream.on('data',(chunk)=>{//收到数据
	console.log(chunk);
})
myReadStream.on('end',()=>{//接受完成
	console.log(chunk);
})

var mywriteStream = fs.createWriteStream('./writeMe.txt');//utf8格式
mywriteStream.write("this string will be written in file");
mywriteStream.end();
mywriteStream.on('finish',()=>{
    console.log("finished!")
})
```

管道：

```javascript
myReadStream.pipe(mywriteStream)
```



## 模板引擎

为了使用户界面与业务数据（内容）分离而产生的，它可以生成特定格式的文档，用于网站的模板引擎就会生成一个标准的HTML文档

### EJS

[官方API](https://ejs.bootcss.com/)   [github API](https://github.com/mde/ejs)   [教程](https://blog.csdn.net/u014695532/article/details/51334806)

新建一个views文件夹，必须叫views，否则报错。把HTML文件的后缀名改成ejs

```javascript
app.set('views', './views');  // 指定模板文件存放位置
app.set('view engine', 'ejs');  // 设置默认的模板引擎
```

#### 发送

```javascript
app.get('/',function(req,res){
    var data = "hello";
	res.render('todo',{ todos:data });//发送给浏览器：todo.ejs,不用加后缀。data赋值给ejs文件里的变量todos
})
```

#### 调用

```ejs
//todo.ejs
//每一行js代码加<%= ... %>
<%- include('header') -%>				//引用其他ejs，加-号避免html转义
<% todos.forEach(function(todo) { %>	//流程控制，无输出
<li><%= todo.item %></li>				//加=为转义输出
<% }) %>
```



## 中间件

处理请求和响应之间的过程

[API](http://www.expressjs.com.cn/guide/using-middleware.html)

### 使用

```javascript
//路由地址可选
app.use('/'， express.static('./public'))//使用静态文件

app.use('/', function (req, res, next) {
  console.log('Time:', Date.now())
  next()
})
```

引用其他路由文件

```javascript
//index.js
var router = express.Router();
router.get('/',function(req,res,next){//这里路由地址不用加额外参数
    res.send('root');
})
module.exports = router;
```

```javascript
//server.js
var indexRouter = require('./routes/index')
app.use('/', indexRouter);
```

## 连接MongoDB

[API](http://mongodb.github.io/node-mongodb-native/3.1/api/)





# 开发工具

## Sublime Text3

——html,css,js代码编辑器

### 插件

1.AutoFileName

2.BracketHighlighter

3.DocBlockr

4.Emmet

5.JsFormat

6.Package Control——管理插件

7.Side Bar——管理文件操作

8.View in Browser——快速在浏览器中访问当前网页

9.Nodejs

10.SublimeCodeIntel——代码提示，需要配置文件

11.ColorPicker——ctrl+shift+c

## Typora

——Markdown编辑器

## Postman

——模拟前端表单发送















