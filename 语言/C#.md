

# .Net框架

.Net 框架是一个创新的平台，能帮您编写出下面类型的应用程序：Windows 应用程序，Web 应用程序，Web 服务

.Net 框架应用程序是多平台的应用程序。框架的设计方式使它适用于下列各种语言：C#、C++、Visual Basic、Jscript、COBOL 等等。所有这些语言可以访问框架，彼此之间也可以互相交互。

.Net 框架由一个巨大的代码库组成，用于 C# 等客户端语言。下面列出一些 .Net 框架的组件：

- 公共语言运行库（Common Language Runtime - CLR）
- .Net 框架类库（.Net Framework Class Library）
- 公共语言规范（Common Language Specification）
- 通用类型系统（Common Type System）
- 元数据（Metadata）和组件（Assemblies）
- Windows 窗体（Windows Forms）
- ASP.Net 和 ASP.Net AJAX



# C#基础

## 程序结构


```c#
using System;
namespace RectangleApplication
{
    class Rectangle
    {
        // 成员变量
        double length;
        double width;
        public void Acceptdetails(){
            length = 4.5;    
            width = 3.5;
        }
        public double GetArea(){
            return length * width;
        }
        public void Display(){
            Console.WriteLine("Length: {0}", length);
            Console.WriteLine("Width: {0}", width);
            Console.WriteLine("Area: {0}", GetArea());
        }
    }
   
    class ExecuteRectangle
    {
        static void Main(string[] args){
            Rectangle r = new Rectangle();
            r.Acceptdetails();
            r.Display();
            Console.ReadLine();
        }
    }
}
```

## 数据类型

- **值类型**

  从类`System.ValueType`中派生，获取大小：`sizeof(int)`

  | 类型    | 描述                                 | 范围                                                    | 默认值 |
  | ------- | ------------------------------------ | ------------------------------------------------------- | ------ |
  | bool    | 布尔值                               | True 或 False                                           | False  |
  | byte    | 8 位无符号整数                       | 0 到 255                                                | 0      |
  | char    | 16 位 Unicode 字符                   | U +0000 到 U +ffff                                      | '\0'   |
  | decimal | 128 位精确的十进制值，28-29 有效位数 | (-7.9 x 1028 到 7.9 x 1028)  / 100 到 28                | 0.0M   |
  | double  | 64 位双精度浮点型                    | (+/-)5.0 x 10-324 到 (+/-)1.7 x 10308                   | 0.0D   |
  | float   | 32 位单精度浮点型                    | -3.4 x 1038 到 + 3.4 x 1038                             | 0.0F   |
  | int     | 32 位有符号整数类型                  | -2,147,483,648 到 2,147,483,647                         | 0      |
  | long    | 64 位有符号整数类型                  | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807 | 0L     |
  | sbyte   | 8 位有符号整数类型                   | -128 到 127                                             | 0      |
  | short   | 16 位有符号整数类型                  | -32,768 到 32,767                                       | 0      |
  | uint    | 32 位无符号整数类型                  | 0 到 4,294,967,295                                      | 0      |
  | ulong   | 64 位无符号整数类型                  | 0 到 18,446,744,073,709,551,615                         | 0      |
  | ushort  | 16 位无符号整数类型                  | 0 到 65,535                                             | 0      |

- **引用类型**

  内置的 引用类型有：object、dynamic 和 string

  **对象(Object)类型**：是 C# 通用类型系统(Common Type System - CTS)中所有数据类型的终极基类，可以被分配任何其他类型，需要先进行类型转换

  **动态(Dynamic)类型**：可以存储任何类型的值在动态数据类型变量中，这些变量的类型检查是在运行时发生的

  **字符串(String)类型**：前面可以加 @（称作"逐字字符串"）将转义字符（\）当作普通字符对待，@ 字符串中可以任意换行，换行符及缩进空格都计算在字符串长度之内。

- **指针类型**

  与 C 或 C++ 中的指针有相同的功能

- **可空类型（Nullable）**

  可空类型可以表示其基础值类型正常范围内的值，再加上一个 null 值

  ```c#
  int? ii; //默认值null
  int? num1 = null;
  int? num2 = 3;		//即：Nullable<int> num2 = new Nullable<int>(3);
  double? num3 = new double?();
  ```

  Null 合并运算符用于定义可空类型和引用类型的默认值，把操作数类型隐式转换为另一个可空（或不可空）的值类型的操作数的类型。如果第一个操作数的值为 null，则运算符返回第二个操作数的值，否则返回第一个操作数的值

  ```c#
  int? num1 = null;
  int? num2 = 3;
  int num3;
  num3 = num1 ?? 5;	// num3 = 5
  num3 = num2 ?? 5;	// num3 = 3
  ```

**类型转换：**`ToInt32,ToChar,ToString,ToBoolean` 等等



