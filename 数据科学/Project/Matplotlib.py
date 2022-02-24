import matplotlib
import matplotlib.pyplot as plt
import numpy as np

dataX=np.linspace(-6,6,256)
dataY=np.sin(dataX)
# 总画布，设置point和分辨率
fig = plt.figure(figsize=(15,7), dpi=80)
# axes子图
ax = fig.add_subplot(111)
# 等价于
fig, ax = plt.subplots(1,1,figsize=(15,7), dpi=80)

# 标题
ax.set_title('Title',fontsize=18)
ax.set_xlabel('xlabel', fontsize=18,fontfamily = 'sans-serif',fontstyle='italic')
ax.set_ylabel('ylabel', fontsize='x-large',fontstyle='oblique')
# 显示图例
ax.legend(loc=1)    # loc为axes的象限序号
# 设置坐标
ax.set_aspect('equal')  # 横纵坐标长度相等
ax.minorticks_on()  # 显示副坐标
ax.grid(which='major', axis='both') #显示网格

ax.set_xlim(-7,7)   # 设置坐标范围
start, end = ax.get_xlim()  # 获取坐标范围

ax.xaxis.set_ticks(np.arange(start, end, 1)) # 设置坐标轴数字
ax.xaxis.set_tick_params(rotation=45,labelsize=18,colors='g')   # 设置坐标轴数字格式
ax.xaxis.set_ticks_position('top')   # 设置坐标轴数字位置

ax.yaxis.tick_right()   # 设置在右侧显示y坐标

ax.spines['right'].set_color('none')    # 设置脊柱颜色
ax.spines['bottom'].set_position(('data',0))    # 设置脊柱位置

# 曲线图
ax.plot(dataX, dataY, color="b", linewidth=1.0, linestyle="-")

# 散点图
ax.scatter(dataX, dataY)

#绘制图片
plt.imshow(x_train[0])






plt.show()

# plt.savefig("./exercice_2.png",dpi=72)