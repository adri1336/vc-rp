-- MariaDB dump 10.17  Distrib 10.4.6-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: vc_rp
-- ------------------------------------------------------
-- Server version	10.4.6-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `achievements`
--

DROP TABLE IF EXISTS `achievements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `achievements` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `achievements`
--

LOCK TABLES `achievements` WRITE;
/*!40000 ALTER TABLE `achievements` DISABLE KEYS */;
INSERT INTO `achievements` VALUES (1,'new user'),(2,'rent_car'),(3,'purchase_car'),(4,'purchase_used_car'),(5,'driver_license'),(6,'hospital_bed'),(7,'use_atm'),(8,'purchase_property'),(9,'rent_property'),(10,'purchase_business'),(11,'gun_license'),(12,'intro');
/*!40000 ALTER TABLE `achievements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `actors`
--

DROP TABLE IF EXISTS `actors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `actors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `skin` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `angle` float NOT NULL DEFAULT 0,
  `animation` tinyint(1) NOT NULL DEFAULT 0,
  `animlib` varchar(32) NOT NULL DEFAULT 'animlib',
  `animname` varchar(32) NOT NULL DEFAULT 'animname',
  `anim_loop` tinyint(1) NOT NULL DEFAULT 0,
  `lockx` tinyint(1) NOT NULL DEFAULT 0,
  `locky` tinyint(1) NOT NULL DEFAULT 0,
  `freeze` tinyint(1) NOT NULL DEFAULT 0,
  `time` int(11) NOT NULL DEFAULT 0,
  `id_entrance` int(11) DEFAULT NULL,
  `id_business` int(11) DEFAULT NULL,
  `id_property` int(11) DEFAULT NULL,
  `clerk` tinyint(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `id_entrance` (`id_entrance`),
  KEY `id_business` (`id_business`),
  KEY `id_property` (`id_property`),
  CONSTRAINT `actors_ibfk_1` FOREIGN KEY (`id_entrance`) REFERENCES `entrances` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `actors_ibfk_2` FOREIGN KEY (`id_business`) REFERENCES `business` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `actors_ibfk_3` FOREIGN KEY (`id_property`) REFERENCES `properties` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `actors`
--

LOCK TABLES `actors` WRITE;
/*!40000 ALTER TABLE `actors` DISABLE KEYS */;
INSERT INTO `actors` VALUES (2,148,1169.74,-1345.96,2423.05,180,0,'animlib','animname',0,0,0,0,0,1,NULL,NULL,0),(3,187,2383.26,2659.64,8001.15,0,0,'animlib','animname',0,0,0,0,0,2,NULL,NULL,0),(4,17,5090.7,704.122,994.023,0,0,'animlib','animname',0,0,0,0,0,3,NULL,NULL,0),(5,141,5081.49,715.463,994.023,270,0,'animlib','animname',0,0,0,0,0,3,NULL,NULL,0),(6,147,1455.4,-1004.39,2725.88,180,0,'animlib','animname',0,0,0,0,0,4,NULL,NULL,0),(7,150,1451.38,-1004.39,2725.88,180,0,'animlib','animname',0,0,0,0,0,4,NULL,NULL,0),(8,219,6411.68,2207.86,1213.05,90,0,'animlib','animname',0,0,0,0,0,7,NULL,NULL,0),(9,59,6416.17,2207.6,1213,270,0,'animlib','animname',0,0,0,0,0,7,NULL,NULL,0),(10,150,6412.26,2139.16,1213.23,135,0,'animlib','animname',0,0,0,0,0,7,NULL,NULL,0),(12,210,-2035.09,-117.559,1035.17,270,0,'animlib','animname',0,0,0,0,0,9,NULL,NULL,0),(13,141,27.8483,30.9537,1000.09,357.398,1,'ped','SEAT_idle',1,0,0,1,0,11,NULL,NULL,0),(14,150,4963.45,206.031,7.55,229.267,0,'ped','SEAT_idle',1,0,0,1,0,NULL,NULL,NULL,0),(15,142,-29.193,-186.818,1003.55,359.929,0,'animlib','animname',0,0,0,0,0,NULL,1,NULL,1),(16,184,5029.79,350.933,994.525,8.21922,0,'animlib','animname',0,0,0,0,0,NULL,2,NULL,1),(17,211,207.549,-98.7008,1005.26,181.513,0,'animlib','animname',0,0,0,0,0,NULL,3,NULL,1),(18,155,375.641,-117.273,1001.49,178.429,0,'animlib','animname',0,0,0,0,0,NULL,4,NULL,1),(19,217,203.816,-41.61,1001.8,181.859,0,'animlib','animname',0,0,0,0,0,NULL,5,NULL,1),(20,67,2.21658,-30.7031,1003.55,0,0,'animlib','animname',0,0,0,0,0,NULL,6,NULL,1),(21,247,5405.15,1693.99,995.992,97.2792,0,'animlib','animname',0,0,0,0,0,NULL,7,NULL,1),(22,155,375.641,-117.273,1001.49,178.429,0,'animlib','animname',0,0,0,0,0,NULL,8,NULL,1),(23,217,207.108,-127.8,1003.51,180,0,'animlib','animname',0,0,0,0,0,NULL,9,NULL,1),(24,167,370.087,-4.47238,1001.86,180,0,'animlib','animname',0,0,0,0,0,NULL,10,NULL,1),(25,217,203.816,-41.61,1001.8,180,0,'animlib','animname',0,0,0,0,0,NULL,11,NULL,1),(26,179,308.167,-143.097,999.602,358.886,0,'animlib','animname',0,0,0,0,0,NULL,12,NULL,1),(27,211,204.854,-8.10225,1001.21,270,0,'animlib','animname',0,0,0,0,0,NULL,13,NULL,1),(28,289,-2237.12,128.584,1035.41,0.877149,0,'animlib','animname',0,0,0,0,0,NULL,14,NULL,1),(29,217,6408.99,2092.6,994.405,222.976,0,'animlib','animname',0,0,0,0,0,NULL,15,NULL,1),(30,211,6408.98,2092.61,1000.73,223.603,0,'animlib','animname',0,0,0,0,0,NULL,15,NULL,1),(31,179,5936.97,-433.057,997.109,356.088,0,'animlib','animname',0,0,0,0,0,NULL,16,NULL,1),(32,182,6363.53,2125.21,997.609,357.599,0,'animlib','animname',0,0,0,0,0,NULL,17,NULL,1),(33,186,6471.2,2058.17,997.431,110.982,0,'animlib','animname',0,0,0,0,0,NULL,18,NULL,1),(34,188,-27.9157,-91.6371,1003.55,0,0,'animlib','animname',0,0,0,0,0,NULL,19,NULL,1),(35,205,375.841,-65.849,1001.51,182.74,0,'animlib','animname',0,0,0,0,0,NULL,20,NULL,1),(36,155,375.636,-117.275,1001.49,180,0,'animlib','animname',0,0,0,0,0,NULL,21,NULL,1),(37,169,6466.63,995.309,998.531,230,0,'animlib','animname',0,0,0,0,0,NULL,22,NULL,1),(38,183,5030.04,350.959,994.526,7,0,'animlib','animname',0,0,0,0,0,NULL,23,NULL,1),(39,206,-29.0755,-186.819,1003.55,3,0,'animlib','animname',0,0,0,0,0,NULL,24,NULL,1),(40,155,375.513,-117.278,1001.49,180,0,'animlib','animname',0,0,0,0,0,NULL,25,NULL,1),(41,237,6090.2,-388.912,998.031,123.037,0,'animlib','animname',0,0,0,0,0,NULL,26,NULL,1),(42,179,5315.34,2247.77,997.178,0,0,'animlib','animname',0,0,0,0,0,NULL,27,NULL,1),(43,87,6082,-393.296,999.078,203.991,1,'STRIP','STR_A2B',1,1,1,0,0,NULL,26,NULL,0),(44,244,6080,-396.855,999.047,275.174,1,'STRIP','strip_G',1,1,1,0,0,NULL,26,NULL,0),(45,246,6086.03,-393.427,999.039,148.385,1,'STRIP','STR_B2C',1,1,1,0,0,NULL,26,NULL,0),(46,256,6072.89,-394.55,998.867,296.65,1,'STRIP','STR_C1',1,1,1,0,0,NULL,26,NULL,0),(47,257,6086.16,-398.093,998.867,34.4435,1,'STRIP','STR_C2',1,1,1,0,0,NULL,26,NULL,0);
/*!40000 ALTER TABLE `actors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `admin_restrictions_types`
--

DROP TABLE IF EXISTS `admin_restrictions_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admin_restrictions_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(24) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin_restrictions_types`
--

LOCK TABLES `admin_restrictions_types` WRITE;
/*!40000 ALTER TABLE `admin_restrictions_types` DISABLE KEYS */;
INSERT INTO `admin_restrictions_types` VALUES (1,'PERM_BAN'),(2,'TEMP_BAN'),(3,'KICK'),(4,'WARN');
/*!40000 ALTER TABLE `admin_restrictions_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business`
--

DROP TABLE IF EXISTS `business`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_type` int(11) NOT NULL,
  `price` int(11) NOT NULL DEFAULT 0,
  `level` int(11) NOT NULL DEFAULT 1,
  `money` int(11) NOT NULL DEFAULT 0,
  `hour_open` int(11) NOT NULL DEFAULT 0,
  `hour_close` int(11) NOT NULL DEFAULT 0,
  `id_player` int(11) DEFAULT NULL,
  `radio` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `id_type` (`id_type`),
  KEY `id_player` (`id_player`),
  CONSTRAINT `business_ibfk_1` FOREIGN KEY (`id_type`) REFERENCES `business_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_ibfk_2` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business`
--

LOCK TABLES `business` WRITE;
/*!40000 ALTER TABLE `business` DISABLE KEYS */;
INSERT INTO `business` VALUES (1,1,80000,5,10000,0,0,NULL,0),(2,10,50000,3,10000,10,20,NULL,0),(3,3,80000,5,10000,10,20,NULL,0),(4,6,80000,5,10000,0,0,NULL,0),(5,3,80000,5,10000,10,20,NULL,0),(6,1,80000,5,10000,0,0,NULL,0),(7,8,60000,5,10000,0,0,NULL,0),(8,6,80000,5,10000,0,0,NULL,0),(9,3,80000,5,10000,10,20,NULL,0),(10,4,80000,5,10000,0,0,NULL,0),(11,3,80000,5,10000,10,20,NULL,0),(12,2,100000,10,10000,10,20,NULL,0),(13,3,90000,5,10000,9,22,NULL,0),(14,9,100000,6,10000,0,0,NULL,0),(15,3,100000,6,10000,0,0,NULL,0),(16,2,100000,10,10000,0,0,NULL,0),(17,10,80000,6,10000,0,0,NULL,0),(18,8,100000,6,10000,0,0,NULL,0),(19,1,80000,10,10000,10,22,NULL,0),(20,5,80000,10,10000,0,0,NULL,0),(21,6,80000,5,10000,0,0,NULL,0),(22,7,200000,10,10000,20,8,NULL,0),(23,10,60000,4,10000,10,20,NULL,0),(24,1,80000,5,10000,10,21,NULL,0),(25,6,80000,5,10000,0,0,NULL,0),(26,7,150000,10,10000,20,8,NULL,0),(27,2,100000,10,10000,10,20,NULL,0);
/*!40000 ALTER TABLE `business` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_doors`
--

DROP TABLE IF EXISTS `business_doors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_doors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_business` int(11) NOT NULL,
  `closed` int(11) DEFAULT 0,
  `ext_x` float NOT NULL,
  `ext_y` float NOT NULL,
  `ext_z` float NOT NULL,
  `ext_angle` float NOT NULL DEFAULT 0,
  `ext_entrance_door_id` int(11) DEFAULT NULL,
  `ext_sub_id` int(11) DEFAULT NULL,
  `id_interior` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_business` (`id_business`),
  KEY `ext_entrance_door_id` (`ext_entrance_door_id`),
  KEY `ext_sub_id` (`ext_sub_id`),
  KEY `id_interior` (`id_interior`),
  CONSTRAINT `business_doors_ibfk_1` FOREIGN KEY (`id_business`) REFERENCES `business` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_doors_ibfk_2` FOREIGN KEY (`ext_entrance_door_id`) REFERENCES `entrances_doors` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `business_doors_ibfk_3` FOREIGN KEY (`ext_sub_id`) REFERENCES `business_doors` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `business_doors_ibfk_4` FOREIGN KEY (`id_interior`) REFERENCES `interiors` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_doors`
--

LOCK TABLES `business_doors` WRITE;
/*!40000 ALTER TABLE `business_doors` DISABLE KEYS */;
INSERT INTO `business_doors` VALUES (1,1,0,5139.63,408.315,5.70541,194.096,NULL,NULL,21),(2,2,0,5031.54,361.881,5.90675,9.76563,NULL,NULL,169),(3,3,0,4977.32,621.095,5.38871,275.586,NULL,NULL,81),(4,4,0,4940.25,1133.74,5.95259,91.1202,NULL,NULL,23),(5,5,0,4919.14,1135.22,5.67594,271.981,NULL,NULL,34),(6,6,0,5147.64,964.025,5.5665,200.82,NULL,NULL,29),(7,7,0,5402.69,1701.62,5.83891,10.5269,NULL,NULL,171),(8,8,0,5115.5,1846.34,5.58478,275.16,NULL,NULL,23),(9,9,0,5081.49,1935.29,5.53688,272.139,NULL,NULL,17),(10,10,0,5140.05,1908.71,5.64531,79.2928,NULL,NULL,131),(11,11,0,5122.85,2314.98,5.86438,273.024,NULL,NULL,34),(12,12,0,5323.49,2251,5.53687,176.549,NULL,NULL,25),(13,13,0,5532.01,2122.47,5.53375,341.397,NULL,NULL,26),(14,14,0,6471.11,2173.63,1219.03,90.4817,11,NULL,122),(15,15,0,6413.94,2091.9,1213.65,355.485,11,NULL,175),(16,15,0,6413.95,2091.7,1219.83,356.28,11,NULL,176),(17,16,0,6368.48,2106.65,1213.65,266.843,11,NULL,155),(18,17,0,6368.6,2128.21,1213.53,266.9,11,NULL,168),(19,18,0,6463.76,2059.78,1213.64,47.05,11,NULL,177),(20,19,0,6446.36,1823.47,7.41594,133.537,NULL,NULL,53),(21,20,0,6532.22,1819.85,5.70941,263.604,NULL,NULL,48),(22,21,0,6430.34,1122.29,5.59608,215.093,NULL,NULL,23),(23,22,0,6491.01,972.832,5.95585,221.875,NULL,NULL,153),(24,22,0,6488.74,970.525,5.94906,221.908,NULL,NULL,154),(25,23,0,6197.9,570.095,5.52744,183.578,NULL,NULL,169),(26,24,0,6124.31,145.045,4.89911,101.91,NULL,NULL,21),(27,25,0,6086.59,59.9482,4.93177,78.1523,NULL,NULL,23),(28,26,0,6096.68,-420.666,4.89437,211.69,NULL,NULL,167),(29,27,0,5940.11,-431.322,4.96858,260.079,NULL,NULL,156);
/*!40000 ALTER TABLE `business_doors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_sales`
--

DROP TABLE IF EXISTS `business_sales`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_sales` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_business` int(11) NOT NULL,
  `id_player` int(11) DEFAULT NULL,
  `id_product` int(11) NOT NULL,
  `price` int(11) NOT NULL DEFAULT 0,
  `amount` int(11) NOT NULL DEFAULT 1,
  `sale_date` datetime NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `id_business` (`id_business`),
  KEY `id_player` (`id_player`),
  KEY `id_product` (`id_product`),
  CONSTRAINT `business_sales_ibfk_1` FOREIGN KEY (`id_business`) REFERENCES `business` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_sales_ibfk_2` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `business_sales_ibfk_3` FOREIGN KEY (`id_product`) REFERENCES `business_sales_products` (`id_product`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_sales`
--

LOCK TABLES `business_sales` WRITE;
/*!40000 ALTER TABLE `business_sales` DISABLE KEYS */;
/*!40000 ALTER TABLE `business_sales` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_sales_points`
--

DROP TABLE IF EXISTS `business_sales_points`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_sales_points` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_type` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `id_interior` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_type` (`id_type`),
  KEY `id_interior` (`id_interior`),
  CONSTRAINT `business_sales_points_ibfk_1` FOREIGN KEY (`id_type`) REFERENCES `business_sales_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_sales_points_ibfk_2` FOREIGN KEY (`id_interior`) REFERENCES `interiors` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_sales_points`
--

LOCK TABLES `business_sales_points` WRITE;
/*!40000 ALTER TABLE `business_sales_points` DISABLE KEYS */;
INSERT INTO `business_sales_points` VALUES (1,9,-29.115,-185.13,1003.55,21),(2,10,5029.71,353.177,994.55,169),(3,9,207.563,-100.409,1005.26,81),(4,9,375.567,-119.321,1001.5,23),(5,9,203.819,-43.3595,1001.8,34),(6,9,2.25742,-29.0127,1003.55,29),(7,6,5403.67,1693.86,995.992,171),(8,9,207.087,-129.58,1003.51,17),(9,9,370.047,-6.17496,1001.86,131),(10,9,308.133,-141.204,999.602,25),(11,9,206.613,-8.12775,1001.21,26),(12,5,-2236.98,130.416,1035.41,122),(13,4,6410.28,2091.21,1000.73,175),(14,3,6410.28,2091.21,994.405,175),(15,9,5936.93,-430.576,997.102,155),(16,10,6363.55,2127.97,997.609,168),(17,6,6469.6,2058.39,997.439,177),(18,9,-28.1843,-89.9267,1003.55,53),(19,9,375.808,-67.6739,1001.52,48),(20,6,6468.02,994,998.531,153),(21,6,6088.72,-389.886,998.031,167),(22,9,5315.34,2250.46,997.178,156);
/*!40000 ALTER TABLE `business_sales_points` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_sales_products`
--

DROP TABLE IF EXISTS `business_sales_products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_sales_products` (
  `id_product` int(11) NOT NULL,
  `id_business` int(11) NOT NULL,
  `price` int(11) NOT NULL DEFAULT 0,
  `stock` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id_product`,`id_business`),
  KEY `id_business` (`id_business`),
  CONSTRAINT `business_sales_products_ibfk_1` FOREIGN KEY (`id_product`) REFERENCES `business_sales_products_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_sales_products_ibfk_2` FOREIGN KEY (`id_business`) REFERENCES `business` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_sales_products`
--

LOCK TABLES `business_sales_products` WRITE;
/*!40000 ALTER TABLE `business_sales_products` DISABLE KEYS */;
INSERT INTO `business_sales_products` VALUES (2,1,5,100),(2,4,5,100),(2,6,5,100),(2,8,5,100),(2,10,5,100),(2,19,5,100),(2,20,5,100),(2,21,5,100),(2,24,5,100),(2,25,5,100),(3,1,10,100),(3,4,10,100),(3,6,10,100),(3,8,10,100),(3,10,10,100),(3,19,10,100),(3,20,10,100),(3,21,10,100),(3,24,10,100),(3,25,10,100),(4,1,10,100),(4,4,10,100),(4,6,10,100),(4,8,10,100),(4,10,10,100),(4,19,10,100),(4,20,10,100),(4,21,10,100),(4,24,10,100),(4,25,10,100),(5,1,5,100),(5,4,5,100),(5,6,5,100),(5,8,5,100),(5,10,5,100),(5,19,5,100),(5,20,5,100),(5,21,5,100),(5,24,5,100),(5,25,5,100),(6,1,5,100),(6,4,5,100),(6,6,5,100),(6,8,5,100),(6,10,5,100),(6,19,5,100),(6,20,5,100),(6,21,5,100),(6,24,5,100),(6,25,5,100),(7,1,3,100),(7,4,3,100),(7,6,3,100),(7,8,3,100),(7,10,3,100),(7,19,3,100),(7,20,3,100),(7,21,3,100),(7,24,3,100),(7,25,3,100),(8,1,10,100),(8,4,10,100),(8,6,10,100),(8,8,10,100),(8,10,10,100),(8,19,10,100),(8,20,10,100),(8,21,10,100),(8,24,10,100),(8,25,10,100),(9,3,50,100),(9,5,50,100),(9,9,50,100),(9,11,50,100),(9,13,50,100),(9,15,50,100),(10,3,80,100),(10,5,80,100),(10,9,80,100),(10,11,80,100),(10,13,80,100),(10,15,80,100),(11,3,80,100),(11,5,80,100),(11,9,80,100),(11,11,80,100),(11,13,80,100),(11,15,80,100),(12,3,100,100),(12,5,100,100),(12,9,100,100),(12,11,100,100),(12,13,100,100),(12,15,100,100),(13,3,150,100),(13,5,150,100),(13,9,150,100),(13,11,150,100),(13,13,150,100),(13,15,150,100),(14,3,200,100),(14,5,200,100),(14,9,200,100),(14,11,200,100),(14,13,200,100),(14,15,200,100),(15,3,50,100),(15,5,50,100),(15,9,50,100),(15,11,50,100),(15,13,50,100),(15,15,50,100),(16,3,60,100),(16,5,60,100),(16,9,60,100),(16,11,60,100),(16,13,60,100),(16,15,60,100),(17,3,60,100),(17,5,60,100),(17,9,60,100),(17,11,60,100),(17,13,60,100),(17,15,60,100),(18,3,150,100),(18,5,150,100),(18,9,150,100),(18,11,150,100),(18,13,150,100),(18,15,150,100),(19,3,60,100),(19,5,60,100),(19,9,60,100),(19,11,60,100),(19,13,60,100),(19,15,60,100),(20,3,60,100),(20,5,60,100),(20,9,60,100),(20,11,60,100),(20,13,60,100),(20,15,60,100),(21,3,70,100),(21,5,70,100),(21,9,70,100),(21,11,70,100),(21,13,70,100),(21,15,70,100),(22,3,100,100),(22,5,100,100),(22,9,100,100),(22,11,100,100),(22,13,100,100),(22,15,100,100),(23,3,150,100),(23,5,150,100),(23,9,150,100),(23,11,150,100),(23,13,150,100),(23,15,150,100),(24,3,70,100),(24,5,70,100),(24,9,70,100),(24,11,70,100),(24,13,70,100),(24,15,70,100),(25,3,80,100),(25,5,80,100),(25,9,80,100),(25,11,80,100),(25,13,80,100),(25,15,80,100),(26,3,50,100),(26,5,50,100),(26,9,50,100),(26,11,50,100),(26,13,50,100),(26,15,50,100),(27,3,100,100),(27,5,100,100),(27,9,100,100),(27,11,100,100),(27,13,100,100),(27,15,100,100),(28,3,100,100),(28,5,100,100),(28,9,100,100),(28,11,100,100),(28,13,100,100),(28,15,100,100),(29,3,70,100),(29,5,70,100),(29,9,70,100),(29,11,70,100),(29,13,70,100),(29,15,70,100),(30,3,80,100),(30,5,80,100),(30,9,80,100),(30,11,80,100),(30,13,80,100),(30,15,80,100),(31,3,80,100),(31,5,80,100),(31,9,80,100),(31,11,80,100),(31,13,80,100),(31,15,80,100),(32,3,120,100),(32,5,120,100),(32,9,120,100),(32,11,120,100),(32,13,120,100),(32,15,120,100),(33,3,40,100),(33,5,40,100),(33,9,40,100),(33,11,40,100),(33,13,40,100),(33,15,40,100),(34,3,40,100),(34,5,40,100),(34,9,40,100),(34,11,40,100),(34,13,40,100),(34,15,40,100),(35,3,40,100),(35,5,40,100),(35,9,40,100),(35,11,40,100),(35,13,40,100),(35,15,40,100),(36,3,50,100),(36,5,50,100),(36,9,50,100),(36,11,50,100),(36,13,50,100),(36,15,50,100),(37,3,80,100),(37,5,80,100),(37,9,80,100),(37,11,80,100),(37,13,80,100),(37,15,80,100),(38,3,120,100),(38,5,120,100),(38,9,120,100),(38,11,120,100),(38,13,120,100),(38,15,120,100),(39,3,60,100),(39,5,60,100),(39,9,60,100),(39,11,60,100),(39,13,60,100),(39,15,60,100),(40,3,100,100),(40,5,100,100),(40,9,100,100),(40,11,100,100),(40,13,100,100),(40,15,100,100),(41,3,50,100),(41,5,50,100),(41,9,50,100),(41,11,50,100),(41,13,50,100),(41,15,50,100),(42,3,80,100),(42,5,80,100),(42,9,80,100),(42,11,80,100),(42,13,80,100),(42,15,80,100),(43,3,80,100),(43,5,80,100),(43,9,80,100),(43,11,80,100),(43,13,80,100),(43,15,80,100),(44,3,30,100),(44,5,30,100),(44,9,30,100),(44,11,30,100),(44,13,30,100),(44,15,30,100),(45,3,80,100),(45,5,80,100),(45,9,80,100),(45,11,80,100),(45,13,80,100),(45,15,80,100),(46,14,100,100),(47,14,80,100),(48,7,10,100),(48,10,10,100),(48,18,10,100),(48,22,10,100),(48,26,10,100),(49,7,5,100),(49,10,5,100),(49,18,5,100),(49,22,5,100),(49,26,5,100),(50,12,30,100),(50,16,30,100),(50,27,30,100),(51,12,1000,100),(51,16,1000,100),(51,27,1000,100),(52,12,3000,100),(52,16,3000,100),(52,27,3000,100),(53,2,20,100),(53,17,20,100),(53,23,20,100),(54,12,75,100),(54,16,75,100),(54,27,75,100),(55,1,3,100),(55,6,3,100),(55,7,3,100),(55,18,3,100),(55,19,3,100),(55,22,3,100),(55,24,3,100),(55,26,3,100),(56,14,100,100),(57,14,200,100);
/*!40000 ALTER TABLE `business_sales_products` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_sales_products_info`
--

DROP TABLE IF EXISTS `business_sales_products_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_sales_products_info` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) DEFAULT NULL,
  `id_type` int(11) NOT NULL,
  `id_invitem` int(11) DEFAULT NULL,
  `params` varchar(128) DEFAULT NULL,
  `price` int(11) NOT NULL DEFAULT 0,
  `level` int(11) NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`),
  KEY `id_type` (`id_type`),
  KEY `id_invitem` (`id_invitem`),
  CONSTRAINT `business_sales_products_info_ibfk_1` FOREIGN KEY (`id_type`) REFERENCES `business_sales_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_sales_products_info_ibfk_2` FOREIGN KEY (`id_invitem`) REFERENCES `inv_items` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_sales_products_info`
--

LOCK TABLES `business_sales_products_info` WRITE;
/*!40000 ALTER TABLE `business_sales_products_info` DISABLE KEYS */;
INSERT INTO `business_sales_products_info` VALUES (2,'HOTDOG',1,7,'5',5,1),(3,'PIZZA',1,12,'10',10,1),(4,'HAMBURGER',1,19,'10',10,1),(5,'BEER',2,2,'5',5,1),(6,'SODA',2,15,'5',5,1),(7,'WATER',2,17,'10',3,1),(8,'WHISKY',2,18,'2',10,1),(9,'CLOTHE_MALE_0',3,NULL,'0,0',50,1),(10,'CLOTHE_MALE_1',3,NULL,'0,1',80,1),(11,'CLOTHE_MALE_2',3,NULL,'0,2',80,1),(12,'CLOTHE_MALE_3',3,NULL,'0,3',100,1),(13,'CLOTHE_MALE_4',3,NULL,'0,4',150,1),(14,'CLOTHE_MALE_5',3,NULL,'0,5',200,1),(15,'CLOTHE_FEMALE_0',3,NULL,'1,0',50,1),(16,'CLOTHE_FEMALE_1',3,NULL,'1,1',60,1),(17,'CLOTHE_FEMALE_2',3,NULL,'1,2',60,1),(18,'CLOTHE_FEMALE_3',3,NULL,'1,3',150,1),(19,'CLOTHE_FEMALE_4',3,NULL,'1,4',60,1),(20,'CLOTHE_FEMALE_5',3,NULL,'1,5',60,1),(21,'BANDANA_1',4,1,'18903, 0, 0',70,1),(22,'BANDANA_2',4,1,'18899, 0, 0',100,1),(23,'BANDANA_3',4,1,'18897, 0, 0',150,1),(24,'CAP_1',4,3,'18933, 0, 0',70,1),(25,'CAP_2',4,3,'18960, 0, 0',80,1),(26,'CAP_2',4,3,'18934, 0, 0',50,1),(27,'GLASSES_1',4,5,'19025, 0, 0',100,1),(28,'GLASSES_2',4,5,'19138, 0, 0',100,1),(29,'GLASSES_3',4,5,'19030, 0, 0',70,1),(30,'HELMET_1',4,6,'18977, 0, 0',80,1),(31,'HELMET_2',4,6,'18979, 0, 0',80,1),(32,'HELMET_3',4,6,'18645, 0, 0',120,1),(33,'MASK_1',4,9,'19036, 0, 0',40,1),(34,'MASK_2',4,9,'19038, 0, 0',40,1),(35,'MASK_3',4,9,'19037, 0, 0',40,1),(36,'SMASK_1',4,13,'18919, 0, 0',50,1),(37,'SMASK_2',4,13,'18917, 0, 0',80,1),(38,'SMASK_3',4,13,'18914, 0, 0',120,1),(39,'SKI_MASK_1',4,14,'19163, 0, 0',60,1),(40,'WATCH_1',4,16,'19039, 0, 0',100,1),(41,'WATCH_2',4,16,'19047, 0, 0',50,1),(42,'WATCH_3',4,16,'19040, 0, 0',80,1),(43,'HAT_1',4,20,'18951, 0, 0',80,1),(44,'HAT_2',4,20,'19553, 0, 0',30,1),(45,'HAT_3',4,20,'19488, 0, 0',80,1),(46,'PHONE',5,11,NULL,100,1),(47,'GPS',5,70,NULL,80,1),(48,'ACTION_WINE',6,NULL,'22',10,1),(49,'ACTION_SPRUNK',6,NULL,'23',5,1),(50,'BRASS_KNUCKLES',7,21,'1, 1',30,1),(51,'COLT45',7,39,'22, 0',1000,1),(52,'SHOTGUN',7,42,'25, 0',3000,6),(53,'KEY_DUPLICATE',10,NULL,NULL,20,1),(54,'GENERAL_AMMO',8,NULL,'100',75,1),(55,'CIGARETTES',11,4,'CIGARETTE',3,1),(56,'WATCH_1',5,16,'19039',100,1),(57,'BOOMBOX',5,72,'2226, 40.0',200,3);
/*!40000 ALTER TABLE `business_sales_products_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_sales_types`
--

DROP TABLE IF EXISTS `business_sales_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_sales_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_sales_types`
--

LOCK TABLES `business_sales_types` WRITE;
/*!40000 ALTER TABLE `business_sales_types` DISABLE KEYS */;
INSERT INTO `business_sales_types` VALUES (1,'FOOD'),(2,'DRINK'),(3,'CLOTHES'),(4,'TOYS'),(5,'ELECTRONICS'),(6,'BAR'),(7,'WEAPONS'),(8,'AMMO'),(9,'ALL'),(10,'HARDWARE'),(11,'CIGARETTES');
/*!40000 ALTER TABLE `business_sales_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_types`
--

DROP TABLE IF EXISTS `business_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(32) DEFAULT NULL,
  `mapicon` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_types`
--

LOCK TABLES `business_types` WRITE;
/*!40000 ALTER TABLE `business_types` DISABLE KEYS */;
INSERT INTO `business_types` VALUES (1,'GENERAL_STORE',17),(2,'AMMUNATION',6),(3,'CLOTHING_STORE',45),(4,'RESTAURANT',50),(5,'BURGER',10),(6,'PIZZA',29),(7,'DISCO',48),(8,'BAR',49),(9,'ELECTRONICS',0),(10,'HARDWARE_STORE',0);
/*!40000 ALTER TABLE `business_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `business_types_stypes`
--

DROP TABLE IF EXISTS `business_types_stypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `business_types_stypes` (
  `id_business_type` int(11) NOT NULL,
  `id_business_sales_type` int(11) NOT NULL,
  PRIMARY KEY (`id_business_type`,`id_business_sales_type`),
  KEY `id_business_sales_type` (`id_business_sales_type`),
  CONSTRAINT `business_types_stypes_ibfk_1` FOREIGN KEY (`id_business_type`) REFERENCES `business_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `business_types_stypes_ibfk_2` FOREIGN KEY (`id_business_sales_type`) REFERENCES `business_sales_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `business_types_stypes`
--

LOCK TABLES `business_types_stypes` WRITE;
/*!40000 ALTER TABLE `business_types_stypes` DISABLE KEYS */;
INSERT INTO `business_types_stypes` VALUES (1,1),(1,2),(1,11),(2,7),(2,8),(3,3),(3,4),(4,1),(4,2),(4,6),(5,1),(5,2),(6,1),(6,2),(7,6),(7,11),(8,6),(8,11),(9,5),(10,10);
/*!40000 ALTER TABLE `business_types_stypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `entrances`
--

DROP TABLE IF EXISTS `entrances`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entrances` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `radio` int(11) NOT NULL DEFAULT 0,
  `audio` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `entrances`
--

LOCK TABLES `entrances` WRITE;
/*!40000 ALTER TABLE `entrances` DISABLE KEYS */;
INSERT INTO `entrances` VALUES (1,'HOSPITAL_WEST_HAVEN',0,NULL),(2,'HOSPITAL_OCEAN_VIEW',0,NULL),(3,'BANK_1',0,NULL),(4,'BANK_2',0,NULL),(5,'POLICE_WASHINGTON_BEACH',0,NULL),(6,'DOWNTOWN_POLICE',0,NULL),(7,'NORTH_POINT_MALL',0,'https://www.dropbox.com/s/t80flo0bj5uv1v8/northpoint.mp3?dl=1'),(9,'DRIVING_SCHOOL',0,NULL),(10,'TRUCKERS_1',0,NULL),(11,'REAL_ESTATE_1',0,NULL),(12,'TRUCKERS_2',0,NULL),(13,'ARMEROS',0,NULL);
/*!40000 ALTER TABLE `entrances` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `entrances_doors`
--

DROP TABLE IF EXISTS `entrances_doors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entrances_doors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_entrance` int(11) NOT NULL,
  `id_interior` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `angle` float NOT NULL DEFAULT -1,
  `time_open` int(11) NOT NULL DEFAULT 0,
  `time_close` int(11) NOT NULL DEFAULT 0,
  `mapicon_model` int(11) NOT NULL DEFAULT -1,
  `pickup_model` int(11) NOT NULL DEFAULT 0,
  `sub_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_entrance` (`id_entrance`),
  KEY `id_interior` (`id_interior`),
  KEY `fk_sub_id` (`sub_id`),
  CONSTRAINT `entrances_doors_ibfk_1` FOREIGN KEY (`id_entrance`) REFERENCES `entrances` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `entrances_doors_ibfk_2` FOREIGN KEY (`id_interior`) REFERENCES `interiors` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_sub_id` FOREIGN KEY (`sub_id`) REFERENCES `entrances_doors` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `entrances_doors`
--

LOCK TABLES `entrances_doors` WRITE;
/*!40000 ALTER TABLE `entrances_doors` DISABLE KEYS */;
INSERT INTO `entrances_doors` VALUES (1,1,183,5111.95,580.024,7.57281,269.301,0,0,22,0,NULL),(2,2,184,5860.2,67.8435,4.92645,283.546,0,0,22,0,NULL),(3,3,160,5103.04,709.048,7.84406,270,9,20,52,0,NULL),(5,4,180,6319.62,515.324,4.57729,327.511,8,22,52,0,NULL),(6,4,179,6326.09,511.328,4.59374,328.451,8,22,52,0,NULL),(7,5,172,6396.73,577.199,6.79529,320.978,0,0,30,0,NULL),(8,6,28,5343.58,1813.39,6.05875,134.856,0,0,30,0,NULL),(9,7,161,6449.9,2045.92,12.8196,180.177,0,0,-1,0,NULL),(10,7,162,6379.08,2044.61,12.7964,179.553,0,0,-1,0,NULL),(11,7,163,6478.28,2174.37,12.0874,270.586,0,0,-1,0,NULL),(12,7,164,6349.72,2173.89,12.7939,90.2729,0,0,-1,0,NULL),(13,7,165,6449.49,2306.53,12.8202,0.682136,0,0,-1,0,NULL),(14,7,166,6378.68,2307.11,12.9688,1.30881,0,0,-1,0,NULL),(16,9,135,5391.06,1699.25,5.89844,9.85842,10,20,36,0,NULL),(17,10,117,4936.81,767.513,6.54719,270.83,0,0,51,0,NULL),(18,11,186,6236.76,325.967,4.89707,63.0571,10,20,-1,0,NULL),(19,12,8,5126.21,-350.987,6.00546,154.307,0,0,51,0,NULL),(20,13,187,5137.1,1327.28,5.73024,178.813,0,0,18,0,NULL);
/*!40000 ALTER TABLE `entrances_doors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `env_areas`
--

DROP TABLE IF EXISTS `env_areas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `env_areas` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_type` int(11) NOT NULL,
  `area_type` enum('cylinder','cuboid') NOT NULL DEFAULT 'cylinder',
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `size` float NOT NULL DEFAULT 1,
  `max_x` float DEFAULT NULL,
  `max_y` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_type` (`id_type`),
  CONSTRAINT `env_areas_ibfk_1` FOREIGN KEY (`id_type`) REFERENCES `env_areas_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `env_areas`
--

LOCK TABLES `env_areas` WRITE;
/*!40000 ALTER TABLE `env_areas` DISABLE KEYS */;
INSERT INTO `env_areas` VALUES (1,1,'cylinder',6477.5,985.514,997.03,10,NULL,NULL),(2,4,'cylinder',6082,-393.296,999.078,2.5,NULL,NULL),(3,4,'cylinder',6082,-393.296,999.078,2.5,NULL,NULL),(4,4,'cylinder',6080,-396.855,999.047,2.5,NULL,NULL),(5,4,'cylinder',6086.03,-393.427,999.039,2.5,NULL,NULL),(6,4,'cylinder',6072.89,-394.55,998.867,2.5,NULL,NULL),(7,4,'cylinder',6086.16,-398.093,998.867,2.5,NULL,NULL);
/*!40000 ALTER TABLE `env_areas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `env_areas_types`
--

DROP TABLE IF EXISTS `env_areas_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `env_areas_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `env_areas_types`
--

LOCK TABLES `env_areas_types` WRITE;
/*!40000 ALTER TABLE `env_areas_types` DISABLE KEYS */;
INSERT INTO `env_areas_types` VALUES (1,'DANCE'),(2,'BED'),(3,'SEAT'),(4,'PROSTITUTE_MONEY');
/*!40000 ALTER TABLE `env_areas_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gps_cat`
--

DROP TABLE IF EXISTS `gps_cat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gps_cat` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) DEFAULT NULL,
  `icon` varchar(32) NOT NULL DEFAULT 'hud:radar_qmark',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gps_cat`
--

LOCK TABLES `gps_cat` WRITE;
/*!40000 ALTER TABLE `gps_cat` DISABLE KEYS */;
INSERT INTO `gps_cat` VALUES (1,'hospital','hud:radar_hostpital'),(2,'bank','hud:radar_cash'),(3,'police','hud:radar_police'),(4,'mechanic','hud:radar_toreno'),(5,'driving_school','hud:radar_school'),(6,'jobs','hud:radar_gangb'),(7,'real estates','mdl-1000:icon_real_estate'),(8,'business','mdl-1000:radar_propertyb');
/*!40000 ALTER TABLE `gps_cat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gps_sites`
--

DROP TABLE IF EXISTS `gps_sites`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gps_sites` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `cat_id` int(11) NOT NULL,
  `icon` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `cat_id` (`cat_id`),
  CONSTRAINT `gps_sites_ibfk_1` FOREIGN KEY (`cat_id`) REFERENCES `gps_cat` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gps_sites`
--

LOCK TABLES `gps_sites` WRITE;
/*!40000 ALTER TABLE `gps_sites` DISABLE KEYS */;
INSERT INTO `gps_sites` VALUES (1,5111.95,580.024,7.57281,1,NULL),(2,5860.2,67.8435,4.92645,1,NULL),(3,6322.99,514.347,4.58475,2,NULL),(4,5103.04,709.048,7.84406,2,NULL),(5,6396.73,577.199,6.79529,3,NULL),(6,5343.58,1813.39,6.05875,3,NULL),(7,6087.87,245.652,6.19547,4,NULL),(8,5391.06,1699.25,5.89844,5,NULL),(9,4936.81,767.513,6.54719,6,'hud:radar_truck'),(10,5004.86,1235.44,6.89219,6,'hud:radar_gangy'),(11,6236.76,325.967,4.89707,7,NULL),(12,5126.21,-350.987,6.00546,6,'hud:radar_truck'),(13,5139.63,408.315,5.70541,8,'hud:radar_diner'),(14,5031.54,361.881,5.90675,8,'hud:radar_modgarage'),(15,4977.32,621.095,5.38871,8,'hud:radar_tshirt'),(16,4940.25,1133.74,5.95259,8,'hud:radar_pizza'),(17,4919.14,1135.22,5.67594,8,'hud:radar_tshirt'),(18,5147.64,964.025,5.5665,8,'hud:radar_diner'),(19,4965.92,203.55,7.55,8,'hud:radar_impound'),(20,5402.69,1701.62,5.83891,8,'hud:radar_datedrink'),(21,5115.5,1846.34,5.58478,8,'hud:radar_pizza'),(22,5081.49,1935.29,5.53688,8,'hud:radar_tshirt'),(23,5140.05,1908.71,5.64531,8,'hud:radar_chicken'),(24,5122.85,2314.98,5.86438,8,'hud:radar_tshirt'),(25,5323.49,2251,5.53687,8,'hud:radar_ammugun'),(26,5532.01,2122.47,5.53375,8,'hud:radar_tshirt'),(27,6471.11,2173.63,1219.03,8,'hud:radar_savegame'),(28,6413.95,2091.7,1219.83,8,'hud:radar_tshirt'),(29,6368.48,2106.65,1213.65,8,'hud:radar_ammugun'),(30,6368.6,2128.21,1213.53,8,'hud:radar_modgarage'),(31,6446.36,1823.47,7.41594,8,'hud:radar_diner'),(32,6532.22,1819.85,5.70941,8,'hud:radar_burgershot'),(33,6430.34,1122.29,5.59608,8,'hud:radar_pizza'),(34,6490.29,971.049,5.94906,8,'hud:radar_datedisco'),(35,6197.9,570.095,5.52744,8,'hud:radar_modgarage'),(36,6124.31,145.045,4.89911,8,'hud:radar_diner'),(37,6086.59,59.9482,4.93177,8,'hud:radar_pizza'),(38,6096.68,-420.666,4.89437,8,'hud:radar_datedisco'),(39,5137.1,1327.28,5.73024,6,'hud:radar_emmetgun'),(40,5940.11,-431.322,4.96858,8,'hud:radar_ammugun');
/*!40000 ALTER TABLE `gps_sites` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interiors`
--

DROP TABLE IF EXISTS `interiors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `interiors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `interiorid` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `angle` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interiors`
--

LOCK TABLES `interiors` WRITE;
/*!40000 ALTER TABLE `interiors` DISABLE KEYS */;
INSERT INTO `interiors` VALUES (1,'Four Dragons\' Managerial Suite',11,2003.12,1015.19,33.008,351.579),(2,'Ganton Gym',5,772.365,-4.98912,1000.73,358.967),(3,'Brothel',3,975.126,-8.56176,1001.15,91.8833),(4,'Brothel2',3,966.13,-53.2109,1001.12,86.814),(5,'Inside Track Betting',3,834.494,7.39441,1004.19,86.9592),(6,'Blastin\' Fools Records',3,1038.15,-3.75163,1001.28,356.775),(7,'The Big Spread Ranch',3,1212.11,-26.0423,1000.95,177.682),(8,'Warehouse 1',18,1310.12,3.96735,1002.49,90),(9,'Warehouse 2',1,1415.93,3.89931,1000.93,93.516),(10,'B Dup\'s Apartment',3,1528.92,-11.555,1002.1,84.1958),(11,'B Dup\'s Crack Palace',2,1521.11,-47.9559,1002.13,269.49),(12,'Wheel Arch Angels',3,610.664,-125.464,997.992,269.579),(13,'OG Loc\'s House',3,513.981,-7.53223,1001.57,179.058),(14,'Barber Shop',3,418.617,-84.1901,1001.8,351.384),(15,'Planning Department',3,390.455,173.686,1008.38,87.3741),(16,'Las Venturas Police Department',3,288.716,167.364,1007.17,358.746),(17,'Pro-Laps',3,207.004,-140.094,1003.51,359.515),(18,'Sex Shop',3,-100.369,-25.0328,1000.72,359.486),(19,'Las Venturas Tattoo parlor',3,-204.382,-44.2988,1002.27,357.136),(20,'Lost San Fierro Tattoo parlor',17,-204.318,-9.07874,1002.27,359.081),(21,'24/7 (version 1)',17,-25.9427,-187.748,1003.55,3.39754),(22,'Diner 1',5,458.794,-111.456,999.663,1.25195),(23,'Pizza Stack',5,372.234,-133.258,1001.49,358.662),(24,'Rusty Brown\'s Donuts',17,377.084,-193.001,1000.64,353.826),(25,'Ammu-nation',7,315.829,-143.564,999.602,356.356),(26,'Victim',5,227.338,-8.05033,1002.21,88.8365),(27,'Loco Low Co',2,610.553,-76.3667,997.992,271.239),(28,'San Fierro Police Department',10,246.508,107.641,1003.22,358.56),(29,'24/7 (version 2 - large)',10,6.1344,-31.6549,1003.55,357.616),(30,'Below The Belt Gym (Las Venturas)',7,773.981,-78.7481,1000.66,2.16374),(31,'Transfenders',1,626.849,-11.9899,1000.92,91.5888),(32,'World of Coq',1,447.137,-7.4472,1000.73,180.263),(33,'Ammu-nation (version 2)',1,285.408,-41.5381,1001.52,357.088),(34,'SubUrban',1,203.755,-50.3672,1001.8,356.991),(35,'Denise\'s Bedroom',1,243.892,304.942,999.148,272.684),(36,'Helena\'s Barn',3,293.116,310.111,999.148,89.7092),(37,'Barbara\'s Love nest',5,322.291,302.639,999.148,356.174),(38,'San Fierro Garage',1,-2036.1,179.118,28.8429,91.8472),(39,'Oval Stadium',1,-1401.77,106.738,1032.27,90.2571),(40,'8-Track Stadium',7,-1393.65,-252.919,1043.62,221.208),(41,'The Pig Pen (strip club 2)',2,1204.76,-13.8471,1000.92,356.738),(42,'Four Dragons',10,2018.97,1017.9,996.875,88.9713),(43,'Liberty City',1,-741.961,493.186,1371.98,68.9477),(44,'Ryder\'s house',2,2468.73,-1698.56,1013.51,86.0984),(45,'Sweet\'s House',1,2524.76,-1679.37,1015.5,263.228),(46,'RC Battlefield',10,-1129.84,1057.81,1346.41,268.875),(47,'The Johnson House',3,2495.95,-1692.19,1014.74,176.024),(48,'Burger shot',10,363.082,-74.955,1001.51,310.782),(49,'Caligula\'s Casino',1,2233.94,1714.36,1012.38,185.626),(50,'Katie\'s Lovenest',2,266.826,304.934,999.148,271.604),(51,'Barber Shop 2 (Reece\'s)',2,411.667,-23.0599,1001.8,349.35),(52,'Angel Pine Trailer',2,1.96018,-3.17859,999.428,84.3662),(53,'24/7 (version 3)',18,-30.9611,-91.6759,1003.55,5.43599),(54,'Zip',18,161.456,-97.1079,1001.8,0.646192),(55,'The Pleasure Domes',3,-2636.69,1402.66,906.461,0.263929),(56,'Madd Dogg\'s Mansion',5,1260.74,-785.38,1091.91,291.438),(57,'Big Smoke\'s Crack Palace',2,2541.83,-1304.03,1025.07,268.785),(58,'Burning Desire Building',5,2352.84,-1180.87,1027.98,87.9156),(59,'Wu-Zi Mu\'s',1,-2158.72,642.816,1052.38,177.068),(60,'Abandoned AC tower',10,419.894,2537.12,67.6537,90),(61,'Wardrobe/Changing room',14,254.269,-41.5882,1002.03,266.029),(62,'Didier Sachs',14,204.327,-168.751,1000.52,347.848),(63,'Casino (Redsands West)',12,1133.12,-15.3909,1000.68,355.414),(64,'Kickstart Stadium',14,-1420.58,1616.13,1052.53,263.635),(65,'Club',17,493.351,-24.6838,1000.68,354.364),(66,'Atrium',18,1727.17,-1637.96,20.223,174.456),(67,'Los Santos Tattoo Parlor',16,-204.414,-27.2424,1002.27,355.244),(68,'Safe House group 1',5,2233.58,-1115.1,1050.88,357.769),(69,'Safe House group 2',6,1211.25,1049.02,359.941,170.934),(70,'Safe House group 3',9,2317.74,-1026.66,1050.22,357.44),(71,'Safe House group 4',10,2259.48,-1135.87,1050.64,268.571),(72,'Sherman Dam',17,-959.706,1955.96,9,177.338),(73,'24/7 (version 4)',16,-25.9361,-141.239,1003.55,356.834),(74,'Jefferson Motel',15,2214.49,-1150.49,1025.8,267.843),(75,'Jet Interior',1,1.69159,23.3449,1199.59,357.977),(76,'The Welcome Pump',1,681.44,-451.51,-25.6172,178.188),(77,'Burglary House X1',3,235.31,1187.01,1080.26,357.967),(78,'Burglary House X2',2,226.566,1239.99,1082.14,89.5055),(79,'Burglary House X3',1,223.11,1287.18,1082.14,358.124),(80,'Burglary House X4',5,226.52,1114.36,1080.99,266.928),(81,'Binco',15,207.764,-111.1,1005.13,358.838),(82,'4 Burglary houses',15,295.201,1472.42,1080.26,357.201),(83,'Blood Bowl Stadium',15,-1417.89,932.448,1041.53,0.700811),(84,'Budget Inn Motel Room',12,446.749,507.134,1001.42,358.308),(85,'Palamino Bank',0,2304.9,-16.1007,26.7422,267.684),(86,'Palamino Diner',0,2333.29,6.16101,26.4934,87.7077),(87,'Dillimore Gas Station',0,662.744,-573.466,16.3359,268.584),(88,'Lil\' Probe Inn',18,-229.132,1401.15,27.7656,267.434),(89,'Torreno\'s Ranch',0,-688.15,942.083,13.6328,177.657),(90,'Zombotech - lobby area',0,-1920.97,716.415,46.5625,172.789),(91,'Crypt in LS cemetery (temple)',0,821.356,-1102.77,25.7969,90.0819),(92,'Blueberry Liquor Store',0,254.597,-60.6487,1.57031,359.636),(93,'Pair of Burglary Houses',2,447.169,1397.31,1084.3,356.644),(94,'Crack Den',5,226.399,1114.38,1080.99,266.879),(95,'Burglary House X11',5,226.399,1114.33,1080.99,267.261),(96,'Burglary House X12',4,260.903,1284.46,1080.26,356.923),(97,'Ammu-nation (version 3)',4,285.757,-86.537,1001.52,356.432),(98,'Jay\'s Diner',4,460.255,-88.6738,999.555,87.1716),(99,'24/7 (version 5)',4,-27.3768,-31.66,1003.56,357.59),(100,'Warehouse 3 	 ',0,2133.76,-2276.9,20.6719,312.836),(101,'Michelle\'s Love Nest*',4,309.457,311.403,1003.3,174.293),(102,'Burglary House X14',10,24.0159,1340.26,1084.38,358.704),(103,'Sindacco Abatoir',1,964.831,2160.08,1011.03,87.5455),(104,'K.A.C.C. Military Fuels Depot',0,2550.22,2823.49,10.8203,270.92),(105,'Area 69',0,214.153,1873.45,13.1406,177.794),(106,'Burglary House X13',4,221.975,1140.68,1082.61,357.286),(107,'Unused Safe House',12,2324.36,-1149.28,1050.71,357.294),(108,'Millie\'s Bedroom',6,343.821,304.993,999.148,267.171),(109,'Barber Shop',12,412.05,-54.3442,1001.9,357.854),(110,'Dirtbike Stadium',4,-1423.56,-663.848,1059.74,84.4987),(111,'Cobra Gym',6,774.164,-50.3749,1000.59,357.973),(112,'Los Santos Police Department',6,246.781,62.4248,1003.64,355.62),(113,'Los Santos Airport',14,-1884.26,59.5762,1055.15,269.259),(114,'Burglary House X15',4,-260.636,1456.7,1084.37,86.8156),(115,'Burglary House X16',5,22.8991,1403.43,1084.44,357.252),(116,'Burglary House X17',5,140.202,1366.14,1083.86,358.851),(117,'Bike School',3,1494.47,1303.85,1093.29,356.491),(118,'Francis International Airport',14,-1812.46,-57.2841,1058.96,0.583162),(119,'Vice Stadium',16,-1401.07,1265.37,1039.87,178.648),(120,'Burglary House X18',6,234.177,1063.82,1084.21,357.112),(121,'Burglary House X19',6,-68.8237,1351.3,1080.21,357.953),(122,'Zero\'s RC Shop',6,-2240.68,137.051,1035.41,266.273),(123,'Ammu-nation (version 4)',6,296.861,-111.929,1001.52,358.204),(124,'Ammu-nation (version 5)',6,316.354,-170.192,999.594,357.634),(125,'Burglary House X20',15,-283.54,1471.1,1084.38,86.972),(126,'24/7 (version 6)',6,-27.3409,-58.1665,1003.55,356.815),(127,'Secret Valley Diner',6,441.687,-49.5601,999.863,181.819),(128,'Rosenberg\'s Office in Caligulas',2,2187.2,1628.77,1043.41,89.9041),(129,'Fanny Batter\'s Whore House',6,744.619,1436.43,1102.7,336.579),(130,'Colonel Furhberger\'s',8,2807.58,-1174.65,1025.57,350.583),(131,'Cluckin\' Bell',9,365.026,-11.6211,1001.85,354.57),(132,'The Camel\'s Toe Safehouse',1,2218.28,-1076.11,1050.48,86.5802),(133,'Caligula\'s Roof',1,2266.32,1647.35,1084.23,265.9),(134,'Old Venturas Strip Casino',2,2237.46,-1081.27,1049.02,356.176),(135,'Driving School',3,-2029.64,-119.397,1035.17,0),(136,'Verdant Bluffs Safehouse',8,2365.26,-1135.44,1050.88,357.371),(137,'Bike School',0,1168.64,1362.33,10.9293,178.041),(138,'Andromada',9,315.897,973.843,1961.47,1.02374),(139,'Four Dragons\' Janitor\'s Office',10,1889.96,1017.75,31.8828,267.402),(140,'Bar',11,501.994,-68.0152,998.758,176.709),(141,'Burglary House X21',8,-42.5758,1405.59,1084.43,359.148),(142,'Willowfield Safehouse',11,2283.31,1139.31,1050.9,19.7032),(143,'Burglary House X22',9,83.1361,1322.38,1083.87,352.4),(144,'Burglary House X23',9,260.836,1237.43,1084.26,357.259),(145,'Otto\'s Autos',0,-1644.84,1204.81,7.25,61.3528),(146,'Wang Cars',0,-1964.1,293.932,35.4688,268.168),(150,'Scarfaceinterior',0,6306.95,933.635,1048.81,0),(151,'Hardware Store Washington Beach',0,6201.99,587.149,999.727,180),(152,'Ocean View Hotel',0,6228.71,-227.186,999.922,75),(153,'Malibu Club Door 1',0,6490.03,973.854,998.531,45),(154,'Malibu Club Door 2',0,6487.55,971.518,998.531,45),(155,'Ammunation',0,5940.5,-429.63,997.087,90),(156,'Ammunation Downtown',0,5318.3,2251.28,997.179,90),(157,'Mansion Principal Door',0,5621.46,494.428,996.133,180),(158,'Mansion Terrace Door',0,5663.56,476.213,1012.12,270),(159,'Mansion Pool Door',0,5672.6,471.018,988.161,270),(160,'El Banco Corrupto Grande',0,5101.99,708.993,994.023,90),(161,'North Point Mall Door 1',0,6448.64,2053.69,1213.64,0),(162,'North Point Mall Door 2',0,6379.67,2052.79,1213.65,0),(163,'North Point Mall Door 3',0,6470.98,2173.61,1212.78,90),(164,'North Point Mall Door 4',0,6357.09,2174.61,1213.48,270),(165,'North Point Mall Door 5',0,6448.21,2299.29,1213.48,180),(166,'North Point Mall Door 6',0,6379.62,2299.88,1213.61,180),(167,'Pole Position Club',0,6096.09,-404.722,998.031,30),(168,'Hardware Store Mall',0,6367.55,2128.26,997.609,90),(169,'Hardware Store Little Havana',0,5033.35,354.851,994.56,90),(170,'Ken Rosenburg\'s office',0,6121.11,215.509,1000,250),(171,'Greasy Chopper (Biker Bar)',0,5402.77,1700.65,995.992,180),(172,'Washington Beach Police HQ',0,6396.04,576.625,996.383,135),(173,'Auntie Poulet\'s',0,5037.27,1197.05,997.695,0),(174,'Print Works',0,4935.41,767.392,998.069,90),(175,'GASH Door 1',0,6407.9,2082.15,994.421,270),(176,'GASH Door 2',0,6407.75,2082.1,1000.73,270),(177,'Tarbrush Café',0,6464.65,2058.89,997.458,220),(178,'Café Robina',0,4830.08,441.309,1001.29,180),(179,'Banco Texturizado Door 1',0,1450.55,-1048.53,2725.88,0),(180,'Banco Texturizado Door 2',0,1458,-1048.53,2725.88,0),(183,'Hospital WestHaven',1,1169.62,-1356.62,2423.05,0),(184,'Hospital OceanView',1,2383.19,2665.66,8001.15,180),(185,'HOTEL_1',0,1404.88,-32.6355,1000.93,79.7878),(186,'OFFICE_1',0,30.0673,42.7068,1000.09,181.182),(187,'ArmeroInt',2,2577.14,-1290,1044.12,88.556),(188,'caravanaD1',2,0.256313,-3.7858,994.439,357.572),(189,'caravanaD2',2,0.784592,4.92316,994.439,183.984);
/*!40000 ALTER TABLE `interiors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inv_items`
--

DROP TABLE IF EXISTS `inv_items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inv_items` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) NOT NULL,
  `icon_name` varchar(32) NOT NULL DEFAULT 'icon_undefinied',
  `name` varchar(24) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `type` (`type`),
  CONSTRAINT `inv_items_ibfk_1` FOREIGN KEY (`type`) REFERENCES `inv_items_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inv_items`
--

LOCK TABLES `inv_items` WRITE;
/*!40000 ALTER TABLE `inv_items` DISABLE KEYS */;
INSERT INTO `inv_items` VALUES (1,6,'icon_bandana','BANDANA'),(2,3,'icon_beer','BEER'),(3,6,'icon_cap','CAP'),(4,12,'icon_cigarette','CIGARETTE'),(5,6,'icon_glasses','GLASSES'),(6,6,'icon_helmet','HELMET'),(7,4,'icon_hotdog','HOTDOG'),(8,1,'icon_property_key','PROPERTY_KEY'),(9,6,'icon_mask','MASK'),(10,2,'icon_property_master_key','PROPERTY_MASTER_KEY'),(11,7,'icon_phone','PHONE'),(12,4,'icon_pizza','PIZZA'),(13,6,'icon_smask','SMASK'),(14,6,'icon_ski_mask','SKI_MASK'),(15,3,'icon_soda','SODA'),(16,6,'icon_watch','WATCH'),(17,3,'icon_water','WATER'),(18,3,'icon_whisky','WHISKY'),(19,4,'icon_burger','HAMBURGER'),(20,6,'icon_hat','HAT'),(21,5,'icon_weapon1','BRASS_KNUCKLES'),(22,5,'icon_weapon2','GOLF_CLUB'),(23,5,'icon_weapon3','NIGHTSTICK'),(24,5,'icon_weapon4','KNIFE'),(25,5,'icon_weapon5','BASEBALL_BAT'),(26,5,'icon_weapon6','SHOVEL'),(27,5,'icon_weapon7','POOL_CUE'),(28,5,'icon_weapon8','KATANA'),(29,5,'icon_weapon9','CHAINSAW'),(30,5,'icon_weapon10','PURPLE_DILDO'),(31,5,'icon_weapon11','DILDO'),(32,5,'icon_weapon12','VIBRATOR'),(33,5,'icon_weapon13','SILVER_VIBRATOR'),(34,5,'icon_weapon14','FLOWERS'),(35,5,'icon_weapon15','CANE'),(36,5,'icon_weapon16','GRENADE'),(37,5,'icon_weapon17','TEAR_GAS'),(38,5,'icon_weapon18','MOLOTOV_COCKTAIL'),(39,5,'icon_weapon22','COLT45'),(40,5,'icon_weapon23','SILENCED_COLT45'),(41,5,'icon_weapon24','DESERT_EAGLE'),(42,5,'icon_weapon25','SHOTGUN'),(43,5,'icon_weapon26','SAWNOFF_SHOTGUN'),(44,5,'icon_weapon27','COMBAT_SHOTGUN'),(45,5,'icon_weapon28','UZI'),(46,5,'icon_weapon29','MP5'),(47,5,'icon_weapon30','AK_47'),(48,5,'icon_weapon31','M4'),(49,5,'icon_weapon32','TEC_9'),(50,5,'icon_weapon33','COUNTRY_RIFLE'),(51,5,'icon_weapon34','SNIPER_RIFLE'),(52,5,'icon_weapon35','RPG'),(53,5,'icon_weapon36','HS_ROCKET'),(54,5,'icon_weapon37','FLAMETHROWER'),(55,5,'icon_weapon38','MINIGUN'),(56,5,'icon_weapon39','SATCHEL_CHARGE'),(57,5,'icon_weapon40','DETONATOR'),(58,5,'icon_weapon41','SPRAYCAN'),(59,5,'icon_weapon42','FIRE_EXTINGUISHER'),(60,5,'icon_weapon43','CAMERA'),(61,5,'icon_weapon46','PARACHUTE'),(62,1,'icon_vehicle_key','VEHICLE_KEY'),(63,2,'icon_vehicle_master_key','VEHICLE_MASTER_KEY'),(64,1,'icon_business_key','BUSINESS_KEY'),(65,2,'icon_business_master_key','BUSINESS_MASTER_KEY'),(66,8,'icon_driver_license','DRIVER_LICENSE'),(67,9,'icon_id','CHARACTER_ID'),(68,10,'icon_vehicle_rent_key','VEHICLE_RENT_KEY'),(69,10,'icon_property_rent_key','PROPERTY_RENT_KEY'),(70,11,'icon_gps','GPS'),(71,8,'icon_gun_license','GUN_LICENSE'),(72,13,'icon_boombox','BOOMBOX');
/*!40000 ALTER TABLE `inv_items` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inv_items_types`
--

DROP TABLE IF EXISTS `inv_items_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inv_items_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL,
  `multipliable` int(11) NOT NULL DEFAULT 0,
  `max_multiplied` int(11) NOT NULL DEFAULT 1,
  `inv_unique` tinyint(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inv_items_types`
--

LOCK TABLES `inv_items_types` WRITE;
/*!40000 ALTER TABLE `inv_items_types` DISABLE KEYS */;
INSERT INTO `inv_items_types` VALUES (1,'KEY',1,3,0),(2,'MASTER_KEY',0,1,0),(3,'DRINK',1,10,0),(4,'FOOD',1,10,0),(5,'WEAPON',0,1,0),(6,'TOY',0,1,0),(7,'PHONE',0,1,1),(8,'LICENSE',0,1,0),(9,'ID',0,1,1),(10,'RENT_KEY',0,1,0),(11,'GPS',0,1,1),(12,'CIGARETTE',1,10,0),(13,'BOOMBOX',0,1,1);
/*!40000 ALTER TABLE `inv_items_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jobs`
--

DROP TABLE IF EXISTS `jobs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jobs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) DEFAULT NULL,
  `icon` varchar(32) DEFAULT NULL,
  `mapicon` int(11) DEFAULT NULL,
  `min_level` int(11) NOT NULL DEFAULT 1,
  `max_payment` int(11) NOT NULL DEFAULT 1000,
  `exp_per_job` int(11) NOT NULL DEFAULT 1,
  `exp_for_next_level` int(11) NOT NULL DEFAULT 10,
  `percentage_payment_level` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jobs`
--

LOCK TABLES `jobs` WRITE;
/*!40000 ALTER TABLE `jobs` DISABLE KEYS */;
INSERT INTO `jobs` VALUES (1,'TAXI','mdl-1000:icon_taxi',60,1,1000,0,0,0),(2,'TRUCKER','hud:radar_truck',51,1,500,1,10,1),(3,'GUNSMITH',NULL,NULL,1,100,1,50,1);
/*!40000 ALTER TABLE `jobs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `jobs_points`
--

DROP TABLE IF EXISTS `jobs_points`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `jobs_points` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_job` int(11) NOT NULL,
  `min_job_level` int(11) NOT NULL DEFAULT 1,
  `actor_skin` int(11) DEFAULT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `angle` float NOT NULL DEFAULT 0,
  `base_payment` int(11) NOT NULL DEFAULT 0,
  `id_entrance_door` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_job` (`id_job`),
  KEY `id_entrance_door` (`id_entrance_door`),
  CONSTRAINT `jobs_points_ibfk_1` FOREIGN KEY (`id_job`) REFERENCES `jobs` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `jobs_points_ibfk_2` FOREIGN KEY (`id_entrance_door`) REFERENCES `entrances_doors` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `jobs_points`
--

LOCK TABLES `jobs_points` WRITE;
/*!40000 ALTER TABLE `jobs_points` DISABLE KEYS */;
INSERT INTO `jobs_points` VALUES (1,1,1,262,5004.86,1235.44,6.89219,0,15,NULL),(2,2,1,7,1490.29,1305.6,1093.3,270,60,17),(3,2,5,66,1298.14,1.91165,1001.02,180,110,19),(4,3,1,6,2569.28,-1297.84,1044.12,90,50,20);
/*!40000 ALTER TABLE `jobs_points` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player`
--

DROP TABLE IF EXISTS `player`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL,
  `salt` varchar(16) NOT NULL,
  `passwd` varchar(65) NOT NULL,
  `ip` varchar(16) NOT NULL,
  `register_date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_connection` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `time_playing` int(11) NOT NULL DEFAULT 0,
  `money` int(11) NOT NULL DEFAULT 0,
  `level` int(11) NOT NULL DEFAULT 1,
  `reputation` float NOT NULL DEFAULT 1,
  `lang` varchar(3) NOT NULL,
  `email` varchar(64) NOT NULL,
  `connected` int(11) NOT NULL DEFAULT 0,
  `playerid` int(11) NOT NULL DEFAULT 0,
  `admin_level` int(11) NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `angle` float NOT NULL DEFAULT 0,
  `interiorid` int(11) NOT NULL DEFAULT 0,
  `worldid` int(11) NOT NULL DEFAULT 0,
  `health` float NOT NULL DEFAULT 100,
  `armour` float NOT NULL DEFAULT 0,
  `gender` int(11) NOT NULL DEFAULT 0,
  `hungry` float NOT NULL DEFAULT 0,
  `thirst` float NOT NULL DEFAULT 0,
  `world_state` int(11) NOT NULL DEFAULT 0,
  `world_state_index` int(11) NOT NULL DEFAULT -1,
  `world_state_extra_index` int(11) NOT NULL DEFAULT -1,
  `world_state_id` int(11) NOT NULL DEFAULT 0,
  `world_state_extra_id` int(11) NOT NULL DEFAULT 0,
  `bank_money` int(11) NOT NULL DEFAULT 0,
  `kills` int(11) NOT NULL DEFAULT 0,
  `deaths` int(11) NOT NULL DEFAULT 0,
  `ar_width` int(11) NOT NULL DEFAULT 16,
  `ar_height` int(11) NOT NULL DEFAULT 9,
  `gps_minimap` tinyint(1) NOT NULL DEFAULT 0,
  `gps_location` tinyint(1) NOT NULL DEFAULT 1,
  `gps_route` int(11) NOT NULL DEFAULT 1,
  `gps_objectives` int(11) NOT NULL DEFAULT 1,
  `gps_properties` int(11) NOT NULL DEFAULT 1,
  `gps_business` int(11) NOT NULL DEFAULT 1,
  `gps_vehicles` int(11) NOT NULL DEFAULT 1,
  `phone_number` int(11) NOT NULL DEFAULT 0,
  `phone_on` tinyint(1) NOT NULL DEFAULT 1,
  `clothing_character` int(11) NOT NULL DEFAULT 1,
  `clothing_clothe` int(11) NOT NULL DEFAULT 0,
  `last_character_change` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `help_channel` int(11) NOT NULL DEFAULT 1,
  `pcu_ip` varchar(16) NOT NULL,
  `pcu_last_login` varchar(16) NOT NULL,
  `admin_messages` int(11) NOT NULL DEFAULT 1,
  `tutorial` int(11) NOT NULL DEFAULT 0,
  `mph` tinyint(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player`
--

LOCK TABLES `player` WRITE;
/*!40000 ALTER TABLE `player` DISABLE KEYS */;
/*!40000 ALTER TABLE `player` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_achievements`
--

DROP TABLE IF EXISTS `player_achievements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_achievements` (
  `id_player` int(11) NOT NULL,
  `id_achievement` int(11) NOT NULL,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id_player`,`id_achievement`),
  KEY `id_achievement` (`id_achievement`),
  CONSTRAINT `player_achievements_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_achievements_ibfk_2` FOREIGN KEY (`id_achievement`) REFERENCES `achievements` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_achievements`
--

LOCK TABLES `player_achievements` WRITE;
/*!40000 ALTER TABLE `player_achievements` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_achievements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_admin_history`
--

DROP TABLE IF EXISTS `player_admin_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_admin_history` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_admin` int(11) DEFAULT NULL,
  `id_player` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `reason` varchar(256) DEFAULT NULL,
  `date` datetime NOT NULL,
  `expire_date` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_admin` (`id_admin`),
  KEY `id_player` (`id_player`),
  KEY `type` (`type`),
  CONSTRAINT `player_admin_history_ibfk_1` FOREIGN KEY (`id_admin`) REFERENCES `player` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `player_admin_history_ibfk_2` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_admin_history_ibfk_3` FOREIGN KEY (`type`) REFERENCES `admin_restrictions_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_admin_history`
--

LOCK TABLES `player_admin_history` WRITE;
/*!40000 ALTER TABLE `player_admin_history` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_admin_history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_admin_restrictions`
--

DROP TABLE IF EXISTS `player_admin_restrictions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_admin_restrictions` (
  `id_player` int(11) NOT NULL,
  `ip` varchar(16) DEFAULT NULL,
  `id_history` int(11) NOT NULL,
  PRIMARY KEY (`id_player`),
  KEY `id_history` (`id_history`),
  CONSTRAINT `player_admin_restrictions_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_admin_restrictions_ibfk_2` FOREIGN KEY (`id_history`) REFERENCES `player_admin_history` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_admin_restrictions`
--

LOCK TABLES `player_admin_restrictions` WRITE;
/*!40000 ALTER TABLE `player_admin_restrictions` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_admin_restrictions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_bank_movements`
--

DROP TABLE IF EXISTS `player_bank_movements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_bank_movements` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL DEFAULT current_timestamp(),
  `from_id` int(11) NOT NULL,
  `to_id` int(11) NOT NULL,
  `from_name` varchar(24) NOT NULL,
  `to_name` varchar(24) NOT NULL,
  `amount` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `from_id` (`from_id`),
  KEY `to_id` (`to_id`),
  CONSTRAINT `player_bank_movements_ibfk_1` FOREIGN KEY (`from_id`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_bank_movements_ibfk_2` FOREIGN KEY (`to_id`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_bank_movements`
--

LOCK TABLES `player_bank_movements` WRITE;
/*!40000 ALTER TABLE `player_bank_movements` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_bank_movements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_clothes`
--

DROP TABLE IF EXISTS `player_clothes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_clothes` (
  `id_player` int(11) NOT NULL,
  `id_clothe` int(11) NOT NULL,
  PRIMARY KEY (`id_player`,`id_clothe`),
  CONSTRAINT `player_clothes_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_clothes`
--

LOCK TABLES `player_clothes` WRITE;
/*!40000 ALTER TABLE `player_clothes` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_clothes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_gps_cats`
--

DROP TABLE IF EXISTS `player_gps_cats`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_gps_cats` (
  `id_player` int(11) NOT NULL,
  `id_cat` int(11) NOT NULL,
  `enabled` tinyint(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id_player`,`id_cat`),
  KEY `id_cat` (`id_cat`),
  CONSTRAINT `player_gps_cats_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_gps_cats_ibfk_2` FOREIGN KEY (`id_cat`) REFERENCES `gps_cat` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_gps_cats`
--

LOCK TABLES `player_gps_cats` WRITE;
/*!40000 ALTER TABLE `player_gps_cats` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_gps_cats` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_inv`
--

DROP TABLE IF EXISTS `player_inv`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_inv` (
  `player_id` int(11) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `item_id` int(11) NOT NULL,
  `amount` int(11) NOT NULL DEFAULT 1,
  `params` varchar(128) DEFAULT NULL,
  `position` int(11) NOT NULL DEFAULT -1,
  PRIMARY KEY (`id`),
  KEY `player_id` (`player_id`),
  KEY `item_id` (`item_id`),
  CONSTRAINT `player_inv_ibfk_1` FOREIGN KEY (`player_id`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_inv_ibfk_2` FOREIGN KEY (`item_id`) REFERENCES `inv_items` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_inv`
--

LOCK TABLES `player_inv` WRITE;
/*!40000 ALTER TABLE `player_inv` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_inv` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_jobs_info`
--

DROP TABLE IF EXISTS `player_jobs_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_jobs_info` (
  `id_player` int(11) NOT NULL,
  `id_job` int(11) NOT NULL,
  `level` int(11) NOT NULL DEFAULT 1,
  `exp` int(11) NOT NULL DEFAULT 1,
  `jobs` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id_player`,`id_job`),
  KEY `id_job` (`id_job`),
  CONSTRAINT `player_jobs_info_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `player_jobs_info_ibfk_2` FOREIGN KEY (`id_job`) REFERENCES `jobs` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_jobs_info`
--

LOCK TABLES `player_jobs_info` WRITE;
/*!40000 ALTER TABLE `player_jobs_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_jobs_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_phone_book`
--

DROP TABLE IF EXISTS `player_phone_book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_phone_book` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_player` int(11) NOT NULL,
  `contact` varchar(24) NOT NULL,
  `number` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_player` (`id_player`),
  CONSTRAINT `player_phone_book_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_phone_book`
--

LOCK TABLES `player_phone_book` WRITE;
/*!40000 ALTER TABLE `player_phone_book` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_phone_book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_toys`
--

DROP TABLE IF EXISTS `player_toys`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_toys` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_player` int(11) NOT NULL,
  `inv_itemid` int(11) NOT NULL DEFAULT 0,
  `attached` tinyint(1) NOT NULL DEFAULT 0,
  `modelid` int(11) NOT NULL,
  `bone` int(11) NOT NULL DEFAULT 1,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `rx` float NOT NULL DEFAULT 0,
  `ry` float NOT NULL DEFAULT 0,
  `rz` float NOT NULL DEFAULT 0,
  `sx` float NOT NULL DEFAULT 1,
  `sy` float NOT NULL DEFAULT 1,
  `sz` float NOT NULL DEFAULT 1,
  `color1` int(11) NOT NULL DEFAULT 0,
  `color2` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `id_player` (`id_player`),
  CONSTRAINT `player_toys_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_toys`
--

LOCK TABLES `player_toys` WRITE;
/*!40000 ALTER TABLE `player_toys` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_toys` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_toys_clothes`
--

DROP TABLE IF EXISTS `player_toys_clothes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_toys_clothes` (
  `id_toy` int(11) NOT NULL,
  `id_clothe` int(11) NOT NULL,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `rx` float NOT NULL DEFAULT 0,
  `ry` float NOT NULL DEFAULT 0,
  `rz` float NOT NULL DEFAULT 0,
  `sx` float NOT NULL DEFAULT 1,
  `sy` float NOT NULL DEFAULT 1,
  `sz` float NOT NULL DEFAULT 1,
  PRIMARY KEY (`id_toy`,`id_clothe`),
  CONSTRAINT `player_toys_clothes_ibfk_1` FOREIGN KEY (`id_toy`) REFERENCES `player_toys` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_toys_clothes`
--

LOCK TABLES `player_toys_clothes` WRITE;
/*!40000 ALTER TABLE `player_toys_clothes` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_toys_clothes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_weapons`
--

DROP TABLE IF EXISTS `player_weapons`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player_weapons` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_player` int(11) NOT NULL,
  `carried` int(11) NOT NULL DEFAULT 0,
  `weaponid` int(11) NOT NULL,
  `ammo` int(11) NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`),
  KEY `id_player` (`id_player`),
  CONSTRAINT `player_weapons_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_weapons`
--

LOCK TABLES `player_weapons` WRITE;
/*!40000 ALTER TABLE `player_weapons` DISABLE KEYS */;
/*!40000 ALTER TABLE `player_weapons` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `properties`
--

DROP TABLE IF EXISTS `properties`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `properties` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `price` int(11) NOT NULL DEFAULT 0,
  `level` int(11) NOT NULL DEFAULT 1,
  `rent` int(11) NOT NULL DEFAULT 0,
  `rent_expire_date` datetime DEFAULT NULL,
  `id_player` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_player` (`id_player`),
  CONSTRAINT `properties_ibfk_1` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `properties`
--

LOCK TABLES `properties` WRITE;
/*!40000 ALTER TABLE `properties` DISABLE KEYS */;
INSERT INTO `properties` VALUES (1,25000,1,0,NULL,NULL),(2,25000,1,0,NULL,NULL),(3,25000,1,0,NULL,NULL),(4,25000,1,0,NULL,NULL),(5,25000,1,0,NULL,NULL),(6,25000,1,0,NULL,NULL),(7,25000,1,0,NULL,NULL),(8,25000,1,0,NULL,NULL),(9,25000,1,0,NULL,NULL),(10,25000,1,0,NULL,NULL),(11,25000,1,0,NULL,NULL),(12,25000,1,0,NULL,NULL),(13,25000,1,0,NULL,NULL),(14,25000,1,0,NULL,NULL),(15,25000,1,0,NULL,NULL),(16,25000,1,0,NULL,NULL),(17,25000,1,0,NULL,NULL),(18,25000,1,0,NULL,NULL),(19,25000,1,0,NULL,NULL),(20,25000,1,0,NULL,NULL),(21,25000,1,0,NULL,NULL),(22,25000,1,0,NULL,NULL),(23,30000,1,0,NULL,NULL),(24,30000,1,0,NULL,NULL),(25,30000,1,0,NULL,NULL),(26,30000,1,0,NULL,NULL),(27,30000,1,0,NULL,NULL),(28,30000,1,0,NULL,NULL),(29,30000,1,0,NULL,NULL),(30,30000,1,0,NULL,NULL),(31,30000,1,0,NULL,NULL),(32,30000,1,0,NULL,NULL),(33,40000,1,0,NULL,NULL),(34,40000,1,0,NULL,NULL),(35,40000,1,0,NULL,NULL),(36,40000,1,0,NULL,NULL),(37,40000,1,0,NULL,NULL),(38,40000,1,0,NULL,NULL),(39,40000,1,0,NULL,NULL),(40,40000,1,0,NULL,NULL),(41,40000,1,0,NULL,NULL),(42,40000,1,0,NULL,NULL),(43,40000,1,0,NULL,NULL),(44,40000,1,0,NULL,NULL),(45,40000,1,0,NULL,NULL),(46,40000,1,0,NULL,NULL),(47,40000,1,0,NULL,NULL),(48,40000,1,0,NULL,NULL),(49,40000,1,0,NULL,NULL),(50,40000,1,0,NULL,NULL),(51,40000,1,0,NULL,NULL),(52,40000,1,0,NULL,NULL),(53,40000,1,0,NULL,NULL),(54,40000,1,0,NULL,NULL),(55,40000,1,0,NULL,NULL),(56,40000,1,0,NULL,NULL),(57,40000,1,0,NULL,NULL),(58,40000,1,0,NULL,NULL),(59,40000,1,0,NULL,NULL),(60,40000,1,0,NULL,NULL),(61,40000,1,0,NULL,NULL),(62,40000,1,0,NULL,NULL),(63,40000,1,0,NULL,NULL),(64,40000,1,0,NULL,NULL),(65,20000,1,0,NULL,NULL),(66,20000,1,0,NULL,NULL),(67,20000,1,0,NULL,NULL),(68,20000,1,0,NULL,NULL),(69,20000,1,0,NULL,NULL),(70,20000,1,0,NULL,NULL),(71,20000,1,0,NULL,NULL),(72,20000,1,0,NULL,NULL),(73,20000,1,0,NULL,NULL),(74,20000,1,0,NULL,NULL),(75,20000,1,0,NULL,NULL),(76,20000,1,0,NULL,NULL),(77,20000,1,0,NULL,NULL),(78,20000,1,0,NULL,NULL),(79,20000,1,0,NULL,NULL),(80,20000,1,0,NULL,NULL),(81,20000,1,0,NULL,NULL),(82,20000,1,0,NULL,NULL),(83,20000,1,0,NULL,NULL),(84,20000,1,0,NULL,NULL),(85,190000,5,0,NULL,NULL),(86,130000,5,0,NULL,NULL),(87,60000,3,0,NULL,NULL),(88,60000,3,0,NULL,NULL),(89,60000,3,0,NULL,NULL),(90,60000,3,0,NULL,NULL),(91,60000,3,0,NULL,NULL),(92,60000,3,0,NULL,NULL),(93,60000,3,0,NULL,NULL),(94,60000,3,0,NULL,NULL),(95,60000,3,0,NULL,NULL),(96,60000,3,0,NULL,NULL),(97,60000,3,0,NULL,NULL),(98,60000,3,0,NULL,NULL),(99,60000,3,0,NULL,NULL),(100,60000,3,0,NULL,NULL),(101,60000,3,0,NULL,NULL),(102,60000,3,0,NULL,NULL),(103,60000,3,0,NULL,NULL),(104,60000,3,0,NULL,NULL),(105,60000,3,0,NULL,NULL),(106,60000,3,0,NULL,NULL),(107,60000,3,0,NULL,NULL),(108,60000,3,0,NULL,NULL),(109,60000,3,0,NULL,NULL),(110,60000,3,0,NULL,NULL),(111,60000,3,0,NULL,NULL),(112,60000,3,0,NULL,NULL),(113,60000,3,0,NULL,NULL),(114,60000,3,0,NULL,NULL),(115,60000,3,0,NULL,NULL),(116,60000,3,0,NULL,NULL),(117,60000,3,0,NULL,NULL),(118,60000,3,0,NULL,NULL),(119,60000,3,0,NULL,NULL),(120,60000,3,0,NULL,NULL),(121,60000,3,0,NULL,NULL),(122,60000,3,0,NULL,NULL),(123,60000,3,0,NULL,NULL),(124,60000,3,0,NULL,NULL),(125,60000,3,0,NULL,NULL),(126,60000,3,0,NULL,NULL),(127,60000,3,0,NULL,NULL),(128,60000,3,0,NULL,NULL),(129,60000,3,0,NULL,NULL),(130,60000,3,0,NULL,NULL),(131,60000,3,0,NULL,NULL),(132,80000,3,0,NULL,NULL),(133,80000,3,0,NULL,NULL),(134,80000,3,0,NULL,NULL),(135,30000,1,0,NULL,NULL),(136,30000,1,0,NULL,NULL),(137,30000,1,0,NULL,NULL),(138,30000,1,0,NULL,NULL),(139,30000,1,0,NULL,NULL),(140,30000,1,0,NULL,NULL),(141,30000,1,0,NULL,NULL),(142,30000,1,0,NULL,NULL),(143,30000,1,0,NULL,NULL),(144,30000,1,0,NULL,NULL),(145,30000,1,0,NULL,NULL),(146,30000,1,0,NULL,NULL),(147,30000,1,0,NULL,NULL),(148,30000,1,0,NULL,NULL),(149,30000,1,0,NULL,NULL),(150,30000,1,0,NULL,NULL),(151,30000,1,0,NULL,NULL),(152,30000,1,0,NULL,NULL),(153,30000,1,0,NULL,NULL),(154,30000,1,0,NULL,NULL),(155,50000,1,0,NULL,NULL),(156,50000,1,0,NULL,NULL),(157,50000,1,0,NULL,NULL),(158,50000,1,0,NULL,NULL),(159,50000,1,0,NULL,NULL),(160,50000,1,0,NULL,NULL),(161,50000,1,0,NULL,NULL),(162,50000,1,0,NULL,NULL),(163,50000,1,0,NULL,NULL),(164,50000,1,0,NULL,NULL),(165,50000,1,0,NULL,NULL),(166,50000,1,0,NULL,NULL),(167,50000,1,0,NULL,NULL),(168,50000,1,0,NULL,NULL),(169,50000,1,0,NULL,NULL),(170,50000,1,0,NULL,NULL),(171,50000,1,0,NULL,NULL),(172,50000,1,0,NULL,NULL),(173,50000,1,0,NULL,NULL),(174,50000,1,0,NULL,NULL),(175,50000,1,0,NULL,NULL),(176,50000,1,0,NULL,NULL),(177,50000,1,0,NULL,NULL),(178,50000,1,0,NULL,NULL),(179,50000,1,0,NULL,NULL),(180,50000,1,0,NULL,NULL),(181,50000,1,0,NULL,NULL),(182,50000,1,0,NULL,NULL),(183,50000,1,0,NULL,NULL),(184,50000,1,0,NULL,NULL),(185,50000,1,0,NULL,NULL),(186,50000,1,0,NULL,NULL),(187,50000,1,0,NULL,NULL),(188,50000,1,0,NULL,NULL),(189,50000,1,0,NULL,NULL),(190,50000,1,0,NULL,NULL),(191,50000,1,0,NULL,NULL),(192,50000,1,0,NULL,NULL),(193,50000,1,0,NULL,NULL),(194,50000,1,0,NULL,NULL),(195,50000,1,0,NULL,NULL),(196,50000,1,0,NULL,NULL),(197,50000,1,0,NULL,NULL),(198,80000,3,0,NULL,NULL),(199,80000,3,0,NULL,NULL),(200,80000,3,0,NULL,NULL),(201,80000,3,0,NULL,NULL),(202,80000,3,0,NULL,NULL),(203,80000,3,0,NULL,NULL),(204,80000,3,0,NULL,NULL),(205,80000,3,0,NULL,NULL),(206,80000,3,0,NULL,NULL),(207,80000,3,0,NULL,NULL),(208,80000,3,0,NULL,NULL),(209,80000,3,0,NULL,NULL),(210,80000,3,0,NULL,NULL),(211,80000,3,0,NULL,NULL),(212,50000,1,0,NULL,NULL),(213,50000,1,0,NULL,NULL),(214,50000,1,0,NULL,NULL),(215,50000,1,0,NULL,NULL),(216,50000,1,0,NULL,NULL),(217,50000,1,0,NULL,NULL),(218,50000,1,0,NULL,NULL),(219,50000,1,0,NULL,NULL),(220,90000,3,0,NULL,NULL),(221,90000,3,0,NULL,NULL),(222,90000,3,0,NULL,NULL),(223,90000,3,0,NULL,NULL),(224,90000,3,0,NULL,NULL),(225,90000,3,0,NULL,NULL),(226,90000,3,0,NULL,NULL),(227,90000,3,0,NULL,NULL),(228,90000,3,0,NULL,NULL),(229,90000,3,0,NULL,NULL),(230,90000,3,0,NULL,NULL),(231,90000,3,0,NULL,NULL),(232,95000,3,0,NULL,NULL),(233,90000,3,0,NULL,NULL),(234,90000,3,0,NULL,NULL),(235,90000,3,0,NULL,NULL),(236,90000,3,0,NULL,NULL),(237,90000,3,0,NULL,NULL),(238,90000,3,0,NULL,NULL),(239,90000,3,0,NULL,NULL),(240,90000,3,0,NULL,NULL),(241,150000,5,0,NULL,NULL),(242,150000,5,0,NULL,NULL),(243,150000,5,0,NULL,NULL),(244,150000,5,0,NULL,NULL),(245,150000,5,0,NULL,NULL),(246,150000,5,0,NULL,NULL),(247,200000,5,0,NULL,NULL),(248,200000,5,0,NULL,NULL),(249,200000,5,0,NULL,NULL),(251,500000,10,0,NULL,NULL);
/*!40000 ALTER TABLE `properties` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `properties_doors`
--

DROP TABLE IF EXISTS `properties_doors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `properties_doors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_property` int(11) NOT NULL,
  `closed` int(11) NOT NULL DEFAULT 1,
  `ext_x` float NOT NULL,
  `ext_y` float NOT NULL,
  `ext_z` float NOT NULL,
  `ext_angle` float NOT NULL DEFAULT 0,
  `ext_entrance_door_id` int(11) DEFAULT NULL,
  `ext_sub_id` int(11) DEFAULT NULL,
  `id_interior` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id_property` (`id_property`),
  KEY `ext_entrance_door_id` (`ext_entrance_door_id`),
  KEY `ext_sub_id` (`ext_sub_id`),
  KEY `id_interior` (`id_interior`),
  CONSTRAINT `properties_doors_ibfk_1` FOREIGN KEY (`id_property`) REFERENCES `properties` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `properties_doors_ibfk_2` FOREIGN KEY (`ext_entrance_door_id`) REFERENCES `entrances_doors` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `properties_doors_ibfk_3` FOREIGN KEY (`ext_sub_id`) REFERENCES `properties_doors` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `properties_doors_ibfk_4` FOREIGN KEY (`id_interior`) REFERENCES `interiors` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `properties_doors`
--

LOCK TABLES `properties_doors` WRITE;
/*!40000 ALTER TABLE `properties_doors` DISABLE KEYS */;
INSERT INTO `properties_doors` VALUES (1,1,1,5202.74,-167.359,5.56185,290.273,NULL,NULL,79),(3,2,1,5210.3,-162.644,5.56406,202.683,NULL,NULL,79),(4,3,1,5196.06,-152.405,5.55625,289.791,NULL,NULL,79),(5,4,1,5194.5,-147.939,5.56021,286.344,NULL,NULL,79),(6,5,1,5198.69,-132.927,5.56406,20.0317,NULL,NULL,79),(7,6,1,5188.78,-131.415,5.56284,290.418,NULL,NULL,79),(8,7,1,5196.7,-126.831,5.56406,201.43,NULL,NULL,79),(9,8,1,5182.85,-116.636,5.55625,287.284,NULL,NULL,79),(10,9,1,5181.41,-111.932,5.56152,289.478,NULL,NULL,79),(11,10,1,5186.17,-97.1347,5.56406,17.5251,NULL,NULL,79),(12,11,1,5176.39,-95.3207,5.5697,287.284,NULL,NULL,79),(13,12,1,5184.17,-91.4281,5.56406,194.85,NULL,NULL,79),(14,13,1,5171.2,-81.1164,5.56406,285.091,NULL,NULL,79),(15,14,1,5169.96,-76.2278,5.56406,285.404,NULL,NULL,79),(16,15,1,5175.29,-61.7272,5.57166,13.4517,NULL,NULL,79),(17,16,1,5165.98,-59.3152,5.57225,283.211,NULL,NULL,79),(18,17,1,5174.12,-56.4721,5.57082,192.97,NULL,NULL,79),(19,18,1,5161.53,-45.5383,5.56833,281.644,NULL,NULL,79),(20,19,1,5160.59,-40.8389,5.56406,280.704,NULL,NULL,79),(21,20,1,5167.06,-27.3992,5.56757,14.3916,NULL,NULL,79),(22,21,1,5157.26,-24.2202,5.56524,281.331,NULL,NULL,79),(23,22,1,5165.98,-21.672,5.56734,189.523,NULL,NULL,79),(24,23,1,4840.11,533.647,6.17188,0.291412,NULL,NULL,79),(25,24,1,4792.05,573.163,6.17188,275.064,NULL,NULL,79),(26,25,1,4785.18,615.303,6.17188,272.871,NULL,NULL,79),(27,26,1,4783.99,635.601,6.17188,274.751,NULL,NULL,79),(28,27,1,4858.21,566.01,6.17188,178.533,NULL,NULL,79),(29,28,1,4817.36,602.95,6.17188,89.8588,NULL,NULL,79),(30,29,1,4814.04,629.879,6.17188,83.2784,NULL,NULL,79),(31,30,1,4809.97,657.601,5.1672,88.2917,NULL,NULL,79),(32,31,1,4881.24,625.766,5.97062,271.257,NULL,NULL,79),(33,32,1,4886.01,598.15,4.83618,273.137,NULL,NULL,79),(34,33,1,5029.01,806.769,5.39544,94.1458,NULL,NULL,71),(35,34,1,5029.14,824.416,5.37778,91.494,NULL,NULL,71),(36,35,1,5028.53,840.997,5.46719,88.6739,NULL,NULL,71),(37,36,1,5031.06,855.88,6.06086,88.0473,NULL,NULL,71),(38,37,1,5030.9,874.235,6.02305,89.6141,NULL,NULL,71),(39,38,1,5031.68,890.064,5.39524,91.8074,NULL,NULL,71),(40,39,1,5031.42,908.385,5.42065,93.0606,NULL,NULL,71),(41,40,1,5030.97,924.752,6.05782,91.8072,NULL,NULL,71),(42,41,1,5031.02,944.334,6.06319,93.3738,NULL,NULL,71),(43,42,1,5031.68,959.699,5.38726,92.7471,NULL,NULL,71),(44,43,1,5031.57,978.002,5.39901,91.8069,NULL,NULL,71),(45,44,1,5030.36,993.596,5.41802,90.5534,NULL,NULL,71),(46,45,1,5031.11,1010.05,5.46142,89.6134,NULL,NULL,71),(47,46,1,5031.44,1027.41,5.41279,90.5533,NULL,NULL,71),(48,47,1,5034.33,1042.95,5.47281,90.8666,NULL,NULL,71),(49,48,1,5032.83,1054.33,5.73406,89.6132,NULL,NULL,71),(50,49,1,4997.97,829.315,5.40675,268.842,NULL,NULL,71),(51,50,1,4997.85,841.031,5.78106,271.662,NULL,NULL,71),(52,51,1,4996.34,849.134,5.46714,269.782,NULL,NULL,71),(53,52,1,4999.24,862.152,5.42501,270.095,NULL,NULL,71),(54,53,1,4999.57,878.249,5.47344,270.722,NULL,NULL,71),(55,54,1,4997.47,898.089,5.46563,359.396,NULL,NULL,71),(56,55,1,4988.62,941.34,5.41974,178.601,NULL,NULL,71),(57,56,1,4974.66,941.238,5.41702,182.047,NULL,NULL,71),(58,57,1,4961.42,939.836,5.43463,175.781,NULL,NULL,71),(59,58,1,4947.83,957.887,5.47704,89.9265,NULL,NULL,71),(60,59,1,4948.16,973.182,5.42232,89.2997,NULL,NULL,71),(61,60,1,4951.06,986.464,5.46469,89.6129,NULL,NULL,71),(62,61,1,4949.55,994.092,5.77673,88.3596,NULL,NULL,71),(63,62,1,5003.03,984.442,5.40616,270.698,NULL,NULL,71),(64,63,1,5002.92,972.14,5.20138,270.385,NULL,NULL,71),(65,64,1,5001.46,957.494,5.4716,266.311,NULL,NULL,71),(66,65,1,5050.84,1136.48,4.75353,356.782,NULL,NULL,189),(67,65,1,5049.49,1128.54,5.07741,181.772,NULL,NULL,188),(68,66,1,5045.08,1137.32,4.71802,5.09666,NULL,NULL,189),(69,66,1,5042.88,1129.26,5.05253,178.975,NULL,NULL,188),(71,67,1,5039.19,1137.14,4.71536,359.77,NULL,NULL,189),(72,67,1,5037.88,1129.36,5.05238,179.312,NULL,NULL,188),(73,68,1,5032.84,1137.17,4.67798,1.3597,NULL,NULL,189),(74,68,1,5031.17,1129.29,5.05222,179.312,NULL,NULL,188),(75,69,1,5020.25,1136.99,4.57827,359.167,NULL,NULL,189),(76,69,1,5018.31,1129.22,4.89392,182.445,NULL,NULL,188),(77,70,1,5014.31,1137.33,4.60123,3.23985,NULL,NULL,189),(78,70,1,5012.08,1129.39,4.9243,182.445,NULL,NULL,188),(79,71,1,5007.01,1136.94,4.63711,1.3597,NULL,NULL,189),(80,71,1,5004.79,1128.95,4.95401,181.505,NULL,NULL,188),(81,72,1,4994.1,1137.25,4.6518,1.3597,NULL,NULL,189),(82,72,1,4992.63,1129.46,4.97357,178.708,NULL,NULL,188),(83,73,1,5005.94,1155.07,3.78853,176.202,NULL,NULL,189),(84,73,1,5007.89,1162.84,3.73986,1.98643,NULL,NULL,188),(85,74,1,5018.5,1155.08,3.73235,179.335,NULL,NULL,189),(86,74,1,5020.23,1162.87,3.71333,359.817,NULL,NULL,188),(87,75,1,5033.85,1154.99,3.70714,269.599,NULL,NULL,189),(88,75,1,5026.07,1157.02,3.69278,88.804,NULL,NULL,188),(89,76,1,5033.85,1161.45,3.69006,270.539,NULL,NULL,189),(90,76,1,5026.07,1163.49,3.69857,90.684,NULL,NULL,188),(91,77,1,5033.88,1170.55,3.69227,267.406,NULL,NULL,189),(92,77,1,5025.87,1172.16,3.71181,91.9373,NULL,NULL,188),(93,78,1,5033.9,1177.44,3.69797,268.972,NULL,NULL,189),(94,78,1,5025.93,1179.33,3.71783,90.0572,NULL,NULL,188),(95,79,1,5018.26,1181.18,3.7272,359.19,NULL,NULL,189),(96,79,1,5016.26,1173.4,3.72963,179.021,NULL,NULL,188),(97,80,1,5005.87,1173.55,3.74232,89.744,NULL,NULL,189),(98,80,1,5013.82,1171.34,3.73261,271.456,NULL,NULL,188),(99,81,1,5009.52,1201.13,3.71724,359.503,NULL,NULL,189),(100,81,1,5007.38,1193.34,3.70227,181.238,NULL,NULL,188),(101,82,1,5016.84,1201.36,3.67605,1.06936,NULL,NULL,189),(102,82,1,5014.72,1193.36,3.67545,180.273,NULL,NULL,188),(103,83,1,5022.94,1201.17,3.6396,359.794,NULL,NULL,189),(104,83,1,5020.81,1193.19,3.65265,174.924,NULL,NULL,188),(105,84,1,5048.59,1186.68,3.76241,176.804,NULL,NULL,189),(106,84,1,5050.56,1194.46,3.73358,355.696,NULL,NULL,188),(107,85,1,6428.51,1654.39,7.17,0.457568,NULL,NULL,107),(108,86,1,6444.13,1574.51,6.75544,2.0733,NULL,NULL,136),(109,87,1,6446.22,1271.54,10.6297,91.9941,NULL,NULL,141),(110,88,1,6445.58,1268.58,10.6297,1.75323,NULL,NULL,141),(111,89,1,6425.51,1268.58,10.6297,0.499285,NULL,NULL,141),(112,90,1,6425.13,1271.41,10.6297,273.079,NULL,NULL,141),(113,91,1,6445.79,1267.55,6.43624,0.20842,NULL,NULL,141),(114,92,1,6425.36,1267.55,6.43437,1.77641,NULL,NULL,141),(115,93,1,6424.93,1271.4,6.43437,269.969,NULL,NULL,141),(116,94,1,6479.82,1239.22,5.84844,0.20842,NULL,NULL,141),(117,95,1,6475.91,1239.85,5.84844,269.656,NULL,NULL,141),(118,96,1,6475.91,1260.03,5.84844,268.089,NULL,NULL,141),(119,97,1,6479.99,1260.5,10.0437,183.801,NULL,NULL,141),(120,98,1,6476.93,1260.13,10.0437,271.849,NULL,NULL,141),(121,99,1,6476.93,1239.6,10.0437,275.922,NULL,NULL,141),(122,100,1,6479.8,1239.22,10.0437,359.897,NULL,NULL,141),(123,101,1,6482.41,1207.74,5.69906,175.608,NULL,NULL,141),(124,102,1,6478.5,1207.26,5.69906,268.982,NULL,NULL,141),(125,103,1,6478.26,1198.05,5.69906,268.356,NULL,NULL,141),(126,104,1,6478.21,1196.23,5.69906,268.356,NULL,NULL,141),(127,105,1,6477.97,1187.1,5.69906,266.789,NULL,NULL,141),(128,106,1,6481.94,1186.51,9.89437,358.596,NULL,NULL,141),(129,107,1,6479,1186.9,9.89437,266.475,NULL,NULL,141),(130,108,1,6479.19,1194.12,9.89437,268.042,NULL,NULL,141),(131,109,1,6479.29,1197.98,9.89437,263.342,NULL,NULL,141),(132,110,1,6479.48,1205.22,9.89437,266.789,NULL,NULL,141),(133,111,1,6482.38,1207.6,9.89437,175.921,NULL,NULL,141),(134,112,1,6458.62,1155.51,5.69906,299.979,NULL,NULL,141),(135,113,1,6457.31,1158.55,5.69906,213.185,NULL,NULL,141),(136,114,1,6466.34,1163.66,5.69906,211.932,NULL,NULL,141),(137,115,1,6475.49,1165.08,9.83969,120.751,NULL,NULL,141),(138,116,1,6466.51,1162.87,9.8473,209.425,NULL,NULL,141),(139,117,1,6457.69,1157.67,9.83969,209.112,NULL,NULL,141),(140,118,1,6458.87,1155.09,9.8473,302.486,NULL,NULL,141),(141,119,1,6440.01,1169.35,5.69906,31.1365,NULL,NULL,141),(142,120,1,6442.78,1171.59,5.69906,117.931,NULL,NULL,141),(143,121,1,6432.17,1188.94,5.69906,122.004,NULL,NULL,141),(144,122,1,6430.26,1188.34,9.91781,211.932,NULL,NULL,141),(145,123,1,6441.79,1171.23,9.91781,123.571,NULL,NULL,141),(146,124,1,6439.72,1169.17,9.91781,29.5699,NULL,NULL,141),(147,125,1,6415.78,1239.42,6.43437,185.298,NULL,NULL,141),(148,126,1,6419.62,1239.24,6.43437,98.1904,NULL,NULL,141),(149,127,1,6421.23,1218.93,6.43437,95.9972,NULL,NULL,141),(150,128,1,6417.48,1218.22,10.6297,4.50293,NULL,NULL,141),(151,129,1,6420.18,1219.16,10.6297,94.7438,NULL,NULL,141),(152,130,1,6418.6,1239.24,10.6375,96.937,NULL,NULL,141),(153,131,1,6415.78,1239.42,10.6297,182.478,NULL,NULL,141),(154,132,1,6291.74,1043.79,6.02187,327.987,NULL,NULL,144),(155,133,1,6286.58,1081.78,6.17188,140.612,NULL,NULL,144),(156,134,1,6301.61,1068.18,6.17188,140.925,NULL,NULL,144),(157,135,1,6283.02,927.796,6.27152,336.287,NULL,NULL,79),(158,136,1,6269.23,920.791,6.29812,242.287,NULL,NULL,79),(159,137,1,6267.02,916.257,6.29812,239.153,NULL,NULL,79),(160,138,1,6269.06,899.076,6.28838,152.359,NULL,NULL,79),(161,139,1,6260.41,901.556,6.29678,242.913,NULL,NULL,79),(162,140,1,6266.2,893.077,6.29348,331.901,NULL,NULL,79),(163,141,1,6252.57,885.744,6.23982,243.853,NULL,NULL,79),(164,142,1,6250.31,881.304,6.23146,238.213,NULL,NULL,79),(165,143,1,6252.22,864.336,6.291,158.313,NULL,NULL,79),(166,144,1,6243.56,866.588,6.29247,242.6,NULL,NULL,79),(167,145,1,6249.53,858.071,6.29625,336.288,NULL,NULL,79),(168,146,1,6235.55,851.059,6.29074,243.227,NULL,NULL,79),(169,147,1,6233.37,846.668,6.29897,242.287,NULL,NULL,79),(170,148,1,6232.44,823.128,6.29476,332.841,NULL,NULL,79),(171,149,1,6235.32,829.293,6.28954,152.673,NULL,NULL,79),(172,150,1,6226.73,831.704,6.29662,246.047,NULL,NULL,79),(173,151,1,6218.75,816.062,6.27036,240.72,NULL,NULL,79),(174,152,1,6216.6,811.467,6.2985,241.033,NULL,NULL,79),(175,153,1,6218.5,794.562,6.27749,157.686,NULL,NULL,79),(176,154,1,6209.96,796.938,6.28148,246.36,NULL,NULL,79),(177,155,1,6008.63,-5.35234,5.79688,354.191,NULL,NULL,71),(178,156,1,6000.34,2.96213,5.79688,273.977,NULL,NULL,71),(179,157,1,5995.02,-19.6367,5.79688,181.543,NULL,NULL,71),(180,158,1,5986.06,-0.692238,5.79688,92.5555,NULL,NULL,71),(181,159,1,5977.63,-11.9309,5.79688,270.217,NULL,NULL,71),(182,160,1,5958.81,-20.9653,5.79688,182.483,NULL,NULL,71),(183,161,1,5955,-6.68354,5.79688,359.182,NULL,NULL,71),(184,162,1,5963.35,1.72348,5.79688,88.4821,NULL,NULL,71),(185,163,1,5997.75,-38.0103,4.92812,3.88136,NULL,NULL,71),(186,164,1,5998.17,-52.1671,4.92812,182.146,NULL,NULL,71),(187,165,1,5995.24,-52.1914,4.92812,180.893,NULL,NULL,71),(188,166,1,5998.11,-58.3173,4.92812,0.094873,NULL,NULL,71),(189,167,1,5995.12,-58.3194,4.92812,359.471,NULL,NULL,71),(190,168,1,5995.16,-72.4803,4.92812,181.52,NULL,NULL,71),(191,169,1,5998.18,-72.4779,4.92812,180.266,NULL,NULL,71),(192,170,1,5998.08,-80.2502,4.92812,358.845,NULL,NULL,71),(193,171,1,5995.66,-80.2506,4.92812,1.66472,NULL,NULL,71),(194,172,1,5983.54,-85.8889,4.92812,269.544,NULL,NULL,71),(195,173,1,5983.55,-88.7261,4.92812,269.544,NULL,NULL,71),(196,174,1,5969.38,-88.883,4.92812,85.3023,NULL,NULL,71),(197,175,1,5969.38,-86.2153,4.92812,87.4956,NULL,NULL,71),(198,176,1,5995.52,-94.4084,4.92812,178.363,NULL,NULL,71),(199,177,1,5998.3,-94.4077,4.92812,181.183,NULL,NULL,71),(200,178,1,5998.37,-100.96,4.92812,0.074019,NULL,NULL,71),(201,179,1,5995.57,-100.96,4.92812,0.074019,NULL,NULL,71),(202,180,1,5995.62,-115.117,4.92812,183.376,NULL,NULL,71),(203,181,1,5998.14,-115.118,4.92812,179.303,NULL,NULL,71),(204,182,1,5977.99,-115.117,4.92033,181.183,NULL,NULL,71),(205,183,1,5975.09,-115.335,4.92033,178.677,NULL,NULL,71),(206,184,1,5974.99,-100.952,4.92812,357.255,NULL,NULL,71),(207,185,1,5977.91,-100.958,4.92033,0.074019,NULL,NULL,71),(208,186,1,6021.39,-80.5499,4.92033,4.12469,NULL,NULL,71),(209,187,1,6018.57,-80.5501,4.92033,0.044235,NULL,NULL,71),(210,188,1,6018.29,-94.7079,4.92033,176.773,NULL,NULL,71),(211,189,1,6021.14,-94.8658,4.92033,177.713,NULL,NULL,71),(212,190,1,6021.46,-102.919,4.92033,3.18475,NULL,NULL,71),(213,191,1,6018.53,-102.919,4.92812,3.81136,NULL,NULL,71),(214,192,1,6018.48,-117.077,4.92812,177.713,NULL,NULL,71),(215,193,1,6021.3,-117.081,4.92033,176.773,NULL,NULL,71),(216,194,1,5895.4,-236.721,4.92,356.605,NULL,NULL,71),(217,195,1,5898.19,-236.72,4.92,1.30476,NULL,NULL,71),(218,196,1,5898.12,-250.878,4.92781,180.823,NULL,NULL,71),(219,197,1,5895.52,-250.88,4.92781,180.823,NULL,NULL,71),(220,198,1,6003.48,-259.103,4.9225,83.2159,NULL,NULL,93),(221,199,1,6003.24,-263.277,4.9225,82.5892,NULL,NULL,93),(222,200,1,6002.67,-269.821,7.46177,86.976,NULL,NULL,93),(223,201,1,6004.18,-252.536,7.46177,81.3359,NULL,NULL,93),(224,202,1,6035.32,-265.981,4.9225,263.988,NULL,NULL,93),(225,203,1,6035.52,-261.786,4.9225,264.928,NULL,NULL,93),(226,204,1,6036.1,-255.109,7.45,263.361,NULL,NULL,93),(227,205,1,6034.56,-272.712,7.45,264.301,NULL,NULL,93),(228,206,1,6020.11,-278.789,4.9225,177.193,NULL,NULL,93),(229,207,1,6015.82,-278.342,4.9225,176.253,NULL,NULL,93),(230,208,1,6009.22,-277.835,7.46177,174.373,NULL,NULL,93),(231,209,1,6026.7,-279.39,7.46177,178.447,NULL,NULL,93),(232,210,1,6018.69,-246.449,4.9225,0.761561,NULL,NULL,93),(233,211,1,6022.82,-246.811,4.9225,346.035,NULL,NULL,93),(234,212,1,5945.29,-254.267,5.67688,180.052,NULL,NULL,79),(235,213,1,5936.98,-262.456,5.67688,272.486,NULL,NULL,79),(236,214,1,5922.7,-248.928,5.67688,89.8107,NULL,NULL,79),(237,215,1,5941.8,-239.982,5.67688,4.26985,NULL,NULL,79),(238,216,1,5935.5,-285.803,5.67688,273.089,NULL,NULL,79),(239,217,1,5943.79,-294.088,5.67688,0.194834,NULL,NULL,79),(240,218,1,5930.28,-308.377,5.67688,182.221,NULL,NULL,79),(241,219,1,5921.21,-289.447,5.67688,86.0272,NULL,NULL,79),(242,220,1,5982.56,-312.044,4.93239,85.1986,NULL,NULL,114),(243,221,1,5980.61,-334.407,4.91995,85.8253,NULL,NULL,114),(244,222,1,6024.59,-310.341,4.92469,355.921,NULL,NULL,114),(245,223,1,6002.3,-308.245,4.93239,355.294,NULL,NULL,114),(246,224,1,5976.55,-386.624,4.91585,86.812,NULL,NULL,114),(247,225,1,5975.46,-399.104,4.91676,83.6787,NULL,NULL,114),(248,226,1,5974.15,-411.278,4.90688,84.3054,NULL,NULL,114),(249,227,1,5973.25,-423.64,4.90688,85.2454,NULL,NULL,114),(250,228,1,5971.42,-444.791,4.90244,84.6187,NULL,NULL,114),(251,229,1,5970.33,-457.312,4.89906,85.5588,NULL,NULL,114),(252,230,1,5969.26,-469.527,4.89906,87.4389,NULL,NULL,114),(253,231,1,5968.18,-481.848,4.89738,86.8123,NULL,NULL,114),(254,232,1,5973.07,-506.122,4.90955,177.053,NULL,NULL,114),(255,233,1,5981.8,-482.986,4.9225,265.727,NULL,NULL,114),(256,234,1,5982.88,-470.748,4.9225,266.981,NULL,NULL,114),(257,235,1,5983.96,-458.322,4.9225,262.594,NULL,NULL,114),(258,236,1,5985.06,-445.772,4.9225,262.907,NULL,NULL,114),(259,237,1,5986.92,-424.829,4.9225,265.414,NULL,NULL,114),(260,238,1,5988.15,-412.658,4.9225,264.161,NULL,NULL,114),(261,239,1,5989.09,-400.009,4.92361,265.101,NULL,NULL,114),(262,240,1,5990.17,-387.668,4.91687,266.981,NULL,NULL,114),(263,241,1,5755.23,726.665,4.72,135.701,NULL,NULL,143),(264,242,1,5649.82,772.737,6.83755,91.1834,NULL,NULL,143),(265,243,1,5471.17,749.293,5.48805,275.088,NULL,NULL,143),(266,244,1,5429.69,501.739,7.03243,268.195,NULL,NULL,143),(267,245,1,5490.26,626.189,7.90243,268.532,NULL,NULL,143),(268,246,1,5631.38,631.393,5.69258,177.038,NULL,NULL,143),(269,247,1,5363.7,523.535,8.57812,1.44577,NULL,NULL,116),(270,248,1,5424.39,604.145,9.44812,181.928,NULL,NULL,116),(271,249,1,5371.65,738.067,7.64219,38.7563,NULL,NULL,116),(272,251,1,5621.46,495.527,14.0375,359.083,NULL,NULL,157),(273,251,1,5659.32,476.278,31.4062,92.7444,NULL,NULL,158),(274,251,1,5665.23,471.232,6.06125,92.4234,NULL,NULL,159);
/*!40000 ALTER TABLE `properties_doors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `variables`
--

DROP TABLE IF EXISTS `variables`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `variables` (
  `name` varchar(32) NOT NULL,
  `value` varchar(128) NOT NULL,
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `variables`
--

LOCK TABLES `variables` WRITE;
/*!40000 ALTER TABLE `variables` DISABLE KEYS */;
INSERT INTO `variables` VALUES ('business_depreciation','0.75'),('oldvehicle_min_price','300'),('property_depreciation','0.75'),('vehicle_default_price','10000'),('vehicle_depreciation','0.750000'),('vehicle_depreciation_kms','1000'),('vehicle_depreciation_value','100');
/*!40000 ALTER TABLE `variables` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicle_components`
--

DROP TABLE IF EXISTS `vehicle_components`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicle_components` (
  `id_vehicle` int(11) NOT NULL,
  `componentid` int(11) NOT NULL,
  PRIMARY KEY (`id_vehicle`,`componentid`),
  CONSTRAINT `vehicle_components_ibfk_1` FOREIGN KEY (`id_vehicle`) REFERENCES `vehicles` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicle_components`
--

LOCK TABLES `vehicle_components` WRITE;
/*!40000 ALTER TABLE `vehicle_components` DISABLE KEYS */;
/*!40000 ALTER TABLE `vehicle_components` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicle_inventory`
--

DROP TABLE IF EXISTS `vehicle_inventory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicle_inventory` (
  `vehicle_id` int(11) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `item_id` int(11) NOT NULL,
  `amount` int(11) NOT NULL DEFAULT 1,
  `params` varchar(128) DEFAULT NULL,
  `position` int(11) NOT NULL DEFAULT -1,
  PRIMARY KEY (`id`),
  KEY `vehicle_id` (`vehicle_id`),
  KEY `item_id` (`item_id`),
  CONSTRAINT `vehicle_inventory_ibfk_1` FOREIGN KEY (`vehicle_id`) REFERENCES `vehicles` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `vehicle_inventory_ibfk_2` FOREIGN KEY (`item_id`) REFERENCES `inv_items` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicle_inventory`
--

LOCK TABLES `vehicle_inventory` WRITE;
/*!40000 ALTER TABLE `vehicle_inventory` DISABLE KEYS */;
/*!40000 ALTER TABLE `vehicle_inventory` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicle_prices`
--

DROP TABLE IF EXISTS `vehicle_prices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicle_prices` (
  `modelid` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `level` int(11) NOT NULL DEFAULT 1,
  UNIQUE KEY `modelid` (`modelid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicle_prices`
--

LOCK TABLES `vehicle_prices` WRITE;
/*!40000 ALTER TABLE `vehicle_prices` DISABLE KEYS */;
INSERT INTO `vehicle_prices` VALUES (400,30000,1),(401,8000,1),(402,60000,3),(405,9000,1),(410,8000,1),(411,200000,5),(412,30000,3),(415,175000,5),(418,15000,1),(419,13500,1),(421,11000,1),(422,14000,1),(424,19000,1),(426,16000,1),(429,190000,5),(436,7000,1),(439,22000,3),(445,10000,1),(451,180000,5),(458,30000,3),(461,20000,3),(462,2000,1),(463,25000,3),(467,8000,1),(468,15000,3),(471,9000,1),(474,12000,1),(475,7000,1),(477,120000,4),(478,9000,1),(479,16000,1),(480,35000,3),(483,30000,3),(489,20000,3),(491,7500,1),(492,8000,1),(496,80000,4),(500,18000,3),(505,16000,3),(506,180000,5),(507,8000,1),(516,6000,1),(517,5500,1),(518,7500,1),(521,15000,3),(522,23000,5),(526,10000,1),(527,9800,1),(529,9300,1),(533,15000,1),(534,9000,1),(535,30000,3),(536,15000,1),(540,9000,1),(541,190000,5),(542,5000,1),(543,6000,1),(545,150000,5),(546,12000,1),(547,10000,1),(549,8000,1),(550,15000,1),(551,8000,1),(554,14000,1),(555,20000,3),(558,16000,1),(559,22000,3),(560,21000,3),(561,19500,3),(562,28000,3),(565,20000,3),(566,9000,1),(567,16000,3),(575,19000,3),(576,9500,1),(579,17000,1),(580,13000,1),(581,13500,1),(585,9000,1),(586,10000,1),(587,17000,1),(589,14000,1),(600,5000,1),(602,45000,3),(603,95000,5);
/*!40000 ALTER TABLE `vehicle_prices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicle_types`
--

DROP TABLE IF EXISTS `vehicle_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicle_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL,
  `load_init` int(11) NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicle_types`
--

LOCK TABLES `vehicle_types` WRITE;
/*!40000 ALTER TABLE `vehicle_types` DISABLE KEYS */;
INSERT INTO `vehicle_types` VALUES (1,'VEHICLE_TYPE_RENT',1),(2,'VEHICLE_TYPE_PLAYER',0),(3,'VEHICLE_TYPE_JOB',1),(4,'VEHICLE_TYPE_FACTION',1),(5,'VEHICLE_TYPE_SELL',1),(6,'VEHICLE_TYPE_DS',0),(7,'VEHICLE_TYPE_FREE',1),(8,'VEHICLE_TYPE_AUTOPILOT',1);
/*!40000 ALTER TABLE `vehicle_types` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicles`
--

DROP TABLE IF EXISTS `vehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `modelid` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `number_plate` varchar(32) NOT NULL DEFAULT 'random',
  `fuel` float NOT NULL DEFAULT -1,
  `addsiren` int(11) NOT NULL DEFAULT 0,
  `health` float NOT NULL DEFAULT 1000,
  `distance` float NOT NULL DEFAULT -1,
  `spawn_pos_x` float NOT NULL,
  `spawn_pos_y` float NOT NULL,
  `spawn_pos_z` float NOT NULL,
  `spawn_angle` float NOT NULL DEFAULT 0,
  `interiorid` int(11) NOT NULL DEFAULT 0,
  `worldid` int(11) NOT NULL DEFAULT 0,
  `color1` int(11) NOT NULL DEFAULT -1,
  `color2` int(11) NOT NULL DEFAULT -1,
  `paintjob` int(11) NOT NULL DEFAULT 3,
  `damage_panels` int(11) NOT NULL DEFAULT 0,
  `damage_doors` int(11) NOT NULL DEFAULT 0,
  `damage_lights` int(11) NOT NULL DEFAULT 0,
  `damage_tires` int(11) NOT NULL DEFAULT 0,
  `params_engine` int(11) NOT NULL DEFAULT 0,
  `params_lights` int(11) NOT NULL DEFAULT 0,
  `params_alarm` int(11) NOT NULL DEFAULT 0,
  `params_doors` int(11) NOT NULL DEFAULT 0,
  `params_bonnet` int(11) NOT NULL DEFAULT 0,
  `params_boot` int(11) NOT NULL DEFAULT 0,
  `params_objective` int(11) NOT NULL DEFAULT 0,
  `radio` int(11) NOT NULL DEFAULT -1,
  `game_state` int(11) NOT NULL DEFAULT 0,
  `id_player` int(11) DEFAULT NULL,
  `price` int(11) NOT NULL DEFAULT 0,
  `level` int(11) NOT NULL DEFAULT 1,
  `id_job_point` int(11) DEFAULT NULL,
  `created` tinyint(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `type` (`type`),
  KEY `id_player` (`id_player`),
  KEY `id_job_point` (`id_job_point`),
  CONSTRAINT `vehicles_ibfk_1` FOREIGN KEY (`type`) REFERENCES `vehicle_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `vehicles_ibfk_2` FOREIGN KEY (`id_player`) REFERENCES `player` (`id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `vehicles_ibfk_3` FOREIGN KEY (`id_job_point`) REFERENCES `jobs_points` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicles`
--

LOCK TABLES `vehicles` WRITE;
/*!40000 ALTER TABLE `vehicles` DISABLE KEYS */;
INSERT INTO `vehicles` VALUES (1,438,3,'random',-1,0,1000,-1,4995.21,1257.72,5.86147,182.478,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(2,438,3,'random',-1,0,1000,-1,5000.73,1257.2,5.89803,166.311,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(3,438,3,'random',-1,0,1000,-1,4991.67,1237.34,5.86748,352.967,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(4,438,3,'random',-1,0,1000,-1,5004.06,1243.88,5.89434,82.7174,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(5,438,3,'random',-1,0,1000,-1,4984.57,1261.85,5.67398,353.441,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(6,438,8,'random',-1,0,1000,-1,4555.15,215.35,9.20382,249.506,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(7,438,8,'random',-1,0,1000,-1,4577.85,217.303,9.24685,298.434,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(8,438,8,'random',-1,0,1000,-1,4533.19,251.732,9.18655,180.857,0,0,6,76,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,1,1),(9,509,7,'random',-1,0,1000,-1,4598.47,241.188,8.84666,81.8251,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(10,509,7,'random',-1,0,1000,-1,4598.08,238.967,8.88165,78.7329,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(11,509,7,'random',-1,0,1000,-1,4597.56,236.803,8.84653,76.6602,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(12,509,7,'random',-1,0,1000,-1,4597.18,234.633,8.84683,75.7725,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(13,509,7,'random',-1,0,1000,-1,4596.29,232.602,8.84598,66.6882,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(14,509,7,'random',-1,0,1000,-1,4595.51,230.271,8.84331,70.1422,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(15,509,7,'random',-1,0,1000,-1,6324.76,2185.96,12.5702,175.383,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(16,509,7,'random',-1,0,1000,-1,6326.65,2185.95,12.5555,180.993,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(17,509,7,'random',-1,0,1000,-1,6328.22,2185.95,12.5412,179.267,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(18,509,7,'random',-1,0,1000,-1,6330.23,2185.81,12.5098,180.821,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(19,509,7,'random',-1,0,1000,-1,6332.22,2185.79,12.5121,181.312,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(20,509,7,'random',-1,0,1000,-1,6334.22,2185.77,12.4642,181.684,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,NULL,1),(21,410,1,'random',-1,0,1000,-1,4337.27,384.624,9.00616,358.51,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(22,401,1,'random',-1,0,1000,-1,4343.77,384.672,9.14264,1.166,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(23,401,1,'random',-1,0,1000,-1,4350.26,384.677,9.12924,0.281855,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(24,410,1,'random',-1,0,1000,-1,4356.55,384.701,9.12968,359.828,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(25,401,1,'random',-1,0,1000,-1,4356.57,395.879,9.13312,178.439,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(26,410,1,'random',-1,0,1000,-1,4340.49,396.132,9.12914,179.723,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(27,405,1,'random',-1,0,1000,-1,4334.23,396.068,9.23737,180.891,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,80,1,NULL,1),(28,405,1,'random',-1,0,1000,-1,4363.12,395.955,9.22498,181.376,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,80,1,NULL,1),(29,462,1,'random',-1,0,1000,-1,4586.38,275.439,8.93253,180.872,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(30,462,1,'random',-1,0,1000,-1,4583.4,275.319,8.94161,180.87,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(31,462,1,'random',-1,0,1000,-1,4580.42,275.349,8.93416,179.737,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(32,462,1,'random',-1,0,1000,-1,4577.25,275.212,8.93026,180.562,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(33,462,1,'random',-1,0,1000,-1,4574.02,275.247,8.93504,180.817,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(34,462,1,'random',-1,0,1000,-1,5169.36,582.197,5.13156,107.921,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(35,462,1,'random',-1,0,1000,-1,5168.69,585.068,5.13072,105.709,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(36,462,1,'random',-1,0,1000,-1,5167.59,588.455,5.13256,103.065,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(37,401,1,'random',-1,0,1000,-1,5353.47,1658.43,5.30637,353.588,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(38,410,1,'random',-1,0,1000,-1,5359.26,1658.19,5.18177,356.696,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(39,410,1,'random',-1,0,1000,-1,5365.34,1657.88,5.18213,357.125,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,60,1,NULL,1),(40,462,1,'random',-1,0,1000,-1,6511.53,2166.14,11.1525,83.7646,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(41,462,1,'random',-1,0,1000,-1,6511.29,2163.14,11.0978,86.0418,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(42,462,1,'random',-1,0,1000,-1,6511.27,2160.33,11.0559,86.2657,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(43,462,1,'random',-1,0,1000,-1,6511.77,2169.41,11.2124,87.1422,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(44,462,1,'random',-1,0,1000,-1,6432.63,348.842,5.13251,67.6328,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(45,462,1,'random',-1,0,1000,-1,6431.76,346.691,5.1409,67.479,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(46,462,1,'random',-1,0,1000,-1,6430.71,344.186,5.14135,67.9909,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(47,462,1,'random',-1,0,1000,-1,6429.52,341.708,5.13811,68.4391,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,20,1,NULL,1),(48,471,1,'random',-1,0,1000,-1,6654.44,807.492,3.65318,276.369,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,100,2,NULL,1),(49,471,1,'random',-1,0,1000,-1,6654.06,810.962,3.65538,278.042,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,100,2,NULL,1),(50,471,1,'random',-1,0,1000,-1,6653.53,814.738,3.63802,275.77,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,100,2,NULL,1),(51,471,1,'random',-1,0,1000,-1,6655.18,803.947,3.67534,276.505,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,100,2,NULL,1),(52,471,1,'random',-1,0,1000,-1,6655.75,799.62,3.69975,292.791,0,0,-1,-1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,100,2,NULL,1),(53,456,3,'random',-1,0,1000,-1,4929.18,829.787,5.99373,270,0,0,28,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(54,414,3,'random',-1,0,1000,-1,4929.66,837.556,5.99373,270,0,0,25,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(55,456,3,'random',-1,0,1000,-1,4930.12,845.51,5.99373,270,0,0,43,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(56,456,3,'random',-1,0,1000,-1,4960.62,832.839,5.99373,90,0,0,67,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(57,414,3,'random',-1,0,1000,-1,4960.34,837.768,5.99373,90,0,0,72,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(58,456,3,'random',-1,0,1000,-1,4960.23,842.659,5.99373,90,0,0,9,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(59,456,3,'random',-1,0,1000,-1,4960.11,847.57,5.99373,90,0,0,95,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(60,414,3,'random',-1,0,1000,-1,4960.22,852.226,5.99373,90,0,0,24,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,2,1),(61,403,3,'random',-1,0,1000,-1,5110.79,-351.61,6.72148,247.946,0,0,36,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(62,515,3,'random',-1,0,1000,-1,5108.48,-356.917,7.27136,247.496,0,0,37,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(63,514,3,'random',-1,0,1000,-1,5106.98,-362.476,6.90879,247.954,0,0,30,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(64,403,3,'random',-1,0,1000,-1,5104.85,-367.059,6.89135,248.56,0,0,28,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(65,403,3,'random',-1,0,1000,-1,5099.62,-347.31,6.72036,68.072,0,0,25,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(66,514,3,'random',-1,0,1000,-1,5097.54,-353.135,6.8285,68.9184,0,0,40,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(67,403,3,'random',-1,0,1000,-1,5095.69,-358.684,6.8515,69.936,0,0,101,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(68,514,3,'random',-1,0,1000,-1,5094.07,-363.453,6.84266,70.8129,0,0,113,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(69,514,3,'random',-1,0,1000,-1,5133.06,-360.974,6.73789,159.691,0,0,36,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(70,515,3,'random',-1,0,1000,-1,5139.46,-363.242,6.72112,165.688,0,0,37,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(71,435,3,'random',-1,0,1000,-1,5170.14,-375.151,6.72233,71.7216,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(72,435,3,'random',-1,0,1000,-1,5168.02,-380.057,6.82053,74.2449,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(73,435,3,'random',-1,0,1000,-1,5166.71,-386.264,6.83944,68.1384,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(74,435,3,'random',-1,0,1000,-1,5165.51,-390.999,6.85457,71.7043,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(75,435,3,'random',-1,0,1000,-1,5164.07,-395.583,6.90862,68.8589,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(76,435,3,'random',-1,0,1000,-1,5161.7,-400.722,6.90211,67.1327,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(77,435,3,'random',-1,0,1000,-1,5105.33,-421.98,7.21014,338.978,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(78,435,3,'random',-1,0,1000,-1,5100.7,-419.874,7.20197,335.919,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(79,435,3,'random',-1,0,1000,-1,5095.45,-417.992,7.18937,331.45,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1),(80,435,3,'random',-1,0,1000,-1,5146.35,-363.296,6.71128,161.558,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0,0,-1,0,NULL,0,1,3,1);
/*!40000 ALTER TABLE `vehicles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehicles_shop_sunshine`
--

DROP TABLE IF EXISTS `vehicles_shop_sunshine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehicles_shop_sunshine` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `modelid` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `modelid` (`modelid`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicles_shop_sunshine`
--

LOCK TABLES `vehicles_shop_sunshine` WRITE;
/*!40000 ALTER TABLE `vehicles_shop_sunshine` DISABLE KEYS */;
INSERT INTO `vehicles_shop_sunshine` VALUES (1,400),(2,401),(3,402),(4,405),(5,410),(6,411),(7,412),(8,415),(9,418),(10,419),(11,421),(12,422),(13,424),(14,426),(15,429),(16,436),(17,439),(18,445),(19,451),(20,458),(21,461),(22,462),(23,463),(24,467),(25,468),(26,471),(27,474),(28,475),(29,477),(30,478),(31,479),(32,480),(33,483),(34,489),(35,491),(36,492),(37,496),(38,500),(39,505),(40,506),(41,507),(42,516),(43,517),(44,518),(45,521),(46,522),(47,526),(48,527),(49,529),(50,533),(51,534),(52,535),(53,536),(54,540),(55,541),(56,542),(57,543),(58,545),(59,546),(60,547),(61,549),(62,550),(63,551),(64,554),(65,555),(66,558),(67,559),(68,560),(69,561),(70,562),(71,565),(72,566),(73,567),(74,575),(75,576),(76,579),(77,580),(78,581),(79,585),(80,586),(81,587),(82,589),(83,600),(84,602),(85,603);
/*!40000 ALTER TABLE `vehicles_shop_sunshine` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-11-01 18:02:23
