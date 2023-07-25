

create or replace FUNCTION update_quantity()
returns TRIGGER as 
$$
declare new_quantity integer;
BEGIN
    select into new_quantity new.quantity from orderlines
    where orderlineid = new.orderlineid
    and order = new.order;
    update inventory set sales = sales + new_quantity
    where orderlineid = new.orderlineid
    and order = new.order;
    return new;
END;
$$
LANGUAGE plpgsql;


create or replace TRIGGER update_quantities
after insert on orderlines 
for each row 
EXECUTE PROCEDURE update_quantity(); 


---- Cau 1 :
select * from orders where extract (MONTH from orderdate ) = '6' and EXTRACT (year from orderdate )= '2004'

create index_key on orders (orderdate);


-- Cau 2 :
create or replace procedure update_product (product_id char(10))
language plpgsql;
as $$
begin 
    update inventory set sales = sales + 1
    where order_id = product_id;
end;
$$
call update_product ('SP01');


-- Bai 1 :
create table khachsan (
    maks char(10),
    tenks char(100),
    diachi char(100),
    PRIMARY key (maks)
);

create table phong (
    sop char(10),
    maks char(10),
    loaip char(20),
    gia money,
    PRIMARY KEY (sop,maks),
    FOREIGN KEY (maks) REFERENCES khachsan(maks)
);

create table datphong (
    maks char(10),
    makhach char(10),
    ngaynhan date,
    ngaytra date,
    sop char(10),
    PRIMARY KEY (maks, makhach, ngaynhan),
    FOREIGN KEY (maks) REFERENCES khachsan(maks),
    FOREIGN KEY (sop) REFERENCES phong(sop)
);

create table khach (
    makhach char(10),
    hoten char(100),
    diachi char(10),
    PRIMARY KEY (makhach)
    FOREIGN KEY (makhach) REFERENCES datphong(makhach)
);


-- a : Dua ra gia va loai phong
select gia , loaip from phong where maks in 
(select maks from khachsan where tenks = 'Media');
---b : Liet ke tat ca cac khach dang o khach san Media
select * from khach where makhach in 
(select makhach from datphong where ngaytra is null or 
ngaytra >= NOW() AND
maks in (select maks form khachsan where tenks ='Media'));
--- c: Liet ke tat ca cac phong & khach dang o phong do Media

select phong , hoten, diachi from phong join datphong 
using (maks) join khach using (makhach) where 
ngaytra is null or ngaytra >= NOW() and maks in 
(select maks from khachsan where tenks = 'Media');

-- d: Liet ke cac phong k co nguoi o cua khach san
select phong from phong join datphong 
using (maks) join khach using (makhach) where 
ngaytra <= NOW() and maks in 
(select maks from khachsan where tenks = 'Media');


--e : Hay cho biet tong so phong cua khach san o London

select maks, count(*) from khachsan join phong using (maks)
where diachi = 'London' GROUP BY (maks);

-- f : tang don gia tat ca cac phong don len 5 %;

update phong set gia = gia * 1.05 where loaip = 'don';




-------Bai 2 :
create table khachhang (
    makh char(10),
    hoten char(50),
    sodienthoai char(10),
    coquan char(100),
    PRIMARY KEY (makh)
);

create table nhachothue (
    man char(10),
    diachi char(10),
    giathue money,
    tenchunha char(10),
    PRIMARY KEY (man)
);
create table hopdong (
    man char(10),
    makh char(10),
    ngaybatdau date,
    ngayketthuc date,
    PRIMARY KEY (man,makh),
    FOREIGN KEY (man) REFERENCES nhachothue(man),
    FOREIGN KEY (makh) REFERENCES khachhang(makh)
);

---a : Dua ra danh sach (dia chi, ten chu nha ) ngoi nha < 10tr
select diachi, tenchunha from nhachothue where 
giathue  < 10.000.000;
--b : dua ra ds (makh, hoten , coquan) cua nhung nguoi tung thue nha cua Nong Van Den
select * from khachhang where makh in 
(select makh from hopdong where man IN
(select man from nhachothue where tenchunha = 'Nong Van Den'));
---c : dua ra ds ngoi nha chua tung duoc ai thue 
select * from nhachothue where man not in 
(select man from hopdong);
--d : dua ra gia thue cao nhat cua cac ngoi nha tung it nhat 1 lan duoc thue
select max(giathue) from nhachothue where man IN
(select man from hopdong);