## I/O

```c#
Console.WriteLine("a = {0}, b = {1}, c = {2}", a, b, c);
num = Convert.ToInt32(Console.ReadLine());
// 文件I/O
FileStream F = new FileStream("sample.txt", FileMode.Open, FileAccess.Read, FileShare.Read);
```

System.IO 命名空间中常用的非抽象类：

| I/O 类         | 描述                               |
| -------------- | ---------------------------------- |
| BinaryReader   | 从二进制流读取原始数据。           |
| BinaryWriter   | 以二进制格式写入原始数据。         |
| BufferedStream | 字节流的临时存储。                 |
| Directory      | 有助于操作目录结构。               |
| DirectoryInfo  | 用于对目录执行操作。               |
| DriveInfo      | 提供驱动器的信息。                 |
| File           | 有助于处理文件。                   |
| FileInfo       | 用于对文件执行操作。               |
| FileStream     | 用于文件中任何位置的读写。         |
| MemoryStream   | 用于随机访问存储在内存中的数据流。 |
| Path           | 对路径信息执行操作。               |
| StreamReader   | 用于从字节流中读取字符。           |
| StreamWriter   | 用于向一个流中写入字符。           |
| StringReader   | 用于读取字符串缓冲区。             |
| StringWriter   | 用于写入字符串缓冲区。             |



| 参数       | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| FileMode   | **FileMode** 枚举定义了各种打开文件的方法。FileMode 枚举的成员有：**Append**：打开一个已有的文件，并将光标放置在文件的末尾。如果文件不存在，则创建文件。 **Create**：创建一个新的文件。如果文件已存在，则删除旧文件，然后创建新文件。 **CreateNew**：指定操作系统应创建一个新的文件。如果文件已存在，则抛出异常。 **Open**：打开一个已有的文件。如果文件不存在，则抛出异常。 **OpenOrCreate**：指定操作系统应打开一个已有的文件。如果文件不存在，则用指定的名称创建一个新的文件打开。 **Truncate**：打开一个已有的文件，文件一旦打开，就将被截断为零字节大小。然后我们可以向文件写入全新的数据，但是保留文件的初始创建日期。如果文件不存在，则抛出异常。 |
| FileAccess | **FileAccess** 枚举的成员有：**Read**、**ReadWrite** 和 **Write**。 |
| FileShare  | **FileShare** 枚举的成员有： **Inheritable**：允许文件句柄可由子进程继承。Win32 不直接支持此功能。 **None**：谢绝共享当前文件。文件关闭前，打开该文件的任何请求（由此进程或另一进程发出的请求）都将失败。  **Read**：允许随后打开文件读取。如果未指定此标志，则文件关闭前，任何打开该文件以进行读取的请求（由此进程或另一进程发出的请求）都将失败。但是，即使指定了此标志，仍可能需要附加权限才能够访问该文件。 **ReadWrite**：允许随后打开文件读取或写入。如果未指定此标志，则文件关闭前，任何打开该文件以进行读取或写入的请求（由此进程或另一进程发出）都将失败。但是，即使指定了此标志，仍可能需要附加权限才能够访问该文件。  **Write**：允许随后打开文件写入。如果未指定此标志，则文件关闭前，任何打开该文件以进行写入的请求（由此进程或另一进过程发出的请求）都将失败。但是，即使指定了此标志，仍可能需要附加权限才能够访问该文件。  **Delete**：允许随后删除文件。 |



## 数组(Array)

```c#
int[] n = new int[10];
//遍历数组
foreach (int elem in n ){
    int i = elem-100;
    Console.WriteLine("Element[{0}] = {1}", i, j);
}
//传参
public int AddElements(int[] arr)
//参数数组
public int AddElements(params int[] arr)
```



## 字符串(String)



## 结构(Struct)

C# 中的结构有以下特点：

- 结构可带有方法、字段、索引、属性、运算符方法和事件。
- 结构可定义构造函数，但不能定义析构函数。但是，**不能为结构定义无参构造函数**。无参构造函数(默认)是自动定义的，且不能被改变。
- **结构体中声明的字段无法赋予初值**
- 与类不同，**结构不能继承其他的结构或类**。
- 结构不能作为其他结构或类的基础结构。
- 结构可实现一个或多个接口。
- 结构成员不能指定为 abstract、virtual 或 protected。
- 当您使用 **New** 操作符创建一个结构对象时，会调用适当的构造函数来创建结构。与类不同，结构可以不使用 New 操作符即可被实例化。
- 如果不使用 New 操作符，只有在所有的字段都被初始化之后，字段才被赋值，对象才被使用。



枚举

```c#
enum Days { Sun, Mon, tue, Wed, thu, Fri, Sat };
int x = (int)Day.Sun;
```







## 面向对象

**类(Class)**

