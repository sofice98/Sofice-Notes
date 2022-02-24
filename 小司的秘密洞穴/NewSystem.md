**【版本兼容是一个很重要的问题】**

# 华硕

## 驱动问题

微软商店搜MyASUS

MyASUS里下载驱动：芯片组，graphic，networking，公用程序，蓝牙

![image-20201024150217747](http://mdimg.sofice.top/202112111341495.png)

**一定要安装以下几个**，不然cpu会降频

![image-20201024150606376](http://mdimg.sofice.top/202112111341542.png)

其他可用鲁大师





# Windows10

## 重装

MSDN镜像：https://msdn.itellyou.cn/

MSDN镜像使用方法：1、插入U盘。

2、运行CMD。

3、输入diskpart。

4、查看当前系统的磁盘列表序号，输入 list disk，磁盘序号从0开始，如电脑只有一个硬盘的，则U盘的磁盘序号为1。如已经确认U盘的磁盘序号，可跳过这个步骤。

5、选择U盘，输入select disk 1。

6、删除U盘内容，输入 clean。

7、创建主分区，输入create partition primary。

8、选择主分区，输入select partition 1。

9、激活注分区，输入active。

10、格式化U盘，输入format fs=fat32 quick。

11、分配盘符。输入assign。

12、将iso镜像解压到U盘根目录。

13、使用U盘引导机器，激动人心的画面将出现在您面前。



install.wim过大：使用命令将其分割 `Dism /Split-Image /ImageFile:D:\install.wim /SWMFile:D:\install.swm /FileSize:2200`



官网制作u盘系统盘（只能制作最新系统）：https://www.microsoft.com/zh-cn/software-download/windows10



BAD_POOL_CALLER蓝屏故障解决：https://mbd.baidu.com/ma/s/fMhgpa8a

## 电源

选高性能

![image-20201024150744425](http://mdimg.sofice.top/202112111341182.png)

![image-20201024150833794](http://mdimg.sofice.top/202112111341711.png)



## 桌面图标

<img src="http://mdimg.sofice.top/202112111341670.png" alt="image-20201024151035944" style="zoom:67%;" />







# vscode

## 插件

Chinese

python

vscode-icons

Bracket Pair Colorizer 2

tabline

jupyter

latex workshop（需texlive）https://www.cnblogs.com/meiqin970126/p/10984568.html

https://blog.csdn.net/weixin_39892850/article/details/105468247

latex language support



vscode+latex：https://zhuanlan.zhihu.com/p/106167792?utm_source=QQ_article_bottom

# Anaconda

## pip修改国内镜像

windows下，直接在user目录中创建一个pip目录，如：C:\Users\xx\pip，新建文件pip.ini，内容如下

```
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```

## Tensorflow-gpu安装

https://blog.csdn.net/sunmingyang1987/article/details/102872658

| tensorflow_gpu | cuda | cudnn |
| -------------- | ---- | ----- |
| 1.14.0         | 10.0 | 7.4   |
| 2.3.1          | 10.1 | 7.6   |

## Jupyter Notebook

**修改启动目录**

通过配置文件修改启动目录，只适合从命令行启动notebook：

查看你的notebook配置文件在哪里：`jupyter notebook --generate-config`，打开这个配置文件，删除c.NotebookApp.notebook_dir 前面的“#”符号（#表示注释的意思），然后修改为自己创建的目录路径，保存.py文件



**运行conda环境**

```
conda install nb_conda_kernels
```



linux：

```bash
# 切换环境
source activate omni
# 环境变量
echo 'export PATH=/usr/local/cuda-9.0/bin:$PATH'>>~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64:$LD_LIBRARY_PATH'>>~/.bashrc
source ~/.bashrc
# 查看版本号
nvcc -v
# cudnn的软连接
cd /usr/local/cuda-10.1/lib64
sudo chmod +r libcudnn.so.7.6.5
sudo ln -sf libcudnn.so.7.6.5 libcudnn.so.7
sudo ln -sf libcudnn.so.7 libcudnn.so
sudo ldconfig


```



# MySQL

安装配置：https://www.cnblogs.com/winton-nfs/p/11524007.html



# JAVA

IDE安装配置：https://www.aiweibk.com/120661.html

JAVA_HOME：D:\ProgramFiles\Java\jdk-12.0.1

Path：%JAVA_HOME%\bin

多版本JDK切换：https://www.cnblogs.com/ccav1/p/10309217.html

# csgo

steam管理员启动，csgo不要管理员启动

闪退：管理员进入cmd窗口后输入netsh winsock reset，然后重启





# 文件结构设计

```
--Files # 各种文件
--Games # 游戏
--Program # 程序
|--GitRepository # git仓库
--ProgramData # 各种软件的数据，缓存等
--ProgramFiles # 各种软件
```













