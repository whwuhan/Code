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

 Date: 03/09/2020 15:12:21
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

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

SET FOREIGN_KEY_CHECKS = 1;
