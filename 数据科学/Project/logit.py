import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os
from sklearn.linear_model import LogisticRegression
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
from sklearn.metrics import roc_curve, auc, accuracy_score

  

if __name__ == "__main__":
    X, y = make_blobs(n_samples=200, centers=2, n_features=2, cluster_std=2.0, random_state=2000)
    X1,X2,y1,y2 = train_test_split(X, y, random_state=0, test_size=0.5)
    model = LogisticRegression()
    model.fit(X1, y1)
    y2_model = model.predict(X2)
    print(accuracy_score(y2, y2_model))
    print(model.score(X1,y1))

    fig = plt.figure()
    ax1 = fig.add_subplot(1, 2, 1)
    ax2 = fig.add_subplot(1, 2, 2)

    map_color_train = {0: 'r', 1: 'g'}
    color_train = list(map(lambda X1: map_color_train[X1], y1))
    map_color_test = {0: 'r', 1: 'g'}
    color_test = list(map(lambda X2: map_color_test[X2], y2))
    ax1.scatter(X1[:,0], X1[:,1], c=color_train, marker='.')
    ax1.scatter(X2[:,0], X2[:,1], c=color_test, marker='*')
    m = np.linspace(-10, 10, 2)
    n = (model.coef_[0][0] * m + model.intercept_) / -model.coef_[0][1]
    ax1.plot(m, n, c='orange')

    fpr, tpr, _ = roc_curve(y2, y2_model)
    _auc = auc(fpr, tpr)
    ax2.plot(fpr, tpr, "k", label="%s = %0.2f" % ("AUC", _auc))
    ax2.fill_between(fpr, tpr, color="grey", alpha=0.6)
    legend = ax2.legend(shadow=True)
    plt.show()