----------Bai 3 :
create table giangvien (
    gv_id char(10),
    hoten char(50),
    diachi char(30),
    ngaysinh date,
    PRIMARY KEY (gv_id)
);
create table detai (
    dt_id char(10),
    tendt char(10),
    cap char(10),
    kinhphi money,
    PRIMARY KEY (dt_id)
);
create table thamgia (
    dt_id char(10),
    gv_id char(10),
    sogio int,
    PRIMARY KEY (dt_id, gv_id),
    FOREIGN KEY (dt_id) references detai(dt_id),
    FOREIGN KEY (gv_id) references giangvien(gv_id)
);

--a : dua ra giam dan ho ten gv o Hai Ba Trung
select * from giangvien where diachi like '%Hai Ba Trung%'
order by (hoten) desc;

--b : Dua ra * tu giang vien tham gia de tai Tinh toan luoi
select * from giangvien where gv_id in 
(select gv_id from thamhgia where dt_id in
(select dt_id from detai where tendt = 'Tinh toan luoi'));

--c : dua ra * tu giang vien tham gia de tai phan loai van ban hoac Dich tu dong Anh viet
select * from giangvien where gv_id in 
(select gv_id from thamhgia where dt_id in
(select dt_id from detai where tendt in ('Phan loai van ban','Dich tu dong Anh Viet')));

--d : Cho biet thong tin giang vien tham gia it nhat 2 de tai
select gv_id , count(*) as tong_dt from giangvien join 
thamgia using (gv_id) GROUP BY (gv_id) having count(*) >=2;

-- e: De tai nao ton kinh phi nhat
select * from detai where kinhphi >= ALL(select kinhphi from detai );

--f : Gv sonG Tay Ho va de tai tham gia
select * from giangvien join thamgia using (gv_id) join detai using (dt_id)
where diachi like '%Tay Ho%';

--g : gv sinh truoc nam 1980 va co de tai Phan loai van ban
select * from giangvien where extract (year from ngaysinh) <1980
and gv_id in (select gv_id from thamgia where dt_id in
(select dt_id from detai where tendt = 'Phan loai van ban'));

--h : dua ra magv, ten va tong so gio nghien cuu
select gv_id, hoten , sum(sogio) from giangvien join thamgia using (gv_id)
GROUP BY (gv_id, hoten);

--i : Them thong tin
insert into giangvien values ('GV06','Ngo Tuan Phong','Dong Da, Ha Noi','08-09-1986');

--K : Cap nhap 
update giangvien set diachi = 'Tay Ho, Ha Noi'
where hoten = 'Vu Tuyet Trinh';

-- m : xoa giang vien 

delete from thamgia where gv_id = 'GV02';
DELETE from giangvien where gv_id = 'GV02';

-- Backup and restore Csdl 

-- Cap quyeen,....


---- BAI 4
create table employess (
    eid char(10) PRIMARY KEY,
    ename char(10),
    age int,
    salary int 
);
create table departments (
    did char(10) PRIMARY KEY,
    dname char(10),
    budget integer,
    manage int
);

create table worksin (
    eid char(10),
    did char(10),
    pct_time real,
    check (pct_time >0 && pct_time <1),
    PRIMARY KEY (eid,did),
    FOREIGN KEY eid references employess(eid),
    FOREIGN key did REFERENCES departments(did)
);

--a : Danh sach nhan vien co luong <=3600
select * from empployees where salary <= 3600;

--b : danh sach ten tuoi luong cua nhan vien <30 tuoi
select * from empployees where age < 30;

--c : dua ra danh sach nhan vien va phan bo thoi gian lam viec tai cac phong ban
select eid, ename , pct_time from employees join worksin 
using (eid);

--d : nhan vien luong >=40000, ma , ten , tuoi, luong
select * from employees where salary >=40000;

-- e: dua ra danh sach nhan vien hoan toan lam viec o phong ban khac
select * from employees where eid not in 
(select eid from worksin);

--f : dua ra danh sach phong ban va so tien phai tra 
select did, dname , count(pct_time * 3500) from departments 
join worksin using (did) group by (did,dname);


---- Bai 5:
create table hanghoa (
    mahh char(10) PRIMARY KEY,
    tenhh char(100),
    dongia money
);

create table nhanvien (
    manv char(10) PRIMARY KEY,
    tennv char(100),
    namsinh integer,
    quequan char(100)
);

create table hoadon (
    mahd char(10) PRIMARY KEY,
    ngaylap date,
    manv char(10),
    FOREIGN KEY (manv) REFERENCES nhanvien (manv) 
);

create chitiethoadon (
    mahd char(10),
    mahh char(10),
    soluong integer,
    PRIMARY key (mahd, mahh),
    FOREIGN KEY mahd references hoadon (mahd),
    FOREIGN key mahh references hanghoa (mahh)
);

