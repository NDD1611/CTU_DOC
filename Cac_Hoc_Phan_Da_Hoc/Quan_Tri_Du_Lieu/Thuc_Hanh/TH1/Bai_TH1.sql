create database QLDIEM_QTDL;

use qldiem_qtdl;

create table khoa (
	maKhoa char(8) not null primary key,
    tenKhoa varchar(50) not null
);

create table sinhVien (
	mssv char(8) not null primary key,
    hoTen varchar(50) not null,
    gioiTinh char(1),
    ngaySinh Date,
    noiSinh varchar(40),
    diaChi varchar(100),
    maKhoa char(8)
);

create table ketqua (
	mssv char(10),
    maHp char(10),
    diem float
);

create table hocphan (
	maHP char(10) not null primary key,
    tenHP varChar(40),
    soTC int,
    soTLT int,
    soTTH int
);

insert into hocphan 
value
("CT101", "Lập trình căn bản", 4, 30, 60),
("CT176", "Lập trình hướng đối tượng", 3, 30, 30),
("CT237", "Nguyên lý hệ điều hành", 3, 30, 30),
("TN001", "Vi tích phấn A1", 3, 45, 0),
("TN101", "Xác suất thống kê", 3, 45, 0),
("SP102", "Đại số tuyến tính", 4, 60, 0),
("TN172", "Toán rời rạc", 4, 60, 0),
("XH023", "Anh văn căn bản 1", 4, 60, 0),
("TN021", "Hóa học đại cương", 3, 60, 0);

insert into khoa 
value
("NNG", "Khoa ngoại ngũ"),
("CNTT&TT", "Công nghệ thông tin và Truyền thông"),
("TN", "Khoa khoa học tự nhiên"),
("TS", "Khoa thủy sản"),
("SP", "Khoa sư phạm"),
("NN", "Khoa Nông Nghiệp"),
("KT", "Khoa kinh tế");

insert into sinhvien
values
("B1456790", "Nguyễn Hồng Thắm 2", "F", '2003-05-09', "An Giang", "133, Nguyễn Văn Cừ, Q. Ninh Kiều, TPCT","NNG"),
("B1234567", "Nguyễn Thanh Hải", "M", '2001-12-02', "Bạc Liêu", "Phường 01, KTX B, DHCT","CNTT&TT"),
("B1234568", "Trần Thanh Mai","M", '2001-01-20', "Cần Thơ", "232, Nguyễn Văn Khéo, Quận Ninh Kiều, Cần Thơ","CNTT&TT"),
("B1234569", "Trần Thu Thủy", "F", '2001-07-01', "Cần Thơ", "02, Địa lộ Hòa Bình, Q. Ninh Kiều, TPCT","CNTT&TT"),
("B1334569", "Nguyễn Thị Trúc Mã", "F", '2002-05-25', "Sóc Trăng", "343, Đường 30/4. Q.Ninh Kiều, TPCT","SP"),
("B1345678", "Trần Hồng Trúc", "F", '2002-03-02', "Cần Thơ", "123, Trần Hưng Đạo, Q. Ninh Kiều, TPCT","CNTT&TT"),
("B1345679", "Bùi Hoàng Yến","F", '2001-11-05', "Vĩnh Long", "Phòng 201, KTX A, TPCT", "CNTT&TT"),
("B1345680", "Trần Minh Tâm","M", '2001-02-04', "Cà Mau", "07, Đại lộ Hòa Bình, Q. Ninh Kiều, TPCT","KT"),
("B1456789", "Nguyễn Hồng Thắm", "F", '2003-05-09', "An Giang", "133, Nguyễn Văn Cừ, Q. Ninh Kiều, TPCT","NNG"),
("B1459230", "Lê Văn Khang", "M", '2002-06-02', "Đồng Tháp", "312, Nguyễn Văn Linh, Q.Ninh Kiều, TPCT","NN");

insert into ketqua
value
("B1234567", "CT101", 4),
("B1234568", "CT176", 8),
("B1234569", "CT237", 9),
("B1334569", "SP102", 2),
("B1345678", "CT101", 6),
("B1345679", "CT176", 5),
("B1456789", "TN172", 10),
("B1456790", "TN172", 7),
("B1456789", "XH023", 6),
("B1459230", "XH023", 8),
("B1234567", "CT176", 1),
("B1234568", "CT101", 9),
("B1234569", "CT101", 8),
("B1334569", "CT101", 4),
("B1345678", "TN001", 6),
("B1345678", "CT101", 2),
("B1345679", "CT101", 7),
("B1456789", "CT101", 6),
("B1456790", "TN101", 7),
("B1456790", "XH023", 7);

ALTER TABLE sinhvien
ADD CONSTRAINT FK_sinhvien_khoa
FOREIGN KEY (maKhoa) REFERENCES khoa(maKhoa);

ALTER TABLE ketqua
ADD CONSTRAINT FK_ketqua_hocphan
FOREIGN KEY (maHP) REFERENCES hocphan(maHP);

ALTER TABLE ketqua
ADD CONSTRAINT FK_ketqua_sinhvien
FOREIGN KEY (mssv) REFERENCES sinhvien(mssv);

-- C1_B1
select mssv, hoTen, ngaySinh from sinhvien
order by mssv;

-- C2_B1
select mssv, hoTen from sinhvien sv join khoa k on sv.maKhoa=k.maKhoa
where k.maKhoa = "CNTT&TT";

-- C3_B1 
select sv.mssv, sv.hoTen, kq.diem, hp.tenHp from sinhvien sv join ketqua kq on sv.mssv=kq.mssv
join hocphan hp on kq.maHp=hp.maHp;

-- C4_B1
select mssv, hoTen, ngaySinh from sinhvien
where YEAR(ngaySinh) = '2001' and gioiTinh ="F";

-- C5_B1
select sv.mssv, sv.hoTen, hp.maHp, kq.diem from 
sinhvien sv join ketqua kq on sv.mssv=kq.mssv
join hocphan hp on kq.maHp = hp.maHp;

-- C6_B1
select  * from (select distinct kq.maHp from 
sinhvien sv join ketqua kq on sv.mssv=kq.mssv) as ntb
right join hocphan hp on ntb.maHp=hp.maHp
where ntb.maHp is null;

-- C7_B1
select sv.mssv, sv.hoTen, avg(diem) as avg from 
sinhvien sv join ketqua kq on sv.mssv=kq.mssv
group by sv.mssv;

-- C8_B1
select makhoa, count(mssv) as mssv from sinhvien 
group by makhoa;

-- C9_B1
select makhoa, count(mssv) as sl from sinhvien 
group by makhoa
having sl = (select max(agv) from (select count(mssv) as agv from sinhvien 
					group by makhoa) as tb);

-- C10 _B1
select hp.maHp from 
sinhvien sv join ketqua kq on sv.mssv=kq.mssv
join hocphan hp on kq.maHp=hp.maHp
where hoTen like '%Mai%';

-- C11_B1
update ketqua
set diem = diem + 1
where mssv in (select mssv from sinhvien 
where maKhoa != "CNTT&TT");


use qldiem_qtdl;
select * from hocphan;
select * from ketqua;
select * from khoa;
select * from sinhvien;
create database tgdd;


