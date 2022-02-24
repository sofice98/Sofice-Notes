'''
ID3方法划分数据集生成决策树
'''
from math import log
import operator

def createDataSet():
    dataSet = [[1, 1, 'yes'],
               [1, 1, 'yes'],
               [1, 0, 'no'],
               [0, 1, 'no'],
               [0, 1, 'no']]
    labels = ['no surfacing','flippers']
    #change to discrete values
    return dataSet, labels

def calcShannonEnt(dataSet):
    '''
    计算给定数据集的熵
    Input:dataSet:数据集
    
    Output:shannonEnt:数据熵
    '''
    numEntries = len(dataSet)
    labelCounts = {}
    for featVec in dataSet: #the the number of unique elements and their occurance
        currentLabel = featVec[-1]
        if currentLabel not in labelCounts.keys(): labelCounts[currentLabel] = 0
        labelCounts[currentLabel] += 1
    shannonEnt = 0.0
    for key in labelCounts:
        prob = float(labelCounts[key])/numEntries
        shannonEnt -= prob * log(prob,2) #log base 2
    return shannonEnt
    
def splitDataSet(dataSet, axis, value):
    '''
    按给定特征划分数据集
    Input:dataSet:待划分数据集
          axis   :特征序号
          value  :特征值
    
    Output:retDataSet:划分后数据集
    '''
    retDataSet = []
    for featVec in dataSet:
        if featVec[axis] == value:
            #reducedFeatVec = featVec[:axis]     #chop out axis used for splitting
            #reducedFeatVec.extend(featVec[axis+1:])
            retDataSet.append(featVec)
    return retDataSet
    
def chooseBestFeatureToSplit(dataSet):
    '''
    选取最好的数据集划分方式
    Input:dataSet:待划分数据集
    
    Output:bestFeature:最好的划分数据集的特征序号
    '''
    numFeatures = len(dataSet[0]) - 1      #the last column is used for the labels
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0.0; bestFeature = -1
    for i in range(numFeatures):         #考虑所有特征
        featList = [example[i] for example in dataSet]#create a list of all the examples of this feature
        uniqueVals = set(featList)       #get a set of unique values
        newEntropy = 0.0                 # 计算条件熵
        for value in uniqueVals:
            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet)/float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)     
        infoGain = baseEntropy - newEntropy     #计算信息增益
        if (infoGain > bestInfoGain):       #取信息增益最大的特征
            bestInfoGain = infoGain         
            bestFeature = i
    return bestFeature                      #returns an integer

def majorityCnt(classList):
    classCount={}
    for vote in classList:
        if vote not in classCount.keys(): classCount[vote] = 0
        classCount[vote] += 1
    sortedClassCount = sorted(classCount.items(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]

def createTree(dataSet,labels):
    '''
    生成决策树
    Input:dataSet:数据集
          labels :标签集
    
    Output:myTree:决策树
    '''
    classList = [example[-1] for example in dataSet]
    if classList.count(classList[0]) == len(classList): #类别相同，停止划分
        return classList[0]
    if len(dataSet[0]) == 1: #数据单一，停止划分
        return majorityCnt(classList)
    bestFeat = chooseBestFeatureToSplit(dataSet)
    bestFeatLabel = labels[bestFeat]
    myTree = {bestFeatLabel:{}}
    del(labels[bestFeat])
    featValues = [example[bestFeat] for example in dataSet]
    uniqueVals = set(featValues)
    for value in uniqueVals:
        subLabels = labels[:]       #copy all of labels, so trees don't mess up existing labels
        myTree[bestFeatLabel][value] = createTree(splitDataSet(dataSet, bestFeat, value),subLabels)
    return myTree                            
    
def classify(inputTree,featLabels,testVec):
    firstStr = inputTree.keys()[0]
    secondDict = inputTree[firstStr]
    featIndex = featLabels.index(firstStr)
    key = testVec[featIndex]
    valueOfFeat = secondDict[key]
    if isinstance(valueOfFeat, dict): 
        classLabel = classify(valueOfFeat, featLabels, testVec)
    else: classLabel = valueOfFeat
    return classLabel

def storeTree(inputTree,filename):
    import pickle
    fw = open(filename,'w')
    pickle.dump(inputTree,fw)
    fw.close()
    
def grabTree(filename):
    import pickle
    fr = open(filename)
    return pickle.load(fr)
    
