create table khoahoc (
    makh varchar(10) primary key,
    tenkh nvarchar2(20),
    ngaybd date,
    ngaykt date
);

create table chuongtrinh (
    mact varchar(10) primary key,
    tenct nvarchar2(100)
);

create table loailop (
    maloai varchar(15) primary key,
    mact varchar(10),
    tenloai nvarchar2(100)
);

create table lop (
    malop varchar(10) primary key,
    maloai varchar(10),
    tenlop nvarchar2(100),
    siso int,
    makh varchar(10)
);

create table hocvien (
    mahv varchar(10) primary key,
    tenhv nvarchar2(100),
    gioitinh int,
    ngaysinh date,
    sdt varchar(15),
    diachi nvarchar2(100)
);

create table phieuthu (
    sopt varchar(20) primary key,
    mahv varchar(15),
    malop varchar(10),
    ngaylapphieu date,
    thanhtien int
);

create table monhoc (
    mamh varchar(15) primary key,
    tenmh nvarchar2(100)
);

create table diem (
    mamh varchar(15),
    mahv varchar(15),
    malop varchar(15),
    diem float
);


alter table loailop
add foreign key (mact) references chuongtrinh(mact);

alter table lop
add foreign key (maloai) references loailop(maloai);

alter table lop
add foreign key (makh) references khoahoc(makh);

alter table phieuthu
add foreign key (mahv) references hocvien(mahv);

alter table diem
add foreign key (mamh) references monhoc(mamh);

alter table diem 
add foreign key (mahv) references hocvien(mahv);

alter table diem
add foreign key (malop) references lop(malop);

alter table khoahoc     -- thay doi data type da sua luc tao table k can chay dong nay
modify makh varchar(20)


alter table khoahoc 
add check(ngaykt>ngaybd);

alter table lop 
add check(siso>12);

alter table hocvien
add check(gioitinh=1 or gioitinh=0);

alter table phieuthu
add check(thanhtien>0);

alter table diem
add check(diem>=0 and diem<=10);


-- them du lieu

insert into khoahoc
values ('K001','khóa 1', '01/10/2020','03/20/2020');
insert into khoahoc
values ('K002','khóa 2', '02/28/2020','05/28/2020');
insert into khoahoc
values ('K003','khóa 3', '04/10/2020','07/20/2020');
insert into khoahoc
values ('K004','khóa 4', '06/15/2020','09/20/2020');
        
insert into chuongtrinh
values ('CT007','Chứng Chỉ Tiếng Anh 6 Bậc (A1, B1, B2, C1');
insert into chuongtrinh
values ('CT006','Chương Trình CamBridge');
insert into chuongtrinh
values ('CT005','Tiếng Anh IELTS');
insert into chuongtrinh
values ('CT004','Chương Trình TOEIC');
insert into chuongtrinh
values ('CT003','Tiếng Anh Luyện Kĩ Năng');
insert into chuongtrinh
values ('CT002','Tiếng Anh trẻ Em');
insert into chuongtrinh
values ('CT001','Tiếng Anh Tổng Quát');

insert into loailop
values ('LL001','CT001','Tiếng Anh Căn Bản');
insert into loailop
values ('LL002','CT001','Tiếng Anh A1');
insert into loailop
values ('LL003','CT001','Tiếng Anh A2');
insert into loailop
values ('LL004','CT001','Tiếng Anh B1');
insert into loailop
values ('LL005','CT001','Tiếng Anh B2');
insert into loailop
values ('LL006','CT001','Tiếng Anh C1');

insert into lop
values ('L001','LL001','Lớp 1',30,'K001');
insert into lop
values ('L002','LL001','Lớp 2',30,'K001');
insert into lop
values ('L003','LL002','Lớp 1',30,'K001');

insert into hocvien
values ('HV0001','Đỗ Bình An', 1, '11/02/2000', '917217036','Cờ Đỏ - Cần Thơ');
insert into hocvien
values ('HV0002','Đỗ Gia Bảo', 1, '12/02/2000', '917217036','Ô Môn - Cần Thơ');
insert into hocvien
values ('HV0003','Đỗ Phúc Vinh', 1, '11/02/2000', '917217036','Cù Lao Dung - Sóc Trăng');
insert into hocvien
values ('HV0004','Thạch Chí tâm', 1, '01/02/2000', '917217036','Châu Thành - An Giang');
insert into hocvien
values ('HV0005','Lê Cẩm Giao', 0, '11/05/2000', '917217036','Phong Điền - Cần Thơ');
insert into hocvien
values ('HV0006','Huỳnh Gia Bảo', 1, '11/02/2000', '917217036','Phong Điền - Cần Thơ');

insert into phieuthu
values ('PT000002','HV0002','L001','01/06/2021', 1350000);
insert into phieuthu
values ('PT000003','HV0003','L001','01/06/2021', 1350000);
insert into phieuthu
values ('PT000004','HV0004','L001','01/06/2021', 1350000);
insert into phieuthu
values ('PT000005','HV0005','L001','01/06/2021', 1350000);
insert into phieuthu
values ('PT000006','HV0006','L001','01/06/2021', 1350000);
insert into phieuthu
values ('PT000007','HV0007','L001','01/06/2021', 1350000);