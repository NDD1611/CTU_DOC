--22
select ten_ctr, diachi_ctr
from cgtrinh c join thamgia t on c.stt_ctr=t.stt_ctr
where hoten_cn='nguyen hong van' 
   and 'dec-18-1994' between ngay_tgia and ngay_tgia+so_ngay;
-- 23
select hoten_kts
from cgtrinh c join thietke t on c.stt_ctr=t.stt_ctr
where ten_thau='phong dich vu so xd'
INTERSECT
select hoten_kts
from cgtrinh c join thietke t on c.stt_ctr=t.stt_ctr
where ten_thau='cty xd so 6';

select hoten_kts
from cgtrinh c join thietke t on c.stt_ctr=t.stt_ctr
where ten_thau='phong dich vu so xd'
 and hoten_kts IN (select hoten_kts
                from cgtrinh c join thietke t on c.stt_ctr=t.stt_ctr
                where ten_thau='cty xd so 6');
--24
select hoten_cn
from cgtrinh c join thamgia t on c.stt_ctr=t.stt_ctr
where tinh_thanh='can tho'
MINUS
select hoten_cn
from cgtrinh c join thamgia t on c.stt_ctr=t.stt_ctr
where tinh_thanh='vinh long';

select hoten_cn
from cgtrinh c join thamgia t on c.stt_ctr=t.stt_ctr
where tinh_thanh='can tho'
and hoten_cn NOT IN (select hoten_cn
          from cgtrinh c join thamgia t on c.stt_ctr=t.stt_ctr
          where tinh_thanh='vinh long');
--25
 select ten_thau
 from cgtrinh
 where kinh_phi > ALL
        (select kinh_phi 
        from cgtrinh
        where ten_thau='phong dich vu so xd');
  select ten_thau
 from cgtrinh
 where kinh_phi > 
        (select max(kinh_phi) 
        from cgtrinh
        where ten_thau='phong dich vu so xd');  
-- 26
-- 27
select hoten_cn, sum(so_ngay)
from thamgia
group by hoten_cn having sum(so_ngay) >
        (select sum(so_ngay)
        from thamgia
        where hoten_cn='nguyen hong van' )
-- 28
select hoten_cn, count(distinct stt_ctr)
from thamgia
group by hoten_cn having count(*)=
        (select count(*)from cgtrinh);
-- 29
select c1.ten_thau, c2.ten_thau
from cgtrinh c1 join cgtrinh c2 on c1.tinh_thanh=c2.tinh_thanh
where  c1.ten_thau< c2.ten_thau
-- group by c1.ten_thau, c2.ten_thau having count(*)>1

-- 30
--20
select t.stt_ctr, ten_ctr,count(*)socn
from cgtrinh c join thamgia t on c.stt_ctr=t.stt_ctr
group by t.stt_ctr, ten_ctr having count(*) =
    (select max(count(*)) from thamgia group by stt_ctr )
        
        