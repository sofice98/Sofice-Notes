@Sofice

网页开发学习笔记



# HTML

[常用对照表](http://tool.oschina.net/commons)

## 基本结构

```html
<!DOCTYPE html>//指定通用标记语言解析器
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>首页</title>
</head>
<body>
	<!--...-->
</body>
</html>
```
### head标签

内含标签包括：

|     标签      |                       作用                       |
| :-----------: | :----------------------------------------------: |
| !DOCTYPE html |              指定通用标记语言解析器              |
|     meta      | 网页介绍，关键字，网页编码，作者，自动跳转定义等 |
|     base      |             定义html网页默认打开方式             |
|     link      |       目标文件链接（css,js,favicon.ico等)        |
|    script     |                 引入或嵌入js代码                 |
|     style     |                嵌入网页的css代码                 |
|     title     |                   网页唯一标题                   |
#### meta
```html
//http-equiv:http协议文件头
<meta http-equiv="Content-Type" content="text/html" charset="utf-8" >//字符集
<meta http-equiv="Content-Language" content="en" >//页面语言
<meta http-equiv="refresh" content="1;url=http://www.baidu.com" />//重定向
<meta name="author" content="king">
<meta name="revised" content="king,01/15/2017">
<meta name="generator" content="Sublime Text3">
<meta name="description" content="HTML5文档head标签元素使用">
<meta name="keywords" content="HTML5, CSS, JavaScript">
```

|  http-equiv属性  |      描述      |                           使用方法                           |                             功能                             |
| :--------------: | :------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|   Content-Type   |     字符集     |     `<meta http-equiv="Content-Language" content="en" >`     |                                                              |
| Content-Language |    页面语言    |     `<meta http-equiv="Content-Language" content="en" >`     |                                                              |
|     refresh      |     重定向     | `<meta http-equiv="refresh" content="1;url=http://www.baidu.com" />` |                                                              |
|     expires      |      期限      |    `<meta http-equiv="expires" content="GMT格式时间" />`     |                       设定网页过期时间                       |
|      pragma      |   cache模式    |      `<meta http-equiv="pragma" content="no-cashe" />`       |            禁止浏览器从本地计算机的缓存中访问网页            |
|    Set-Cookie    | cookie过期设定 | `<meta http-equiv="Set-Cookie" content="cookie-value=xxx;expires=GMT格式时间；path" />` |         如果网页过期，保存在本机的全部cookie自动删除         |
|  Window-target   | 显示窗口的设定 | `<meta http-equiv="Window-target" content="GMT 格式时间" />` | 强制在当前窗口以独立页面方式显示（防止外部页面在框架里调用本页面） |

#### link

```html
<link rel="stylesheet" type="text/css" href="css/style.css" >
```

#### style

```html
<style type="text/css">
	h1 {font: bold 20px/2.0em arial,verdana;}
</style>
```

#### script

```html
<script type="text/javascript">
	document.write("<h1>HTML5 + CSS + JS --- head标签</h1>");
</script>
```

#### title

```html
<title>HTML 5 之网页标题</title>
```

#### base

页面上的所有链接规定的默认地址

+ 前面的base标签会覆盖后面的标签

```html
<base href="./url/" target="_blank" />
```

|  target属性值   |                      作用                      |
| :-------------: | :--------------------------------------------: |
|     _blank      |               在新的窗口打开链接               |
| _self（默认值） |                    自身窗口                    |
|     _parent     |      父窗口或超链接引用框架的框架集中打开      |
|      _top       | 清除所有被包含的框架并将文档载入整个浏览器窗口 |

### 引用css

1.外链式

```html
<link rel="stylesheet" type="text/css" href="css/style.css" >
```

2.嵌入式

+ 在head中

+ 单个页面

```html
<style type="text/css">
	h1 {font: bold 20px/2.0em arial,verdana;}
</style>
```

3.内联式

+ 单个元素

```html
<p style="color:black; margin:16px">
    Something
</p>  
```

### 引用js脚本

1.外链式

```html
<script type="text/javascript" src="js/src.js"></script>
```

