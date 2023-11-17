
#su dung bo du lieu co san cua thu vien skelarn
from sklearn.datasets import load_iris
iris_dt = load_iris()
iris_dt.data[1:5]
iris_dt.target[1:5]

#phan chia tap du lieu
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(iris_dt.data, iris_dt.target, test_size=1/3.0, random_state=5)

#xay dung mo hinh
from sklearn.neighbors import KNeighborsClassifier
MoHinh_KNN = KNeighborsClassifier(n_neighbors=5)
MoHinh_KNN.fit(X_train, y_train)

#du doan
y_preq = MoHinh_KNN.predict(X_test)
y_test
MoHinh_KNN.predict([[4,4,3,3]])

#du doan do chinh xac
from sklearn.metrics import accuracy_score
print("Accuracy is ", accuracy_score(y_test, y_preq)*100)

#tinh do chinh xac qua ma tran con
from sklearn.metrics import confusion_matrix
print(confusion_matrix(y_test, y_preq, labels=[2,0,1]))

# B giai thuat Bayes tho ngay
import pandas as pd
dulieu = pd.read_csv("./Data/data_iris.csv")
print("du lieu iris csv\n", dulieu.nhan)
X = dulieu.iloc[:, 0:4]
# print("X\n",X)
y = dulieu.nhan
# print("Y\n", y)

#phan chia du lieu thanh tap train, test
from sklearn.naive_bayes import GaussianNB
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

model = GaussianNB()
model.fit(X_train, y_train)
print(model)
thucte = y_test
dubao = model.predict(X_test)
# print(thucte)
# print(dubao)

# print("Accuracy is ", accuracy_score(y_test, thucte)*100)
from sklearn.metrics import confusion_matrix
cnf_matrix_gnb = confusion_matrix(thucte, dubao)
print(cnf_matrix_gnb)
