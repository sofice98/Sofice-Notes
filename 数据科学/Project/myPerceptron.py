import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os
from sklearn.linear_model import Perceptron
from sklearn.datasets import make_blobs

class myPerceptron():
    def __init__(self, step=1):
        self.w = 0
        self.b = 0
        self.a = 0
        self.step = step

    def fit(self, features, labels):
        N = len(labels)
        self.a = np.zeros(N)
        # 计算Gram矩阵
        gram = np.array([np.dot(x1,x2) for x1 in features for x2 in features]).reshape(N,N)
        # 判断有无误分条件，有则迭代
        isFind = False
        while isFind == False:
            for i in range(N):
                if self.cal(i, labels, gram, N) <= 0:
                    self.a[i] += self.step
                    self.b += self.step * labels[i]
                    break
                elif i == N - 1:
                    isFind = True
        # 得到参数估计值
        for i in range(N):
            self.w += self.a[i] * labels[i] * np.array(features[i])
  
    def cal(self, row, labels, gram, N):
        result = 0
        for i in range(N):
            result += labels[i] * self.a[i] * gram[row][i]
        result += self.b
        result *= labels[row]
        return result

    def predict(self, features):
        pass

def visualize(X, y, model):
    fig, ax = plt.subplots()
    map_color = {-1: 'r', 1: 'g'}
    color = list(map(lambda x: map_color[x], y))
    ax.scatter(X[:,0], X[:,1], c=color)
    m = np.linspace(-10, 10, 2)
    n = (model.w[0] * m + model.b) / -model.w[1]
    ax.plot(m, n, c='orange')
    plt.show()

if __name__ == "__main__":
    X, y = make_blobs(n_samples=100, centers=2, n_features=2)
    y = [-1 if i == 0 else 1 for i in y]
    model = myPerceptron()
    model.fit(X, y)
    visualize(X, y, model)

