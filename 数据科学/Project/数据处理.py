import os
import numpy as np
import pandas as pd


def autoNorm(dataSet):
    '''
    归一化特征值
    Input:  dataSet: 数据集
            
    Output: normDataSet：归一化后数据集
    '''
    minVals = dataSet.min(0)
    maxVals = dataSet.max(0)
    ranges = maxVals - minVals
    normDataSet = np.zeros(np.shape(dataSet))
    m = dataSet.shape[0]
    normDataSet = dataSet - np.tile(minVals, (m,1))
    normDataSet = normDataSet/np.tile(ranges, (m,1))   
    return normDataSet