```c#
class Line
{
    private double length;   
    public Line(){				// 默认构造函数
        Console.WriteLine("对象已创建");
    }
    public Line(double len){  	// 参数化构造函数
        Console.WriteLine("对象已创建，length = {0}", len);
        length = len;
    }
 	~Line(){ 					//析构函数
        Console.WriteLine("对象已删除");
    }
}
```

**方法**

```c#
<Access Specifier> <Return Type> <Method Name>(Parameter List){
   Method Body
}
```

**参数传递**

按值传递参数：这是参数传递的默认方式 

按引用传递参数：使用 **ref** 关键字声明引用参数

按输出传递参数：输出参数会把方法输出的数据赋给自己，其他方面与引用参数相似，使用 **out** 关键字声明输出参数



**访问修饰符**

- public：所有对象都可以访问；
- private：对象本身在对象内部可以访问；
- protected：只有该类对象及其子类对象可以访问
- internal：同一个程序集的对象可以访问；
- protected internal：访问限于当前程序集或派生自包含类的类型。



**抽象**

```c#
abstract class Shape
{
	abstract public int area();
}
```



**继承**

```c#
// 派生类
class Tabletop : Line
{
    public Tabletop(double l) : base(l){ }
}
//C# 不支持多重继承，但可以使用接口来实现多重继承
class Rectangle : Shape, PaintCost
```



**多态**

静态多态性

在编译时，函数和对象的连接机制被称为早期绑定，也被称为静态绑定。C# 提供了两种技术来实现静态多态性。分别为：

- 函数重载（函数特征不同）
- 运算符重载 `public static Box operator+ (Box b, Box c)`

动态多态性

使用关键字 **abstract** 创建抽象类，用于提供接口的部分类的实现

- **Virtual方法（虚方法）**

　　virtual 关键字用于在基类中修饰方法。virtual的使用会有两种情况：

　　情况1：在基类中定义了virtual方法，但在派生类中没有重写该虚方法。那么在对派生类实例的调用中，该虚方法使用的是基类定义的方法。

　　情况2：在基类中定义了virtual方法，然后在派生类中使用override重写该方法。那么在对派生类实例的调用中，该虚方法使用的是派生重写的方法。

- **Abstract方法（抽象方法）**

  abstract关键字**只能用在抽象类中修饰方法**，并且没有具体的实现。抽象方法的实现必须在派生类中使用override关键字来实现。



**接口**

接口使用 **interface** 关键字声明，它与类的声明类似，接口声明默认是 public 的

```c#
interface IMyInterface
{
    void MethodToImplement();
}
//接口继承
interface IMyInterface : IParentInterface
{
    void MethodToImplement();
}
```



## 预处理器指令

在 C# 中，预处理器指令用于在条件编译中起作用。与 C 和 C++ 不同的是，它们不是用来创建宏。



## 正则表达式

```c#
using System.Text.RegularExpressions;
//查找
MatchCollection mc = Regex.Matches("A Thousand Splendid Suns", @"\bS\S*");
foreach (Match m in mc)
{
    Console.WriteLine(m);
}
//替换
Regex rgx = new Regex("\\s+");
string result = rgx.Replace("Hello   World   ", " ");
```



## 异常处理

C# 中的异常类主要是直接或间接地派生于 **System.Exception** 类。**System.ApplicationException** 和 **System.SystemException** 类是派生于 System.Exception 类的异常类。

**System.ApplicationException** 类支持由应用程序生成的异常。所以程序员定义的异常都应派生自该类。

**System.SystemException** 类是所有预定义的系统异常的基类。

- **try**：一个 try 块标识了一个将被激活的特定的异常的代码块。后跟一个或多个 catch 块。
- **catch**：程序通过异常处理程序捕获异常。catch 关键字表示异常的捕获。
- **finally**：finally 块用于执行给定的语句，不管异常是否被抛出都会执行。例如，如果您打开一个文件，不管是否出现异常文件都要被关闭。
- **throw**：当问题出现时，程序抛出一个异常。使用 throw 关键字来完成。

| 异常类                            | 描述                                           |
| --------------------------------- | ---------------------------------------------- |
| System.IO.IOException             | 处理 I/O 错误。                                |
| System.IndexOutOfRangeException   | 处理当方法指向超出范围的数组索引时生成的错误。 |
| System.ArrayTypeMismatchException | 处理当数组类型不匹配时生成的错误。             |
| System.NullReferenceException     | 处理当依从一个空对象时生成的错误。             |
| System.DivideByZeroException      | 处理当除以零时生成的错误。                     |
| System.InvalidCastException       | 处理在类型转换期间生成的错误。                 |
| System.OutOfMemoryException       | 处理空闲内存不足生成的错误。                   |
| System.StackOverflowException     | 处理栈溢出生成的错误。                         |










