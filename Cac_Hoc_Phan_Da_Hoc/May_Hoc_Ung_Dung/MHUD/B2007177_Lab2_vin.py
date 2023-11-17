
import pandas as pd
import numpy as np

data = pd.read_csv("./Data/winequality-red.csv")
print("So luong phan tu: ",len(data))
print("So luong nhan cua tap du lieu: ", np.unique(data.quality))

#Tap du lieu co 1599, co 6 nhan

print(data)

from sklearn.model_selection import train_test_split

X = data.iloc[:, 0:11]
y = data.quality


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=1/3.0, random_state=5)


from sklearn.neighbors import KNeighborsClassifier
Mohinh_KNN = KNeighborsClassifier(n_neighbors=7)
Mohinh_KNN.fit(X_train, y_train)


#du doan
dubao = Mohinh_KNN.predict(X_test)

thucte = y_test

#print("Thuc te:\n", thucte)
#print("Du bao:\n", dubao)

from sklearn.metrics import accuracy_score
print("Accuracy is ", accuracy_score(thucte, dubao)*100)

from sklearn.metrics import confusion_matrix

matrix = confusion_matrix(thucte, dubao)
print(matrix)

print("BAYES")
from sklearn.naive_bayes import GaussianNB
from sklearn.naive_bayes import MultinomialNB

model = GaussianNB()
model.fit(X_train, y_train)
print(model)

thucte = y_test
dubao = model.predict(X_test)

#print("Thuc te\n",thucte)
#print("Du bao\n", dubao)

cnf_matrix_gnb = confusion_matrix(thucte, dubao)
print(cnf_matrix_gnb)


