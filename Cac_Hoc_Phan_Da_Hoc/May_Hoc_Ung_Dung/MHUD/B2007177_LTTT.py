

print("Cau 1")
print("nhap ten:")
x = input()
print("Hello " + x + " Welcome to python")

print("Cau 2")
print("Nhap so: ")
x = input()
x= int(x)
tong = 0
for i in range(0,4):
    number = x
    for j in range(0, i):
        number = (number * 10) + x
    tong += number
print(tong)

print("Cau 3")
print("Nhap so a:")
a = int(input())
while True:
    print("Nhap so b:")
    b = int(input())
    if b == 0:
        print("vui long nhap so khac 0:")
        continue
    print("a + b: ", a+b)
    print("a - b: ", a-b)
    print("a / b: ", a/b)
    print("a * b: ", a*b)
    print("a % b: ", a%b)
    print("a ** b: ", a**b)
    break


print("Cau 4")
print("nhap vao ban kinh hinh tron:")
a= int(input())
cv = 2*3.14*a
dt = 3.14*a*a
print("chu vi la:", cv ,"\ndien tich la: ", dt)

print("Cau 5")
while True:
    print("Nhap vao mot so nguyen:")
    a = int(input())
    if a < 0:
        print("a phai lon hon 0. vui long nhap lai")
        continue
    b=a
    for i in range(1, a):
        b *= i
    print("Giai thua cua ", a , " la: ", b)
    break

print("Cau 7 Cac so chia het cho 7 nhung khong chia het cho 5")
for i in range(5000, 7001):
    if i%7 == 0 and i % 5 != 0:
        print(i)


print("Cau 8")
print("Nhap vao so thap phan:")
a=int(input())
print(bin(a)[2:])


