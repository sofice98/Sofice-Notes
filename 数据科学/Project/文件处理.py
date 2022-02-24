import os
import numpy as np
import pandas as pd
from PIL import Image

def file2matrix(filename):
    '''
    将文本记录转化为NumPy
    Input:  filename: 文件名

    Output: dataSet, labels
    '''
    fr = open(filename)
    numberOfLines = len(fr.readlines())
    returnMat = np.zeros((numberOfLines, 3))
    classLabelVector = []
    fr = open(filename)
    index = 0
    for line in fr.readlines():
        line = line.strip()                             # 截掉前后空格和换行
        listFromLine = line.split('\t')
        returnMat[index, :] = listFromLine[0:3]         # 前几列作为特征
        classLabelVector.append(int(listFromLine[-1]))  # 最后一列数字作为标签
        index += 1
    return returnMat


# 读csv文件
data = pd.read_csv(path)
# 写csv文件
data.to_csv("titanic/out.csv", index = False)
# 读入图片
img = Image.open(img_path)  
img = img.resize((28, 28), Image.ANTIALIAS) # 改变图片尺寸
img = np.array(img.convert('L'))  # 图片变为8位宽灰度值的np.array格式
img = img / 255.  # 数据归一化 （实现预处理）
img_arr = 255 - img_arr # 反色