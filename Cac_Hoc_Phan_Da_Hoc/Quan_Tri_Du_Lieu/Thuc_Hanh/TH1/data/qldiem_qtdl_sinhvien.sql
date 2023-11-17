-- MySQL dump 10.13  Distrib 8.0.32, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: qldiem_qtdl
-- ------------------------------------------------------
-- Server version	8.0.32

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `sinhvien`
--

DROP TABLE IF EXISTS `sinhvien`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sinhvien` (
  `mssv` char(8) NOT NULL,
  `hoTen` varchar(50) NOT NULL,
  `gioiTinh` char(1) DEFAULT NULL,
  `ngaySinh` date DEFAULT NULL,
  `noiSinh` varchar(40) DEFAULT NULL,
  `diaChi` varchar(100) DEFAULT NULL,
  `maKhoa` char(8) DEFAULT NULL,
  PRIMARY KEY (`mssv`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sinhvien`
--

LOCK TABLES `sinhvien` WRITE;
/*!40000 ALTER TABLE `sinhvien` DISABLE KEYS */;
INSERT INTO `sinhvien` VALUES ('B1234567','Nguyễn Thanh Hải','M','2001-12-02','Bạc Liêu','Phường 01, KTX B, DHCT','CNTT&TT'),('B1234568','Trần Thanh Mai','M','2001-01-20','Cần Thơ','232, Nguyễn Văn Khéo, Quận Ninh Kiều, Cần Thơ','CNTT&TT'),('B1234569','Trần Thu Thủy','F','2001-07-01','Cần Thơ','02, Địa lộ Hòa Bình, Q. Ninh Kiều, TPCT','CNTT&TT'),('B1334569','Nguyễn Thị Trúc Mã','F','2002-05-25','Sóc Trăng','343, Đường 30/4. Q.Ninh Kiều, TPCT','SP'),('B1345678','Trần Hồng Trúc','F','2002-03-02','Cần Thơ','123, Trần Hưng Đạo, Q. Ninh Kiều, TPCT','CNTT&TT'),('B1345679','Bùi Hoàng Yến','F','2001-11-05','Vĩnh Long','Phòng 201, KTX A, TPCT','CNTT&TT'),('B1345680','Trần Minh Tâm','M','2001-02-04','Cà Mau','07, Đại lộ Hòa Bình, Q. Ninh Kiều, TPCT','KT'),('B1456789','Nguyễn Hồng Thắm','F','2003-05-09','An Giang','133, Nguyễn Văn Cừ, Q. Ninh Kiều, TPCT','NNG'),('B1459230','Lê Văn Khang','M','2002-06-02','Đồng Tháp','312, Nguyễn Văn Linh, Q.Ninh Kiều, TPCT','NN');
/*!40000 ALTER TABLE `sinhvien` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-02-22  9:30:16