--1: Co bao nhien nhan vien que o Nam Dinh
select count(*) from nhanvien where quequan = 'Nam Dinh';

--2: Hang hoa co don gia cao nhat ten gi 
select * from hanghoa where dongia >= ALL (select dongia from hanghoa);

--3: So luong hang 3292 ban ngay 10/12/2015
select soluong from chitiethoadon where mahh = '3292'
and mahd in (select mahd from hoadon where ngaylap = '10-12-2015');

--4 : Cho biet thong tin gom hang hoa, ten hang hoa, doanh so trong nam 2014
select mahh, tenhh , count(soluong * dongia) as doanhso
from hanghoa join chitiethoadon using (mahh)
where mahd in (select mahd from hoadon where extract (year from ngaylap) = 2014)
group by (mahh, tenhh);

-- 5: dua ra nhan vien chua phu trach 1 hoa don nao
select * from nhanvien where manv not in
(select manv from hoadon);

--6 : Hoang hoa co ma 3290 tang gia 10%. Hay cap nhap thong tin
update hanghoa set dongia = dongia *1.1
where mahh = '3290';


---- Bai 6 :
create table benhnhan (
    msbn char(10) PRIMARY KEY,
    tenbn char(100),
    gioitinh char(10),
    diachi char(50)
);

create table bacsy (
    idbacsy char(10) PRIMARY KEY,
    ten char(20),
    makhoa char(100)
);

create table dieutri (
    msbn char(10),
    ngaynhapvien date,
    idbacsy char(10),
    tenbeng char(10),
    PRIMARY KEY (msbn, ngaynhapvien),
    FOREIGN KEY idbacsy REFERENCES bacsy (idbacsy)
);


-- b : cac benh nhan nhap vien thang 8 nam 2016
select * from benhnhan where msbn in 
(select msbn from dieutri where extract (month from ngaynhapvien) = 8
and extract (year from ngaynhapvien) = 2016);

--c : dua ra benh nhan kham boi bac si Cat Tuong
select * from benhnhan where msbn in 
(select msbn from dieutri where idbacsy in
(select idbacsy from bacsy where ten = 'cat Tuong'));

--d : thong ke bac si, so luong benh nhan kham t8/2016 giam dan
select idbacsy , ten, count(*) from bacsy join dieutri using (idbacsy)
where extract (year from ngaynhapvien) = 8 and EXTRACT (month from ngaynhapvien) = 2016
group by (idbacsy, ten) order by (count(*)) desc;

--e : dua ra benh nhan vua mac benh Da lieu vua mac benh Tim mach
select * from benhnhan where msbn in 
(select msbn from dieutri where tenbenh = 'Da lieu'
INTERSECT select msbn from dieutri where tenbenh = 'Tim mach');

--f : dua ra ten benh nhan kham nhieu bac si nhat
select tenbn from benhnhan join dieutri 
GROUP BY (tenbn) order by (count(*)) limit 1;

--g : dua ra bac si k kham benh nhan nao mac benh Da lieu
select * from bacsy where idbacsy not in
(select idbacsy from dieutri where tenbenh = 'Da lieu');

--h : dua ra khu vuc theo dia chi co nhieu benh nhan nhat nam 2016
select diachi , count(*) as benhnhan from benhnhan join dieutri using (msbn)
where EXTRACT (year from ngaynhapvien) = 2016
group by (diachi) order by (count(*)) desc limit 1;

---- BAI 7 
create table company (
    company_id char(10) PRIMARY KEY,
    name char(100),
    numberofemployee integer,
    address char(1100),
    telephone char(10),
    establishmentDay date
);

create table supply (
    company_id char(10),
    product_id char(10),
    quantity integer,
    PRIMARY KEY (company_id,product_id),
    FOREIGN KEY (company_id) REFERENCES company (company_id)
);
create table product (
    product_id char(10) PRIMARY KEY,
    name char(100),
    color char(10),
    price money,
    FOREIGN KEY product_id REFERENCES supply (product_id)
);

--2: Cho bet ten , dia chi co dia chi tai London
select name, address from company where address like '%London%';

--3: Cho biet thong tin co cung cap mat hang mau do va nhan vien >1000
select * from company where numberofemployee > 1000
and company_id in (select company_id from supply where product_id in 
(select product_id from product where color = 'red'));

--4 : cho biet cong ty cung tat ca mat hang mau sac blue 
select company_id from company join supply using (company_id)
join product using (product_id) where color = 'blue' GROUP BY (company_id) HAVING
count (*) = (select count(*) from product where color = 'blue');

--5 : cho biet thong tin cong ty chua cung cap mat hang nao 
select * from company where company_id not in 
(select company_id from supply);

