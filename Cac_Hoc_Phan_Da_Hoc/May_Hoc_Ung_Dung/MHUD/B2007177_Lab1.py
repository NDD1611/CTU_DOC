
#vidu 1
a=5
b=3
if a>b:
    a=a*2+3
    b=b-6
    c=a/b
    print(c)
#vidu 2
c=a+b+\
    10*a-b/4-\
    5+a*3
print(c)

#vidu 3
if a>b:
    print("True")
    print(a)
else:
    print("False")
    print(b)

#vidu 4
a=1
b=10
while a<b:
    a += 1
    print(a)

#vidu 5
for i in range(1, 10):
    print(i)

#vidu 6
def binhphuong(number):
    return number*number
print(binhphuong(5))

#vidu  7
a = 5
b = -7
c = 1.234

#vidu 8
str1 = "Hello"
str2 = "welcome"
str3 = "ahjakfa"
#vidu 9
cats = ['Tom', 'Snappy', 'Kitty', 'Jessie', 'Chester']
print(cats[2])
print(cats[-1])
print(cats[1:3])
print(cats)
cats.append('Jerry')
print(cats)
del cats[1]
print(cats)

#vidu 10
dict1 = {'Name':'Zyra', 'Age':'7', 'Class':'A5'}
print(dict1['Name'])
dict1['School'] = "DFS School"
print(dict1['Age'])
print(dict1['School'])

#vidu 11
import numpy as np
a=np.array([0,1,2,3,4,5])
print(a)
print(a.ndim)
print(a.shape)
print(a[a>3])

b=a.reshape((3,2))
print(b)
print(b[2][1])
b[2][0]=50
c=b*2
print(c)

import pandas as pd
print("data play tennis")
dt = pd.read_csv("./Data/play_tenniss.csv", delimiter=',')
print(dt)
print("head\n",dt.head())
print("tail\n",dt.tail(7))

print("loc[3:8]\n",dt.loc[3:8])
print("iloc[:, 3:6]\n",dt.iloc[:, 3:6])
print("iloc[5:10, 3:4]\n",dt.iloc[5:10, 3:4])
print("outlock\n",dt.Outlook)