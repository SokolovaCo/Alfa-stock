SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `Storehouse` DEFAULT CHARACTER SET utf8 ;
USE `Storehouse` ;

-- -----------------------------------------------------
-- Table `Storehouse`.`Director`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Director` (
  `id_director` INT(10) NOT NULL AUTO_INCREMENT ,
  `surname` VARCHAR(50) NOT NULL ,
  `name` VARCHAR(50) NOT NULL ,
  `patronymic` VARCHAR(50) NOT NULL ,
  PRIMARY KEY (`id_director`) ,
  UNIQUE INDEX `id_director_UNIQUE` (`id_director` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Recipient`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Recipient` (
  `id_recipient` INT(10) NOT NULL AUTO_INCREMENT ,
  `recipient` VARCHAR(200) NOT NULL ,
  `address` VARCHAR(255) NOT NULL ,
  `id_director` INT(10) NOT NULL ,
  UNIQUE INDEX `id_recipient_UNIQUE` (`id_recipient` ASC) ,
  PRIMARY KEY (`id_recipient`) ,
  INDEX `fk_Recipient_Director1_idx` (`id_director` ASC) ,
  CONSTRAINT `fk_Recipient_Director1`
    FOREIGN KEY (`id_director` )
    REFERENCES `Storehouse`.`Director` (`id_director` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Firm`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Firm` (
  `id_firm` INT(10) NOT NULL AUTO_INCREMENT ,
  `firm` VARCHAR(100) NOT NULL ,
  UNIQUE INDEX `id_firm_UNIQUE` (`id_firm` ASC) ,
  UNIQUE INDEX `firma_UNIQUE` (`firm` ASC) ,
  PRIMARY KEY (`id_firm`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Unit`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Unit` (
  `id_unit` INT(10) NOT NULL AUTO_INCREMENT ,
  `unit` VARCHAR(40) NOT NULL ,
  UNIQUE INDEX `id_unit_UNIQUE` (`id_unit` ASC) ,
  UNIQUE INDEX `unit_UNIQUE` (`unit` ASC) ,
  PRIMARY KEY (`id_unit`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Type`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Type` (
  `id_type` INT(10) NOT NULL AUTO_INCREMENT ,
  `type` VARCHAR(100) NOT NULL ,
  PRIMARY KEY (`id_type`) ,
  UNIQUE INDEX `id_type_UNIQUE` (`id_type` ASC) ,
  UNIQUE INDEX `type_UNIQUE` (`type` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Subtype`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Subtype` (
  `id_subtype` INT(10) NOT NULL AUTO_INCREMENT ,
  `subtype` VARCHAR(100) NOT NULL ,
  `id_type` INT(10) NOT NULL ,
  UNIQUE INDEX `id_subtype_UNIQUE` (`id_subtype` ASC) ,
  PRIMARY KEY (`id_subtype`) ,
  INDEX `fk_Subtype_Type1_idx` (`id_type` ASC) ,
  CONSTRAINT `fk_Subtype_Type1`
    FOREIGN KEY (`id_type` )
    REFERENCES `Storehouse`.`Type` (`id_type` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Article`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Article` (
  `id_article` INT(10) NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(250) NOT NULL ,
  `id_firm` INT(10) NOT NULL ,
  `id_subtype` INT(10) NOT NULL ,
  `price` DOUBLE NOT NULL ,
  `size` FLOAT NOT NULL ,
  `id_unit` INT(10) NOT NULL ,
  UNIQUE INDEX `id_article_UNIQUE` (`id_article` ASC) ,
  PRIMARY KEY (`id_article`) ,
  INDEX `fk_Article_Firm1_idx` (`id_firm` ASC) ,
  INDEX `fk_Article_Unit1_idx` (`id_unit` ASC) ,
  INDEX `fk_Article_Subtype1_idx` (`id_subtype` ASC) ,
  CONSTRAINT `fk_Article_Firm1`
    FOREIGN KEY (`id_firm` )
    REFERENCES `Storehouse`.`Firm` (`id_firm` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Article_Unit1`
    FOREIGN KEY (`id_unit` )
    REFERENCES `Storehouse`.`Unit` (`id_unit` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Article_Subtype1`
    FOREIGN KEY (`id_subtype` )
    REFERENCES `Storehouse`.`Subtype` (`id_subtype` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Place`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Place` (
  `id_place` INT(10) NOT NULL AUTO_INCREMENT ,
  `line` INT(10) NOT NULL ,
  `point` INT(10) NOT NULL ,
  UNIQUE INDEX `id_place_UNIQUE` (`id_place` ASC) ,
  PRIMARY KEY (`id_place`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Storehouse`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Storehouse` (
  `id_item` BIGINT(20) NOT NULL AUTO_INCREMENT ,
  `id_article` INT(10) NOT NULL ,
  `id_place` INT(10) NOT NULL ,
  `availability` BINARY NOT NULL ,
  UNIQUE INDEX `id_item_UNIQUE` (`id_item` ASC) ,
  PRIMARY KEY (`id_item`) ,
  INDEX `fk_Storehouse_Article1_idx` (`id_article` ASC) ,
  INDEX `fk_Storehouse_Place1_idx` (`id_place` ASC) ,
  CONSTRAINT `fk_Storehouse_Article1`
    FOREIGN KEY (`id_article` )
    REFERENCES `Storehouse`.`Article` (`id_article` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Storehouse_Place1`
    FOREIGN KEY (`id_place` )
    REFERENCES `Storehouse`.`Place` (`id_place` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Shipment`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Shipment` (
  `id_shipment` INT(10) NOT NULL AUTO_INCREMENT ,
  `date` DATETIME NOT NULL ,
  `id_item` BIGINT(20) NOT NULL ,
  `id_recipient` INT(10) NOT NULL ,
  PRIMARY KEY (`id_shipment`) ,
  UNIQUE INDEX `id_shipment_UNIQUE` (`id_shipment` ASC) ,
  UNIQUE INDEX `id_item_UNIQUE` (`id_item` ASC) ,
  INDEX `fk_Shipment_Recipient1_idx` (`id_recipient` ASC) ,
  INDEX `fk_Shipment_Storehouse1_idx` (`id_item` ASC) ,
  CONSTRAINT `fk_Shipment_Recipient1`
    FOREIGN KEY (`id_recipient` )
    REFERENCES `Storehouse`.`Recipient` (`id_recipient` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Shipment_Storehouse1`
    FOREIGN KEY (`id_item` )
    REFERENCES `Storehouse`.`Storehouse` (`id_item` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Supplier`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Supplier` (
  `id_supplier` INT(10) NOT NULL AUTO_INCREMENT ,
  `suplier` VARCHAR(200) NOT NULL ,
  `address` VARCHAR(255) NOT NULL ,
  `id_director` INT(10) NOT NULL ,
  UNIQUE INDEX `id_supplier_UNIQUE` (`id_supplier` ASC) ,
  PRIMARY KEY (`id_supplier`) ,
  INDEX `fk_Supplier_Director1_idx` (`id_director` ASC) ,
  CONSTRAINT `fk_Supplier_Director1`
    FOREIGN KEY (`id_director` )
    REFERENCES `Storehouse`.`Director` (`id_director` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Delivery`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Delivery` (
  `id_delivery` INT(10) NOT NULL AUTO_INCREMENT ,
  `date` DATETIME NOT NULL ,
  `id_item` BIGINT(20) NOT NULL ,
  `id_supplier` INT(10) NOT NULL ,
  PRIMARY KEY (`id_delivery`) ,
  UNIQUE INDEX `id_delivery_UNIQUE` (`id_delivery` ASC) ,
  UNIQUE INDEX `id_item_UNIQUE` (`id_item` ASC) ,
  INDEX `fk_Delivery_Supplier1_idx` (`id_supplier` ASC) ,
  INDEX `fk_Delivery_Storehouse1_idx` (`id_item` ASC) ,
  CONSTRAINT `fk_Delivery_Supplier1`
    FOREIGN KEY (`id_supplier` )
    REFERENCES `Storehouse`.`Supplier` (`id_supplier` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Delivery_Storehouse1`
    FOREIGN KEY (`id_item` )
    REFERENCES `Storehouse`.`Storehouse` (`id_item` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