--6 : Liet ke cong ty ky niem 20 nam thanh lap nam 2019
select * from company where 2019 - EXTRACT (year from establishmentDay) = 20;

--7: Cho biet tog so nhan vien lao dong cho cac cty o Paris
select count(numberofemployee) as tongnhanvien from company where 
address like '%Paris%' group by (address);

--8 : Cho biet so luong trung binh mat hang duoc cung cap boi cong ty co ten la 'EuroCard'
select avg(quantity) from company join supply using (company_id)
where name = 'eurocard';

--9 : moi mat hang deu tang gia 10%
update product set price = price * 1.1 ;

--10 : xoa thong tin lien quan den cong ty co ma 181119
delete FROM supply where company_id = '181119';
delete FROM company where company_id = '181119';

--- Bonus : 
--1 :  cho biet thong tin cong ty thanh lap trong thang 11 cach day 110 nam
select * from company where extract (month from establishmentDay) = 11
and extract (year from now()) - extract (year from establishmentDay) = 110;

--2 : cho biet cac san pham va cung ung cua cong ty Audi
select productid , quantity from supply where companyid in 
(select companyid from company where name = 'Audi');

--3 : ma cong ty cung ung it nhat 2 loai san pham va so luong >1000
select companyid , count(*) as total from supply where quantity >1000
order by (companyid) having count(*) >=2;

--4 : cong ty cung ung tat ca cac san pham mau den trong bang Product
select * from company where companyid in
(select companyid from supply join product using (productid) where color = 'Black' 
group by (companyid) having count(*) = (select count(*) from product where color = 'Black'));

--5 : Tong san pham cung ung boi Porche
select count(*) from company join supply using (companyid) where name = 'Porche';

--6 : Cong ty chua cung ung san pham nao
select * from company where companyid not in 
(select companyid from supply);

--7 : tao view macty, ten , dien thoai, ma sp, tensp, quantity
create view sanpham
select conpanyid, company.name, phone, productid , product.name, quantity
from company join supply using (companyid) join product using (productid) 
where color = 'red';
select * from sanpham; 

--8 : xoa cong ty co ma 2
delete from supply where companyid = '2';
delete from company where companyid = '2';


------Bai 8 :

create table ctdt (
    mactdt CHAR(10) PRIMARY KEY,
    tenctdt char(100),
    sotinchi integer,
    khoavien char(100)
);

create table hocphan (
    mahp char(10) PRIMARY KEY,
    tenhp char(10),
    sotctl integer,
    sogiolt integer,
    sogiobt integer,
    sogioth integer,
    heso real,
    mactdt char(10),
    FOREIGN KEY (mactdt) REFERENCES ctdt(mactdt)
);

create table dieukienhoctruoc (
    id char(10) PRIMARY key,
    mahp char(10),
    mahpdieukien char(10),
    FOREIGN key (mahp) REFERENCES hocphan (mahp),
    FOREIGN key (mahpdieukien) REFERENCES hocphan(mahp)
);
create table sinhvien (
    masv char(10) PRIMARY KEY,
    tensv char(100),
    lop char(50),
    email char(30)
);
create table dangky (
    masv char(10),
    mahp char(10),
    kyhoc char(10),
    diemqt real,
    diemck real,
    PRIMARY KEY (masv, mahp,kyhoc),
    FOREIGN KEY (masv) references sinhvien(masv),
    FOREIGN key (mahp) REFERENCES hocphan(mahp)
);

---1 : liet ke ma ctdt va ten do vien cntt quan ly 
select mactdt, tenctdt from ctdt where khoavien = 'CNTT';

--2: dua ra ds hp , so tc tich luy,.. cua nganh ky su he thong thong tin
select mahp, tenhp , sotctl, sogiolt + sogiobt + 1.5 * sogioth as tinchihocphi from 
hopphan where mactct IN
(select mactdt from ctdt where tenctdt = 'Ky su he thong thong tin');

--3 : Dua ra ma, ten hp la dieu kien hoc truoc cua hoc phan 'Tinh toan luoi'
select mahp , tenhp from hocphan where mahp in 
(select mahpdieukien from dieukienhoctruoc where mahp in 
(select mahp from hocphan where tenhp = 'Tinh toan luoi'));

--4 : Dua ra ten hp vua xuat hien dao tao 'Ky su nganh KTMT' va 'Ky su nganh CNPM'
select tenhp from hocphan where mactdt in 
(select mactdt from ctdt where tenctdt = 'Ky su nganh KTMT'
INTERSECT select mactdt from ctdt where tenctdt = 'Ky su nganh CNPM');