2.嵌入式

```html
<script type="text/javascript">
	document.write("<h1>HTML5 + CSS + JS --- head标签</h1>");
</script>
```

## 网页排版

### 标签

| 标签 |      作用      |
| :--: | :------------: |
|  p   |    定义段落    |
|  hr  |     分割线     |
|  hx  |      标题      |
|  br  |      换行      |
| sup  |      上标      |
| sub  |      下标      |
|  ul  |    无序列表    |
|  ol  |    有序列表    |
|  li  |     列表项     |
|  dl  |   自定义列表   |
|  dt  |  自定义列表项  |
|  dd  | 自定义列表注释 |
#### 定义一个段落

```html
<p style="text-align: justify;text-indent: 2em;">
	...
</p>
```

#### 分割线

```html
<hr style="height:2px;border:dashed;">
```

#### 标题

```html
<h1 style="text-align: center">文章一号标题</h1>
<h2 style="text-align: center">文章二号标题</h2>
```

### 列表属性type

|       属性值       |   作用   |
|:----------------:|:------:|
| 1，I，i，A，a (il) | 有序列表样式 |
|        disc        | 实心圆点 |
|       circle       | 空心圆点 |
|       square       | 实心方形 |

### css样式

|    样式     |   作用   |                      示例                      |
| :---------: | :------: | :--------------------------------------------: |
| text-align  | 对齐方式 | justify：两端对齐，left：左对齐，right：右对齐 |
| text-indent | 缩进尺寸 |                 2em：字符长度                  |
|   height    |   高度   |                                                |
|   border    | 线条样式 |          dashed：虚线, double：双实线          |
| font-family | 字体样式 |             黑体, Microsoft YaHei              |



## 图像

```html
<img id="id-image" src="images/image.jpg"/>
```

| 属性 |  作用  | 示例 |
|:--:|:--:|:--:|
| width | 宽度 |  |
| height | 高度 |  |
| align | 图片位置 | bottom, middle, top, left, right, center |
| alt | 图片无法显示（路径不对）时显示的文本 | alt="图片无法加载" |

### 图片效果

#### 背景图片

```html
<body background="images/image.jpg">
    ...
</body>
```

+ gif、jpg、png格式图片均可用作HTML页面背景

+ 如果图像小于页面, 图像会自动进行重复

#### 图片超链接

```html
<p>
	把网页图像作为链接来使用<a href="#"><img src ="images/image_alink.jpg"></a>.
</p>
```



## 超链接
`<a>...</a>`

+ 绝对超链接：链接到网络上（非本站）的网页链接
+ 相对超链接：链接到本网站内的一个网页链接
+ 锚点超链接（书签）：链接到本页面特定位置（文字，段落，标题等）的链接

|  属性  |      作用      |           注意           |
| :----: | :------------: | :----------------------: |
|  href  |    超链接的    |       #代表本页面        |
|  name  |   锚点的名称   | 用 #+锚点名称 跳转到锚点 |
| target | 重定向打开方式 |                          |

### 电子邮件超链接

```html
//cc:抄送；subject：主题；body：正文
<a href="mailto:10001@qq.com?cc=10002@qq.com&subject=Email%20Subject&body=Email%20Body%20Text.">
	<p>
		mailto:10001@qq.com?cc=10002@qq.com<br>
		&subject=Email%20Subject<br>
		&body=Email%20Body%20Text.
	</p>
</a>
```

### 创建热点区域

通过定义标记可以在图像地图中设定作用区域  

```html
<img src="images/hotspot.jpg" border="1" usemap="#hotspot-map" />
    <map name="hotspot-map">
        <area
              shape="rect"
              coords="10,10,60,60"
              href="hotspot-rect.html" 
              target="_blank" />
	</map>
```



## 表格

### 表格标签

| 标签  | 作用 |
|:---:| :--:|
| table | 定义表格 |
| caption | 标题 |
| thead | 定义表头 |
| th | 表头单元格 |
| tbody | 定义表格主体 |
| tr | 表格行 |
| td | 表格主体单元格 |
| tfoot | 定义表注 |

