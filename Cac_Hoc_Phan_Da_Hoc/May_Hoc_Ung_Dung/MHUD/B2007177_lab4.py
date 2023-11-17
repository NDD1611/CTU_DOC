
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


X = np.array([1,2,4])
Y = np.array([2,3,6])
plt.axis([0,5,0,8])
plt.plot(X,Y, "ro", color="blue")
plt.xlabel("Gia tri thuộc tỉnh X")
plt.ylabel("Gia tri du doan Y")
# plt.show()

def LR1(X, Y, eta, lanlap, theta0, theta1):
    m = len(X)
    for k in range(0,lanlap):
        #print("Lan lap: ", k)
        for i in range(0,m):
            h_i = theta0 + theta1*X[i]
            theta0 = theta0 + eta*(Y[i]-h_i)*1
            #print("Phan tu ", i, "y= ", Y[i], "h=", h_i, "gia tri theta0 = ", round(theta0, 3))
            theta1 = theta1 + eta*(Y[i]-h_i)*X[i]
            #print("Phan tu ", i, "gia tri theta1 = ", round(theta1, 3))
    return [round(theta0,3), round(theta1,3)]

theta = LR1(X, Y, 0.2, 2, 0, 1)
print(theta)
y1 = theta[0]+theta[1]*0
y2 = theta[0]+theta[1]*3
y3 = theta[0]+theta[1]*5
print(y1, y2, y3)

theta = LR1(X,Y,0.1,1,0,1) # theta 1 bước
X1= np.array([1,6])
Y1= theta[0] + theta[1]*X1
theta2 = LR1(X,Y,0.1,2,0,1) # theta 2
# bước lạp
X2= np.array([1,6])
Y2= theta2[0] + theta2[1]*X2
plt.axis([0,7,0,10])
plt.plot(X,Y, "ro", color="blue")
plt.plot(X1, Y1 ,color="violet") # duong hoi quy lan lap 1
# duong hoi quy lan lap 2
plt.plot(X2,Y2, color="green")
plt.xlabel("Gia tri thuoc tinh X")
plt.ylabel("Gia tri du doan Y")
#plt.show()

dt = pd.read_csv("./Data/Housing_2019.csv", index_col=0)
X = dt.iloc[:, [1,2,3,4,10]]
plt.scatter(dt.lotsize, dt.price)
plt.show()
y = dt.price

# huấn luyện mô hình
import sklearn
from sklearn import linear_model
lm = linear_model.LinearRegression()
lm.fit(X[0:520],y[0:520])
print(lm.intercept_)
print(lm.coef_)
# dự báo giá nhà cho 20 phần tử cuối cùng trong tap du lieu
y = dt.price
y_test = y[-20:]
X_test = X[-20:]
y_pred = lm.predict(X_test)
# so sánh giá trị thực tế và giá trị dự báo
y_pred
y_test
from sklearn.metrics import mean_squared_error
err = mean_squared_error(y_test, y_pred)
print(err)
rmse_err = np.sqrt(err)
round (rmse_err,3)