--5 : Dua ra danh sach hoc phan, diem thi ck cao nhat, thap nhat, trung binh tung hoc phan

select tenhp, max(diemck), min(diemck), avg(diemck) from dangky join hocphan using (mahp)
group by (tenhp);

-- 6 : Dua ra ten sv, tong tctl ma sv dang ky hoc theo tung ct
select tensv , count(sotctl) from dangky join sinhvien using (masv) join hocphan using (mahp)
group by (tensv);

------ Bai 8 :
create table thesim (
    sosim char(10) PRIMARY key,
    trangthai char(100),
    manhamang char(10)
);
create table khachhang (
    makhachhang char(10) PRIMARY key,
    ten char(100),
    tuoi INTEGER
);
create table dangkysudung (
    sosim char(10) PRIMARY KEY,
    makhachhang char(10),
    ngaykichhoat date,
    FOREIGN KEY (sosim) REFERENCES thesim (sosim),
    FOREIGN key (makhachhang) REFERENCES khachhang (makhachhang)

);

create table nhamang (
    manhamang char(10) PRIMARY key,
    ten char(10),
    sodt char(10),
    giacuoc money,
    FOREIGN key (manhamang) REFERENCES thesim (manhamang)
);

create table lichsusudung (
    sosim char(10) PRIMARY KEY,
    sosimnhancuocgoi char(10),
    ngaycuocgoi date,
    thoidiembatdau char(10),
    thoiluong real,
    FOREIGN key (sosim) references thesim (sosim),
    FOREIGN key (sosimnhancuocgoi) references thesim (sosim)
);

-- 1: liet ke ds khach hang su dung tren 60 tuoi
select ten , tuoi from khachhang where tuoi > 60;

-- 2: ds khach hang su dung vinaphone
select * from khachhang where makhachhang in 
(select makhachhang from dangkysudung where sosim in
(select sosim from thesim where manhamang in 
(select manhamang from nhamang where ten = 'VNPT')));

-- 3: ds khach hang va so luong sim da dang ky 
select makhachhang , count(*) as so_sim from khachhang join dangkysudung using (makhachhang)
group by (makhachhang) ;

-- 4 : Nguoi su dung mang ca vnpt va viettel
select * from khachhang where makhachhang in 
(select makhachhang from dangkysudung where sosim in
(select sosim from thesim where manhamang in 
(select manhamang from nhamang where ten = 'VNPT'
INTERSECT select manhamang from nhamang where ten = 'Viettel')));

-- 5 : Nguoi chi su dung sim vinaphone 

select makhachhang from khachhang join dangkysudung using (makhachhang)
group by (makhachhang) having count (*) = (
select makhachhang from khachhang join dangkysudung using (makhachhang)
where sosim in
(select sosim from thesim where manhamang in 
(select manhamang from nhamang where ten = 'VNPT')));

--6 : tong cuoc
select makhachhang , ten, EXTRACT (month from ngaykichhoat), (12 - extract(month from ngaykichhoat))*giacuoc 
from khachhang join dangkysudung using (makhachhang) join thesim using(sosim) join nhamang using (manhamang)
where (12 - extract(month from ngaykichhoat))*giacuoc  > 500000;


--- Bai 9 :
create table sinhvien (
    mssv int not null primary key,
    hoten char(40) not null,
    gioitinh int not null,
    quequan char(40) not null,
    cpa float not null
);

create table monhoc (
    mamon int not null PRIMARY KEY,
    tenmon char(30) not null,
    sotinchi int not null,
    trongsogk float not null
);

create table hoc (
    mssv int NOT NULL,
    mamon int not null,
    diemgk float,
    diemck float,
    PRIMARY KEY (mssv,mamon),
    FOREIGN key (mssv) REFERENCES sinhvien (mssv),
    FOREIGn KEY (mamon) references monhoc(mamon)
);

--1 : cho biet thong tin sinh vien que quan Ha Nam
select * from sinhvien where quequan like '%Ha Nam%';

--2 : ten , que quan cua sv co hoc Co so du lieu
select * from sinhvien where mssv in 
(select mssv from hoc where mamon in
(select mamon from monhoc where tenmon = 'Co so du lieu'));

--3 : tong so sinh vien hoc mon co ma 3290
select count(*) as tong_sv from hoc where mamon = '3290';

--4 : mssv cua sinh vien hoc tat ca cac mon
select mssv from hoc group by (mssv) having count(*) = 
(select count(*) from monhoc);

--5 : dia phuong nao co it nhat 5 nu sinh vien co hoc luc gioi (>3.2)
select quequan from sinhvien where gioitinh = 'Nu' and cpa > 3.2 group by (quequan)
having count(*) >=5;

