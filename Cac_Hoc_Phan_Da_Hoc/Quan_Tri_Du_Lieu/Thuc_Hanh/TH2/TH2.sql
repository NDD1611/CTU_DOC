
-- Cau 1 
DELIMITER $$
DROP PROCEDURE IF EXISTS them_sv $$
CREATE PROCEDURE them_sv (mssv char(8), hoten varchar(50), gt char(1), ngaysinh date, noisinh varchar(40), diachi varchar(100), makhoa char(8))
	BEGIN
        insert into sinhvien
        values (mssv, hoten, gt, ngaysinh, noisinh,diachi, makhoa);
	END;
DELIMITER;

call them_sv('B2007177', 'Nguyen Dinh Dinh', 'M', '2000-01-01', 'Tra Vinh', 'Can Tho', 'CNTT&TT');
select * from sinhvien;
-- Cau 2 
DELIMITER $$
DROP PROCEDURE IF EXISTS xoa_sv $$
CREATE PROCEDURE xoa_sv (mssv1 char(8))
	BEGIN
		delete from sinhvien
        where mssv = mssv1;
	END;
DELIMITER;

call xoa_sv('B2007177');
select * from sinhvien;
-- Cau 3
DELIMITER $$
DROP PROCEDURE IF EXISTS diemTb $$
CREATE PROCEDURE diemTb (mssv1 char(8))
	BEGIN
		select sv.mssv, sv.hoTen, avg(diem) as avg from 
		sinhvien sv join ketqua kq on sv.mssv=kq.mssv
		group by sv.mssv
        having sv.mssv = mssv1;
	END;
DELIMITER;
 call diemTb('B1234567');

-- Cau 4
DELIMITER $$
DROP PROCEDURE IF EXISTS Bang_Diem_Tb $$
CREATE PROCEDURE Bang_Diem_Tb (mk char(8))
	BEGIN
		select sv.mssv, sv.maKhoa, avg(kq.diem) from sinhvien sv join khoa k on sv.maKhoa = k.maKhoa
				join ketqua kq on sv.mssv = kq.mssv
		group by sv.mssv
		having sv.maKhoa = mk;
	END;
DELIMITER; 
call Bang_Diem_Tb('CNTT&TT')

-- Cau 5
DROP FUNCTION IF EXISTS tognDiemNhanTicchi;
DELIMITER $$
create function tognDiemNhanTicchi(msv varchar(10))
returns float DETERMINISTIC 
begin
	return (select sum(kq.diem * hp.soTC)
    from ketqua kq join hocphan hp on kq.maHp = hp.maHp
	where kq.mssv = msv);
end
$$

DROP FUNCTION IF EXISTS tongTinChi;
DELIMITER $$
create function tongTinChi(msv varchar(10))
returns float DETERMINISTIC 
begin
	return (select sum(hp.soTC)
    from ketqua kq join hocphan hp on kq.maHp = hp.maHp
	where kq.mssv = msv);
end
$$

DROP FUNCTION IF EXISTS totNghiep;
DELIMITER $$
create function totNghiep(msv varchar(10))
returns varchar(20) DETERMINISTIC 
begin 
    declare dTb float;
    set dTb =  Diem_Trung_Binh(msv);
    if dTb < 5 then 
		return 'KHONG TOT NGHIEP';
	else 
		return 'TOT NGIEP';
	end if;
end
$$
select totNghiep('B1234567');

-- Cau 6 
DROP FUNCTION IF EXISTS Diem_Trung_Binh;
DELIMITER $$
create function Diem_Trung_Binh(msv varchar(10))
returns float DETERMINISTIC
begin
	declare tongTc float;
    declare tongDiem float;
    declare dTb float;
    set tongTc = tongTinChi(msv);
    set tongDiem = tognDiemNhanTicchi(msv);
    set dTb = tongDiem/tongTc;
    return dTb;
end
$$


DROP FUNCTION IF EXISTS Loai_Tot_Nghiep;
DELIMITER $$
create function Loai_Tot_Nghiep(msv varchar(10))
returns varchar(10) DETERMINISTIC
begin
    declare dTb float;
    set dTb = Diem_Trung_Binh(msv);
    if dTb >= 2.5 & dTb < 3.2 then
		return 'Kha';
	elseif dTb >= 3.2 & dTb < 3.6 then
		return 'Gioi';
	elseif dTb >= 3.6 then
		return 'Xuat Sac';
	end if;
end
$$
select Loai_Tot_Nghiep('B1234567');


select * from sinhvien;
select * from ketqua;
select * from hocphan;
select * from khoa;
