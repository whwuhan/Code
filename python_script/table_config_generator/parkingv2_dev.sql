/*
 Navicat Premium Data Transfer

 Source Server         : cdb-mzvws756.cd.tencentcdb.com
 Source Server Type    : MySQL
 Source Server Version : 50718
 Source Host           : cdb-mzvws756.cd.tencentcdb.com:10143
 Source Schema         : parkingv2_dev

 Target Server Type    : MySQL
 Target Server Version : 50718
 File Encoding         : 65001

 Date: 03/09/2020 15:55:06
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for area
-- ----------------------------
DROP TABLE IF EXISTS `area`;
CREATE TABLE `area` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) NOT NULL COMMENT '区域名称',
  `cityId` bigint(20) NOT NULL COMMENT '城市编号',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_city_UNIQUE` (`name`,`cityId`),
  KEY `fk_area_city_idx` (`cityId`),
  CONSTRAINT `fk_area_city` FOREIGN KEY (`cityId`) REFERENCES `city` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8 COMMENT='区域';

-- ----------------------------
-- Table structure for basicPricingRule
-- ----------------------------
DROP TABLE IF EXISTS `basicPricingRule`;
CREATE TABLE `basicPricingRule` (
  `name` varchar(50) NOT NULL COMMENT '计费方式名称',
  `freePeriod` int(11) DEFAULT NULL COMMENT '免费停车时长',
  `maxPrice` decimal(10,2) DEFAULT NULL COMMENT '最高限额',
  `limitPeriod` int(11) DEFAULT NULL COMMENT '限制时长',
  `timeUnit` int(11) DEFAULT NULL COMMENT '单位时长',
  `priceUnit` decimal(5,2) DEFAULT NULL COMMENT '单位费率',
  `description` varchar(100) DEFAULT NULL COMMENT '描述',
  `parameter` text COMMENT '计费区间定价，JSON格式存储，格式为[{"startMinute": 0,"endMinute": 480,"price": 2.0},{"startMinute": 480,"endMinute": 720,"price": 5.0}]',
  PRIMARY KEY (`name`),
  UNIQUE KEY `basic_rule_idx` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='基本计费方式参数';

-- ----------------------------
-- Table structure for car
-- ----------------------------
DROP TABLE IF EXISTS `car`;
CREATE TABLE `car` (
  `id` bigint(20) NOT NULL,
  `numberPlate` varchar(50) NOT NULL COMMENT '车牌号',
  `carOwnerId` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `numberPlate_UNIQUE` (`numberPlate`),
  KEY `fk_car_carOwner1_idx` (`carOwnerId`),
  CONSTRAINT `fk_car_carOwner1` FOREIGN KEY (`carOwnerId`) REFERENCES `carOwner` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='车辆';

-- ----------------------------
-- Table structure for carOwner
-- ----------------------------
DROP TABLE IF EXISTS `carOwner`;
CREATE TABLE `carOwner` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL COMMENT '车主姓名',
  `tel` varchar(50) NOT NULL COMMENT '电话',
  `registerTime` datetime NOT NULL COMMENT '注册时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `tel_UNIQUE` (`tel`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='车主';

-- ----------------------------
-- Table structure for city
-- ----------------------------
DROP TABLE IF EXISTS `city`;
CREATE TABLE `city` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) NOT NULL COMMENT '城市（县市）名',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8 COMMENT='城市（县市）';

-- ----------------------------
-- Table structure for config
-- ----------------------------
DROP TABLE IF EXISTS `config`;
CREATE TABLE `config` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '设置编号',
  `configName` varchar(255) NOT NULL COMMENT '设置名',
  `configJson` text NOT NULL COMMENT '设置内容',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT='设置';

-- ----------------------------
-- Table structure for dailyPricingRule
-- ----------------------------
DROP TABLE IF EXISTS `dailyPricingRule`;
CREATE TABLE `dailyPricingRule` (
  `name` varchar(50) NOT NULL COMMENT '费率类别名称',
  `sequential` tinyint(1) DEFAULT NULL COMMENT '是否首尾相连',
  `description` varchar(100) DEFAULT NULL COMMENT '描述',
  PRIMARY KEY (`name`),
  UNIQUE KEY `daiyly_rule_idx` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='每日费率设置';

-- ----------------------------
-- Table structure for dailyPricingRuleParameter
-- ----------------------------
DROP TABLE IF EXISTS `dailyPricingRuleParameter`;
CREATE TABLE `dailyPricingRuleParameter` (
  `dailyRuleName` varchar(50) DEFAULT NULL COMMENT '费率类别名称',
  `basicRulename` varchar(50) DEFAULT NULL COMMENT '计费方式名称',
  `startTime` time NOT NULL COMMENT '起始时间',
  `endTime` time NOT NULL COMMENT '截止时间',
  KEY `FK_Reference_1` (`dailyRuleName`),
  KEY `FK_Reference_2` (`basicRulename`),
  CONSTRAINT `FK_Reference_1` FOREIGN KEY (`dailyRuleName`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_2` FOREIGN KEY (`basicRulename`) REFERENCES `basicPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='每日费率类别设置映射';

-- ----------------------------
-- Table structure for employee
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `positionId` bigint(20) NOT NULL,
  `sn` varchar(50) NOT NULL COMMENT '员工编号',
  `name` varchar(50) NOT NULL COMMENT '姓名',
  `tel` varchar(50) NOT NULL COMMENT '手机号',
  `status` varchar(50) NOT NULL DEFAULT '正常' COMMENT '状态',
  `deleted` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `sn_UNIQUE` (`sn`),
  KEY `fk_employee_position1` (`positionId`),
  CONSTRAINT `fk_employee_position1` FOREIGN KEY (`positionId`) REFERENCES `position` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT='员工';

-- ----------------------------
-- Table structure for holiday
-- ----------------------------
DROP TABLE IF EXISTS `holiday`;
CREATE TABLE `holiday` (
  `name` varchar(50) NOT NULL COMMENT '节假日名称',
  `startDate` date NOT NULL COMMENT '节假日起始日期',
  `endDate` date NOT NULL COMMENT '节假日结束日期',
  PRIMARY KEY (`name`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='节假日';

-- ----------------------------
-- Table structure for parkingLot
-- ----------------------------
DROP TABLE IF EXISTS `parkingLot`;
CREATE TABLE `parkingLot` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '停车场ID',
  `sn` varchar(50) NOT NULL COMMENT '停车场编号',
  `name` varchar(50) NOT NULL COMMENT '停车场名称',
  `type` varchar(25) NOT NULL COMMENT '停车场类型，路边停车/停车场',
  `latitude` decimal(5,2) NOT NULL COMMENT '停车场位置纬度',
  `longitude` decimal(5,2) NOT NULL COMMENT '停车场位置经度',
  `sectionId` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_section_UNIQUE` (`name`,`sectionId`),
  UNIQUE KEY `sn_UNIQUE` (`sn`),
  KEY `fk_parking_lot_section1_idx` (`sectionId`),
  CONSTRAINT `fk_parking_lot_section1` FOREIGN KEY (`sectionId`) REFERENCES `section` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COMMENT='停车场';

-- ----------------------------
-- Table structure for parkingRecord
-- ----------------------------
DROP TABLE IF EXISTS `parkingRecord`;
CREATE TABLE `parkingRecord` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '停车记录ID',
  `parkingSpaceId` bigint(20) NOT NULL COMMENT '停车位ID',
  `numberPlate` varchar(20) NOT NULL COMMENT '车牌号',
  `arriveTime` datetime NOT NULL COMMENT '入场时间',
  `leaveTime` datetime DEFAULT NULL COMMENT '离场时间',
  `paid` tinyint(1) NOT NULL COMMENT '是否已支付(1为已支付，0为未支付)',
  `arrivePic` varchar(200) DEFAULT NULL COMMENT '入场照片路径',
  `leavePic` varchar(200) DEFAULT NULL COMMENT '离场照片路径',
  `fee` decimal(8,2) DEFAULT NULL COMMENT '停车金额',
  `payTime` datetime DEFAULT NULL COMMENT '支付时间',
  PRIMARY KEY (`id`),
  KEY `FK_Reference_2` (`parkingSpaceId`),
  CONSTRAINT `parking_record_ibfk_1` FOREIGN KEY (`parkingSpaceId`) REFERENCES `parkingSpace` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8 COMMENT='停车记录';

-- ----------------------------
-- Table structure for parkingSpace
-- ----------------------------
DROP TABLE IF EXISTS `parkingSpace`;
CREATE TABLE `parkingSpace` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '停车位ID',
  `sn` varchar(50) NOT NULL COMMENT '停车位编号',
  `parkingLotId` bigint(20) NOT NULL COMMENT '停车场ID',
  `free` tinyint(1) NOT NULL COMMENT '车位状态，0：有车，1：空位',
  `pricingRuleName` varchar(50) DEFAULT NULL COMMENT '计费规则名称',
  PRIMARY KEY (`id`),
  UNIQUE KEY `sn_parkingLot_UNIQUE` (`sn`,`parkingLotId`),
  KEY `FK_Reference_1` (`parkingLotId`),
  KEY `pricing_rule_name` (`pricingRuleName`),
  CONSTRAINT `parking_space_ibfk_1` FOREIGN KEY (`parkingLotId`) REFERENCES `parkingLot` (`id`),
  CONSTRAINT `pricing_rule_name` FOREIGN KEY (`pricingRuleName`) REFERENCES `pricingRule` (`name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8 COMMENT='停车位';

-- ----------------------------
-- Table structure for payment
-- ----------------------------
DROP TABLE IF EXISTS `payment`;
CREATE TABLE `payment` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `wechatSN` varchar(200) DEFAULT NULL COMMENT '微信订单号',
  `status` varchar(50) NOT NULL COMMENT '支付状态',
  `createdTime` datetime NOT NULL COMMENT '创建时间',
  `payTime` datetime DEFAULT NULL COMMENT '支付完成时间',
  `deleted` tinyint(4) NOT NULL DEFAULT '0' COMMENT '删除标记',
  `parkingRecordId` bigint(20) NOT NULL,
  `fee` decimal(8,2) NOT NULL COMMENT '支付费用',
  `stayTime` int(11) NOT NULL COMMENT '停留时间',
  `arriveTime` datetime NOT NULL COMMENT '到达时间',
  `sensorSn` varchar(50) DEFAULT NULL COMMENT '传感器编号',
  `numberPlate` varchar(20) NOT NULL COMMENT '车牌号',
  `arrivePic` varchar(200) NOT NULL COMMENT '到达照片',
  PRIMARY KEY (`id`),
  KEY `fk_payment_parkingRecord1_idx` (`parkingRecordId`),
  KEY `wechatSN_UNIQUE` (`wechatSN`) USING BTREE,
  CONSTRAINT `fk_payment_parkingRecord1` FOREIGN KEY (`parkingRecordId`) REFERENCES `parkingRecord` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8 COMMENT='支付订单';

-- ----------------------------
-- Table structure for photoRecord
-- ----------------------------
DROP TABLE IF EXISTS `photoRecord`;
CREATE TABLE `photoRecord` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `sensorId` bigint(20) DEFAULT NULL,
  `path` varchar(200) NOT NULL COMMENT '图片存储路径',
  `numberPlate` varchar(20) DEFAULT NULL COMMENT '识别的车牌号',
  `shootTime` datetime NOT NULL COMMENT '拍摄时间',
  `type` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_photoRecord_sensor1_idx` (`sensorId`),
  CONSTRAINT `fk_photoRecord_sensor1` FOREIGN KEY (`sensorId`) REFERENCES `sensor` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT='拍照记录';

-- ----------------------------
-- Table structure for position
-- ----------------------------
DROP TABLE IF EXISTS `position`;
CREATE TABLE `position` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `parkingLotId` bigint(20) NOT NULL,
  `name` varchar(200) NOT NULL COMMENT '岗位名',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_parkingLot_UNIQUE` (`name`,`parkingLotId`),
  KEY `fk_position_parkingLot1_idx` (`parkingLotId`),
  CONSTRAINT `fk_position_parkingLot1` FOREIGN KEY (`parkingLotId`) REFERENCES `parkingLot` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COMMENT='岗位';

-- ----------------------------
-- Table structure for pricingRule
-- ----------------------------
DROP TABLE IF EXISTS `pricingRule`;
CREATE TABLE `pricingRule` (
  `name` varchar(50) NOT NULL COMMENT '每周计费类型名称',
  `d1` varchar(50) NOT NULL COMMENT '星期1费率类别名称',
  `d2` varchar(50) NOT NULL COMMENT '星期2费率类别名称',
  `d3` varchar(50) NOT NULL COMMENT '星期3费率类别名称',
  `d4` varchar(50) NOT NULL COMMENT '星期4费率类别名称',
  `d5` varchar(50) NOT NULL COMMENT '星期5费率类别名称',
  `d6` varchar(50) NOT NULL COMMENT '星期6费率类别名称',
  `d7` varchar(50) NOT NULL COMMENT '星期7费率类别名称',
  `holiday` varchar(50) NOT NULL COMMENT '假期费率类别名称',
  `combineFees` tinyint(1) DEFAULT NULL COMMENT '是否合并收费',
  `maxFee` decimal(10,2) DEFAULT NULL COMMENT '每日最高收费',
  `periodUnit` int(11) DEFAULT NULL COMMENT '单位时长',
  `fixedPeriod` int(11) DEFAULT NULL COMMENT '修正时间',
  `discount` decimal(10,0) DEFAULT NULL COMMENT '新能源车折扣',
  `effectiveDate` datetime NOT NULL COMMENT '生效日期',
  `description` varchar(100) DEFAULT NULL COMMENT '温馨提示',
  PRIMARY KEY (`name`),
  UNIQUE KEY `pricing_rule_idx` (`name`),
  KEY `FK_Reference_10` (`holiday`),
  KEY `FK_Reference_3` (`d1`),
  KEY `FK_Reference_4` (`d2`),
  KEY `FK_Reference_5` (`d3`),
  KEY `FK_Reference_6` (`d4`),
  KEY `FK_Reference_7` (`d5`),
  KEY `FK_Reference_8` (`d6`),
  KEY `FK_Reference_9` (`d7`),
  CONSTRAINT `FK_Reference_10` FOREIGN KEY (`holiday`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_3` FOREIGN KEY (`d1`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_4` FOREIGN KEY (`d2`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_5` FOREIGN KEY (`d3`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_6` FOREIGN KEY (`d4`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_7` FOREIGN KEY (`d5`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_8` FOREIGN KEY (`d6`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `FK_Reference_9` FOREIGN KEY (`d7`) REFERENCES `dailyPricingRule` (`name`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='每周计费类型设置';

-- ----------------------------
-- Table structure for requestLog
-- ----------------------------
DROP TABLE IF EXISTS `requestLog`;
CREATE TABLE `requestLog` (
  `requestUid` varchar(128) NOT NULL COMMENT '请求uuid',
  `requestType` varchar(255) NOT NULL COMMENT '请求类型',
  `requestJson` text NOT NULL COMMENT '请求内容',
  `requestTime` datetime NOT NULL COMMENT '请求时间',
  PRIMARY KEY (`requestUid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='请求日志';

-- ----------------------------
-- Table structure for section
-- ----------------------------
DROP TABLE IF EXISTS `section`;
CREATE TABLE `section` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) NOT NULL COMMENT '路段名称',
  `streetId` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_street_UNIQUE` (`name`,`streetId`),
  KEY `fk_section_street1_idx` (`streetId`),
  CONSTRAINT `fk_section_street1` FOREIGN KEY (`streetId`) REFERENCES `street` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8 COMMENT='路段';

-- ----------------------------
-- Table structure for sensor
-- ----------------------------
DROP TABLE IF EXISTS `sensor`;
CREATE TABLE `sensor` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '传感器设备ID',
  `sn` varchar(255) NOT NULL COMMENT '传感器SN码',
  `status` varchar(50) NOT NULL DEFAULT '正常' COMMENT '设备状态',
  `parkingSpaceId` bigint(20) DEFAULT NULL COMMENT '停车位ID',
  `initialPower` decimal(5,2) NOT NULL COMMENT '初始电量',
  `realPower` decimal(5,2) NOT NULL COMMENT '真实电量',
  `sensorType` varchar(64) NOT NULL COMMENT '设备类型',
  PRIMARY KEY (`id`),
  UNIQUE KEY `sn_UNIQUE` (`sn`),
  UNIQUE KEY `parkingSpaceId_UNIQUE` (`parkingSpaceId`),
  KEY `FK_Reference_3` (`parkingSpaceId`),
  CONSTRAINT `sensor_ibfk_1` FOREIGN KEY (`parkingSpaceId`) REFERENCES `parkingSpace` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8 COMMENT='传感器设备';

-- ----------------------------
-- Table structure for sensorAlarmRecord
-- ----------------------------
DROP TABLE IF EXISTS `sensorAlarmRecord`;
CREATE TABLE `sensorAlarmRecord` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `sensorId` bigint(20) NOT NULL COMMENT '传感器设备ID',
  `alarmTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `alarmType` varchar(255) NOT NULL COMMENT '报警类型',
  PRIMARY KEY (`id`),
  KEY `FK_Reference_4` (`sensorId`),
  CONSTRAINT `sensor_alarm_record_ibfk_1` FOREIGN KEY (`sensorId`) REFERENCES `sensor` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT='设备报警记录';

-- ----------------------------
-- Table structure for street
-- ----------------------------
DROP TABLE IF EXISTS `street`;
CREATE TABLE `street` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(200) NOT NULL COMMENT '街道名',
  `areaId` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_area_UNIQUE` (`name`,`areaId`),
  KEY `fk_street_area1_idx` (`areaId`),
  CONSTRAINT `fk_street_area1` FOREIGN KEY (`areaId`) REFERENCES `area` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8 COMMENT='街道';

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '平台管理员ID',
  `account` varchar(25) NOT NULL COMMENT '登录账号',
  `password` varchar(200) NOT NULL COMMENT '登录密码',
  `tel` varchar(50) NOT NULL COMMENT '联系电话',
  `name` varchar(30) NOT NULL COMMENT '姓名',
  `roles` varchar(200) NOT NULL COMMENT '用户角色',
  `parkingLotId` bigint(20) DEFAULT NULL COMMENT '所属停车场ID',
  PRIMARY KEY (`id`),
  UNIQUE KEY `account_UNIQUE` (`account`),
  KEY `parking_lot_id` (`parkingLotId`),
  CONSTRAINT `parking_lot_id` FOREIGN KEY (`parkingLotId`) REFERENCES `parkingLot` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=63 DEFAULT CHARSET=utf8 COMMENT='平台管理员';

-- ----------------------------
-- View structure for snview
-- ----------------------------
DROP VIEW IF EXISTS `snview`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`%` SQL SECURITY DEFINER VIEW `snview` AS select `a`.`id` AS `sensor_id`,`b`.`id` AS `parkingLot_id`,`a`.`sn` AS `sn`,`a`.`status` AS `status`,`a`.`realPower` AS `realPower`,`a`.`sensorType` AS `sensorType`,`b`.`free` AS `free`,`b`.`pricingRuleName` AS `pricingRuleName` from (`sensor` `a` join `parkingSpace` `b` on((`a`.`parkingSpaceId` = `b`.`id`))) where (`a`.`sn` = 'SN01');

SET FOREIGN_KEY_CHECKS = 1;