--6 : danh sach sv nu hoc luc gioi cua dia phuong co it nhat 10 sv gioi, trong do it nhat 2 sinh vien nu
select mssv, hoten from sinhvien where gioitinh = 'Nu' and quequan in 
(select quequan from sinhvien where cpa > 3.2 group by (quequan) 
having count(*) >=10 INTERSECT (select quequan from sinhvien where cpa > 3.2 and gioitinh = 'Nu' group by (quequan) 
having count(*) >=2));

--7 : xoa sv 2611
delete FROM hoc where mssv = '2611';
delete FROM sinhvien where mssv = '2611';

--8 : 3290 thay doi tin xuong 2 
update monhoc set sotinchi = 2 where mamon = '3290';

---bonus :
--1 : tong diem thi tat ca cac mon '20111625'
select sum(diemck) from hoc where mssv = '20111625';


--- Bai 10:
create table student (
    studentid char(10) PRIMARY key,
    name char(100),
    address char(100)
);
create table subject (
    subjectcode char(10) primary key,
    name char(10),
    faculty char(10)
);


create table take (
    studentid char(10),
    subjectcode char(10),
    PRIMARY key (studentid,subjectcode)
);

create table course (
    courseid char(10) PRIMARY key,
    name char(100),
    faculty char(10)
);

create table enrol (
    studentid char(10),
    courseid char(10),
    PRIMARY key (studentid, courseid)
);

--1 : cho biet sv hoc mon co ma IT3292
select * from student where studentid in
(select studentid from take where subjectcode where subjectcode = 'IT3292');

--2: Cho biet sinh vien hoc o New York va hoc Database 
select * from student where address like '%New York%' and studentid in
(select studentid from take where subjectcode in
(select subjectcode from subject where name = 'Database Lab'));

--3 : cho biet sinh hoc tat ca cac mon
select studentid from student join take using (studentid) group by (studentid)
having count(*) = (select count(*) from subject);

--4 : Tong so sinh vien hoc mon IT3292
select count(*) as total from student where studentid IN
(select studentid from take where subjectcode = 'IT3290');

--5 : xoa sinh vien '27112020'
delete from take where studentid = '27112020';
delete from enrol where studentid = '27112020';
delete from student where studentid = '27112020';


-- Bai 10 :
create table customer (
    customerid char(10) PRIMARY key,
    firstname char(10),
    lastname char(10),
    address1 char(10),
    address2 char(10),
    city char(10),
    state char(10),
    zip char(2),
    country char(10),
    region char(10),
    email char(10),
    phone char(10),
    creditcardtype char(10),
    creditcard char(10),
    creditcardexpiration date,
    username char(10),
    password char(10),
    age integer,
    income integer,
    gender char(10)
);

create table order (
    orderid char(10) PRIMARY key,
    orderdate date,
    customerid char(10),
    netamount integer,
    tax integer,
    totalamount integer,
    FOREIGN key (customerid) references customer(customerid);
);

create table categories (
    category char(10) primary key,
    categoryname char(10)
);
create table product (
    prod_id char(10) PRIMARY key,
    category char(10),
    title char(10),
    actor char(10),
    price integer,
    special integer,
    common_prod_id char(10),
    FOREIGN key (category) REFERENCES categories (category)
);

create table orderline (
    orderlineid char(10),
    orderid char(10),
    prod_id char(10),
    quantity integer,
    orderdate date,
    PRIMARY key (orderlineid, orderid),
    FOREIGN key prod_id REFERENCES product(prod_id)
);

create table inventory (
    prod_id char(10) PRIMARY key,
    quan_in_stock integer,
    sales INTEGER,
    FOREIGN key (prod_id) REFERENCES product (prod_id)
);

-- 1: Dua ra danh sach san pham thuoc comedy gia <10, title co chua airport
select * from product where price < 10 and title like '%airport%'
and category in 
(select category from cattegories where categoryname = 'Comedy');

--2 : danh sach khach hang nu co thu nhap 50.000 tro nen
select * from customer where gender = 'Femle' and income >500000;

--3 : thong tin san pham gom : title, actor, price, tong ban duoc trong 3 thang cuoi nam 2014
select title, actor, price, sum(quantity) from product join orderline using (prod_id)
where extract (month from orderdate ) >= 10 end extract (year from orderdate) = 2014;

--4 : cho biet ten , phone, thoi gian het han the cua khach hang het han trong nam hien tai
select concat(firstname, ' ', lastname) , age, phone, creditcardexpiration from customer
where extract (year from creditcardexpiration) = extract (year from now());

--5 : lap danh sach co ngay mua la ngay hien thoi
select * from order where orderdate = now();