### 表格标签属性

|      属性       |               作用                |         值          | 所属标签 |
| :-------------: | :-------------------------------: | :-----------------: | :------: |
|     border      |           是否显示边框            |       1：显示       |  table   |
|   cellpadding   | 单元格内容与其边框之间的空白距离  |                     |  table   |
|   cellspacing   |         单元格之间的距离          |                     |  table   |
| border-collapse | 设定表格合并边框模型，放到style中 | collapse, separate  |  table   |
|     rowspan     |               跨行                |                     |   主体   |
|     colspan     |               跨列                |                     |   主体   |
|     bgcolor     |               颜色                |       #e8e8e8       |   所有   |
|      align      |             对齐方式              | left, center, right |   所有   |



## 表单

### 表单标签

|   标签   |         作用         |
| :------: | :------------------: |
|   form   |       定义表单       |
|  input   |       输入信息       |
| fieldset | 将表单内相关元素分组 |

### 表单标签属性

#### form属性

|      属性      |               作用               |         值          |
| :------------: | :------------------------------: | :-----------------: |
| accept-charset | 定义服务器可处理的表单数据字符集 | utf-8, GBK, gb_2312 |
|     action     |      提交表单时发送目标URL       |                     |
|  autocomplete  |     是否启用表单自动完成功能     |       on, off       |
|    enctype     |         发送之前如何编码         |                     |
|     method     |     发送form-data的HTTP方法      |      get, post      |
|      name      |             表单名称             |                     |
|   novalidate   |       提交表单时不进行验证       |                     |
|     target     |        何处打开action URL        |        同上         |

#### input属性

|    属性     |     作用     |
| :---------: | :----------: |
|    type     | 表单元素类型 |
|    name     |  表单项名字  |
|     id      |   唯一标识   |
|    value    |    默认值    |
|  autofocus  |   自动焦点   |
| placeholder |   浅色提示   |

#### 表单元素

```html
//lable标签通过for属性=id值来关联表单元素
<label for="id_form_username">用户名:</label>
```

1.文本域——text

```html
<input type="text" name="name_form_username" id="id_form_username" placeholder="123" />
```

2.密码域——password

3.单选按钮——radio

+ name要一样

```html
<input type="radio" name="html_css_js" id="id_form_html" value="HTML" />
<input type="radio" name="html_css_js" id="id_form_css" value="CSS" />
<input type="radio" name="html_css_js" id="id_form_js" value="JavaScript" />
```

4.复选框——checkbox

+ name要一样

```html
<input type="checkbox" name="html_css_js[]" id="id_form_html" value="HTML" />
<input type="checkbox" name="html_css_js[]" id="id_form_css" value="CSS" />
<input type="checkbox" name="html_css_js[]" id="id_form_js" value="JavaScript" />
```

5.下拉列表——`<select><option>`

+ 属性selected表示默认选中项
+ 服务器端收到：{ web: 'js' }

```html
<select name="web">
    <option value="html">HTML</option>
    <option value="css">CSS</option>
    <option value="js" selected>JavaScript</option>
    <option value="php">PHP</option>
    <option value="asp">ASP.Net</option>
	<option value="C#">C#</option>
</select>
```

6.多行文本域——`<textarea>`

```html
<textarea
	name="name_textarea_web"
	id="id_textarea_web"
	rows="5"
	cols="25">
</textarea>
```

7.分组框——`<fieldset>`

+ legend标签为分组框标题

```html
<fieldset>
    <legend>最喜爱的编程语言</legend>
</fieldset>
```

8.邮件——email



9.数字——number

+ max：允许的最大值

+ min：允许的最小值

+ step：合法的数字间隔

10.滑动范围——range

+ max：允许的最大值

+ min：允许的最小值

```html
<input
	type="range"
	name="name_form_range"
	id="id_form_range"
	min="0"
	max="100"
	required />
```

11.搜索——search

12.url

13.日期选择器

+ data：日，月，年

+ month：月，年

+ week：周，年

+ time：时间（小时和分钟）

+ datetime：时间，日，月，年（UTC）
















# CSS





















