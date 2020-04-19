-- MySQL dump 10.16  Distrib 10.1.37-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: vc_anticheat
-- ------------------------------------------------------
-- Server version	10.1.37-MariaDB-0+deb9u1

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
-- Table structure for table `anticheats`
--

DROP TABLE IF EXISTS `anticheats`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `anticheats` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL,
  `enabled` tinyint(1) NOT NULL DEFAULT '1',
  `detections` int(11) NOT NULL DEFAULT '1',
  `in_seconds` int(11) NOT NULL DEFAULT '0',
  `min_seconds` int(11) NOT NULL DEFAULT '1',
  `kick` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `anticheats`
--

LOCK TABLES `anticheats` WRITE;
/*!40000 ALTER TABLE `anticheats` DISABLE KEYS */;
INSERT INTO `anticheats` VALUES (1,'WEAPONS',1,1,0,1,1),(2,'AMMO',1,1,0,1,1),(3,'POSITION',1,5,2,1,0),(4,'TELEPORT',1,1,0,1,1),(5,'PLAYER_SPEED',1,1,0,1,1),(6,'SPECIAL_ACTION',1,1,0,1,1),(7,'ENTER_CLOSED_VEHICLE',1,1,0,1,1),(8,'STATE_CHANGE_FLOODER',1,10,5,0,1),(9,'VEHICLE_SPEED',1,1,0,1,1),(10,'TEXT_FLOODER',1,10,5,0,1),(11,'COMMAND_FLOODER',1,10,5,1,1),(12,'VEHICLE_MOD',1,1,0,1,1),(13,'HEALTH',1,1,0,1,1),(14,'ARMOUR',1,1,0,1,1),(15,'VEHICLE_HEALTH',1,1,0,1,1);
/*!40000 ALTER TABLE `anticheats` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `variables`
--

DROP TABLE IF EXISTS `variables`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `variables` (
  `varname` varchar(32) NOT NULL,
  `value` varchar(24) NOT NULL,
  PRIMARY KEY (`varname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `variables`
--

LOCK TABLES `variables` WRITE;
/*!40000 ALTER TABLE `variables` DISABLE KEYS */;
INSERT INTO `variables` VALUES ('default_flooder_maxinterval','50'),('default_protection_seconds','3'),('playerspeed_maxvalue','1000'),('position_distance_foot','8.0'),('position_distance_vehicle','10.0'),('position_distance_vehicle_ms','20.0'),('teleport_distance','80.0'),('vehiclespeed_maxvalue','1000'),('vehiclespeed_offset_maxvalue','100');
/*!40000 ALTER TABLE `variables` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-11-01 12:34:55