--6 : loai san pham k duoc mua 11/2011
select * from product where prod_id not in 
(select prod_id from orderline where extract(month from orderdate) = 11 and
extract (year from orderdate) = 2011);

--7 : Dua ra danh sach 10 nguoi mua nhieu nhat va so luong toi thieu la 5
select customerid, count(*) as total from customer where customerid join order using (customerid) 
group by (customerid) having count(*) >= 5 order by  (count(*)) desc limit 5;

--8 : Hay cho biet gia lon nhat , gia trung binh, nho nhat cua 10 mat hang an chat nhat (tinh theo so luong ban duoc)
select max(price), min(price), avg(price) from product where prod-id in
(select prod_id from product join orderline using (prod_id) group by (prod_id)
order by (count(quantity)) desc limit 10);

--9 : cho biet moi loai category co bao nhieu san pham 
select categoryname, count(*) as total from categories join product using (category) 
group by (categoryname) ;

--10 : chia theo san pham so luong gioi tinh
(select category , count(*) as male from product join orderline using (prod_id) join order using (orderid) join customer using (customerid)
where gender = 'Male' group by (category))
INTERSECT (select category , count(*) as male from product join orderline using (prod_id) join order using (orderid) join customer using (customerid)
where gender = 'Female' group by (category));
-- procedure :

-- Bonus : 
--1 : danh sach don hang ngay mua 6/2004
select orderid, concat (firstname, ' ',lastname) , orderdate, totalamount
from order join customer using (customerid) where
extract (year from orderdate) = '2004' and extract (month from orderdate) = 6;

--2 : danh sach san pham chua ai dat hang 12/2004
select * from product where prod_id not in 
(select prod_id from orderline where 
extract (year from orderdate) = '2004' and extract (month from orderdate) = 12);

--3 : cho tuoi max, min ,avg cua kh mua san pham title airport robbers
select max(age), min(age), avg(age) from customer where customerid in
(select customerid from order where orderid in
(select orderid from orderline where prod_id in
(select prod_id from product where title = 'Airport robbers')));

--4 : bao nhieu khach hang khac nhau mua it nhat 1 mat hang
select count(*) from (select distinct customerid from order);

--5 : lap danh sach san pham , so luong tuong ung, ban trong ngay lap danh sach , sap xep giam dan theo so luong ban
select pro_id, count(quantity) from orderline where 
orderdate = now() order by (count(quantity)) desc;

--6 : dua ra ds khach hang co it nhat 1 hoa don > 1500
select * from customer where customerid in 
(select customerid from order where totalamount > 1500
group by (customerid) having count(*) >=1);

-- 7 : dua ra ds ten nuoc, so luong khach hang, luot khach hang, da mua hang tu moi nuoc
select * from (select city , count(*) as total from customer group by (city)) as C1 join (select city , count(*) as so_luot from customer join order using (customerid) group by (city)) as C2 using (city);

-- 8 : san pham duoc nu mua nhieu nhat 
select count(*) , prod_id from order join orderline using (orderid)
where (customerid in (select customerid from customer where gender = 'female'))
group by (prod_id) order by (count(*)) limit 1;


-- 9 : thu nhap trung binh cua tung gioi tinh dv khach hang co don 2000 tro nen
select avg(income) from customer where gender = 'male'
and customerid in (select customerid from order where totalamount >2000);




-- 
create or replace procedure update(prodid char(10))
as 
$$
    declare quanti integer;
BEGIN
    select into quanti quantity from orderlines 
    where prod_id = prodid and orderdate = now();
    update inventory set sale = sale + quanti
    where prod_id = prodid;
end;
$$
language plpgsql;


--- Bai 11
create table tacgia (
    tacgiaid char(10) primary key,
    hoten char(10),
    ngaysinh date,
    diachi char(10),
    email char(10)
);

create table sach (
    masachid char(10) primary key,
    tensach char(10),
    nhaxuatban char(10),
    namxuatban integer
);
create table vietsach (
    tacgiaid char(10),
    masachid char(10).
    nhuanbut integer,
    primary key (tacgiaid, masachid),
    FOREIGN key (tacgiaid) references tacgia (tacgiaid),
    FOREIGN key (masachid) references masach (masachid)
);

-- 1: dua ra tac gia thuoc truong cntt va tt
select * from tacgia where email like '%@soict.hust.edu.vn%';

---2 : dua ra ms, hoten , viet cuon sach 'Tich hop du lieu'
select tacgiaid, hoten from tacgia where tacgiaid in
(select tacgiaid from vietsach where masachid in 
(select masachid from sach where tensach = 'Tich hop du lieu'));

