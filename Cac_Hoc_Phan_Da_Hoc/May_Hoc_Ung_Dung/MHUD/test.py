
from sklearn.model_selection import KFold
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import MultinomialNB
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

data = [
    [128, 1, 1, 2.7, 1, 265.1, 110, 89, 9.87, 10],
    [107, 1, 1, 3.7, 1, 161.6, 123, 82, 9.78, 13.7],
    [137, 1, 0, 0, 0, 243.4, 114, 52, 6.06, 12.2],
    [84, 0, 0, 0, 2, 299.4, 71, 57, 3.1, 6.6],
    [81, 1, 0, 0.11, 1, 175.5, 67, 53.1, 12.47, 10.2],
    [141, 1, 0, 0, 1, 126.9, 98, 37, 9, 8],
    [87, 0, 0, 0, 5, 151, 83, 45, 10.99, 9.7],
    [121, 1, 1, 1.57, 3, 198.4, 129, 56.7, 3.77, 5.8],
    [82, 1, 0, 0.21, 0, 300.3, 109, 69.1, 9.05, 11.7],
    [144, 0, 0, 0.21, 4, 61.6, 117, 20.1, 3.86, 8.2]
]

test = [0,
        0,
        0,
        0,
        0,
        0,
        1,
        1,
        1,
        1
        ]

xtest = [[116, 0, 0, 0.3, 3, 215.4, 104, 58, 10.24, 12.6]]
Mohinh_KNN = KNeighborsClassifier(n_neighbors=7)
Mohinh_KNN.fit(data, test)
dubao = Mohinh_KNN.predict(data)
print(dubao)
# accuracy_knn = accuracy_score(thucte, dubao)*100
# print("     Accuracy KNN:           ", accuracy_knn)
