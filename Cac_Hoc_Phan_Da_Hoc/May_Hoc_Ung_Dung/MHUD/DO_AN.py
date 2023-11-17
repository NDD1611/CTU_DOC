

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

os.system("cls")
data = pd.read_csv("./telecom_churn.csv")
# print(data)
X = data.iloc[:, 1:11]
y = data.Churn


accuracyKNN = []
accuracyBayes = []
accuracyTree = []
kf = KFold(n_splits=10)

print("KFold")
count = 0
for train_index, test_index in kf.split(data):
    print("Tap du lieu thu:", count+1)
    count += 1
    X_train, X_test = X.iloc[train_index, ], X.iloc[test_index, ]
    y_train, y_test = y.iloc[train_index], y.iloc[test_index]

    Mohinh_KNN = KNeighborsClassifier(n_neighbors=7)
    Mohinh_KNN.fit(X_train, y_train)
    dubao = Mohinh_KNN.predict(X_test)
    thucte = y_test
    accuracy_knn = accuracy_score(thucte, dubao)*100
    accuracyKNN.append(accuracy_knn)
    print("     Accuracy KNN:           ", accuracy_knn)

    model = GaussianNB()
    model.fit(X_train, y_train)
    thucteBayes = y_test
    dubaoBayes = model.predict(X_test)
    accuracy_bayes = accuracy_score(thucteBayes, dubaoBayes)*100
    accuracyBayes.append(accuracy_bayes)
    print("     Accuracy BAYES:         ", accuracy_bayes)

    clf = DecisionTreeClassifier()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    accuracy_tree = accuracy_score(y_pred, y_test)*100
    accuracyTree.append(accuracy_tree)
    print("     Accuracy Decision Tree: ", accuracy_tree)
print("============================================")
tongKNN = 0
tongBayes = 0
tongTree = 0
for i in range(0, 10):
    tongKNN += accuracyKNN[i]
    tongBayes += accuracyBayes[i]
    tongTree += accuracyTree[i]

print("Accuracy trung binh KNN", tongKNN/10)
print("Accuracy trung binh Bayes", tongBayes/10)
print("Accuracy trung binh Tree", tongTree/10)

print("Hold OUT")
accuracyKNN = []
accuracyBayes = []
accuracyTree = []

for i in range(0, 10):
    print("Lan lap thu:", i+1)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=1/3.0, random_state=100)
    Mohinh_KNN = KNeighborsClassifier(n_neighbors=7)
    Mohinh_KNN.fit(X_train, y_train)
    dubao = Mohinh_KNN.predict(X_test)
    thucte = y_test
    accuracy_knn = accuracy_score(thucte, dubao)*100
    accuracyKNN.append(accuracy_knn)
    print("     Accuracy KNN:           ", accuracy_knn)

    model = GaussianNB()
    model.fit(X_train, y_train)
    thucteBayes = y_test
    dubaoBayes = model.predict(X_test)
    accuracy_bayes = accuracy_score(thucteBayes, dubaoBayes)*100
    accuracyBayes.append(accuracy_bayes)
    print("     Accuracy BAYES:         ", accuracy_bayes)

    clf = DecisionTreeClassifier()
    clf = clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    accuracy_tree = accuracy_score(y_pred, y_test)*100
    accuracyTree.append(accuracy_tree)
    print("     Accuracy Decision Tree: ", accuracy_tree)

print("====================================")
tongKNN = 0
tongBayes = 0
tongTree = 0
for i in range(0, 10):
    tongKNN += accuracyKNN[i]
    tongBayes += accuracyBayes[i]
    tongTree += accuracyTree[i]

print("Accuracy trung binh KNN", tongKNN/10)
print("Accuracy trung binh Bayes", tongBayes/10)
print("Accuracy trung binh Tree", tongTree/10)


dataChart = []
for i in range(0, len(accuracyKNN)):
    columns = []
    columns.append(i+1)
    columns.append(accuracyKNN[i])
    columns.append(accuracyBayes[i])
    columns.append(accuracyTree[i])
    dataChart.append(columns)

y = dataChart
df = pd.DataFrame(y, columns=["Lan lap", "KNN", "Bayes", "Decision Tree"])
ax = df.plot(x="Lan lap", y=["KNN", "Bayes",
             "Decision Tree"], kind="bar", rot=0)

plt.show()