--3 : Dong tac gia cua cuon sach 'MS112'
select count(*) as dongtacgia from vietsach where masachid = 'MS112';

--4 : cho biet hoten , ngaysing cua cac tac gia co tong tien nhuan but lon nhat
select hoten , ngaysinh from tacgia where tacgiaid in
(select tacgiaid from vietsach where nhuanbut >= ALL (select nhuanbut from vietsach));


-- Bai 12 :
create table sinhvien (
    mssv char(10) PRIMARY key, 
    hoten char(10),
    ngaysinh date,
    gioitinh char(10),
    quequan char(100)
);

create table monhoc (
    mamon char(10) primary key,
    tenmon char(10),
    sotinchi integer,
    hocphi integer
);

create table dangky (
    mssv char(10),
    mamon char(10),
    kyhoc char(10),
    diem real,
    primary key (mssv, mamon),
    FOREIGN key (mssv) REFERENCES sinhvien(mssv),
    foreign key (mamon) references monhoc(mamon)
);

-- 1 : Dua ra mon co tin < 3
select * from monhoc where sotinchi < 3;

--2 : Mon hoc hoc phi nhap nhat 
select * from monhoc where hocphi <=ALL (select hocphi from monhoc);

-- 3 : cho biet tong hoc phi ma 20205001 da dong
select count(hocphi) from monhoc join dangky using (mamon)
where mssv  = '20215001';

--4 : Diem cao nhat cua mon IT3290 cua sv 20205059
select max(diem) as ck_cao from dangky
where mamon = 'IT3290' and mssv = '20205059';

--5 : Tinh diem gpa trung binh tich luy cya 20205112 
select sum(diem* sotinchi) / sum(sotinchi) from dangky join monhoc
using (mamon) where mssv = '20205112';

-- 6 : Sinh vien ma 20191111 hoc lai bao nhieu mon 
select count(*) from (select mssv, mamon from dangky where mssv = '2019111' group by (mssv, mamon)
having count(*) = 2);

-- 7 : Tao khung nhin chua ma mon, hoc ky , hoc phi 20200404
create view  tkb 
select mamon, hocky, hocphi from dangky join monhoc using (mamon)
where mssv = '20200404';

--8 : Trigger kiem tra ngay sinh nho hon 15 tuoi thi thong bao

create or replace trigger check_date 
after insert on sinhvien 
for each row 
execute procedure check_age();

create or replace check_age()
returns trigger as 
$$
    declare nsing date ;
begin 
    select into nsing ngaysinh from sinhvien where
    mssv = new.mssv;
    if (extract (year from now())- extract (year from nsing) < 15) then
    raise notice 'khong du tuoi';
    return old;
    end if;
    return new;
end;
$$
language plpgsql;

--9 : moi sinh vien ma mon IT3290 o ky 20212 cong 1 diem
update on dangky set diem = diem + 1
where mamon = 'IT3290' and kyhoc = '20212';



-- Bai 13 :
create table sach (
    masach char(10) primary key,
    tensach char(100),
    namxuatban int,
    dongia int,
    theloai char(100),
    soluongcon int
);

create table khachhang (
    makh char(10) primary key,
    tenkh char(100),
    diachi char(100),
    email char(100),
    mst char(10)
);

create table donhang (
    madon char(10) primary key,
    makh char(10), 
    ngaymua date,
    foreign key (makh) references khachhang (makh)
);

create table chitiet (
    madon char(10) primary key,
    masach char(10),
    quantity int,
    check (quantity  < sach(soluongcon)),
    foreign key (madon) references donhang (madon),
    foreign key (masach) references sach (masach)
);

--1 : dua ra quyen sach ma so luong < 10
select * from sach where soluongcon < 10;

--2 : sach 'Dan toc An nam ' duoc ban nhieu cuon
select count(*) from chitiet where masach in 
(select masach from sach where tensach = 'dan toc An Nam');

---3 : tong gia tridon hang khach 01231 mua tu truoc den nay
select sum (quantity * dongia ) from chitiet join sach using (masach)
where madon in (select madon from donhang where 
makh = '01231' and ngaymua <= now());

-- 4 : Tao thu tuc nhan ma sach, hien thi so luong da ban va so luong con lai
create or replace function (sachid char(10))
returns int as 
$$
declare quantity int;
begin 
    select into quantity sum(quantity) from chitiet where
    masach = sachid;
    return quantity;
end;
$$
language plpgsql;
--5 : xoa don hang ngay 25/06/2023 
delete from chitiet where madon in 
(select madon from donhang where ngaymua = '25-06-2023');
delete from donhang where ngaymua = '25-06-2023';
