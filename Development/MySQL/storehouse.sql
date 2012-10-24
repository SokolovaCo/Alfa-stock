SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `Storehouse` DEFAULT CHARACTER SET utf8 ;
USE `Storehouse` ;

-- -----------------------------------------------------
-- Table `Storehouse`.`Shipment`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Shipment` (
  `id_shipment` BIGINT NOT NULL AUTO_INCREMENT ,
  `date` DATETIME NOT NULL ,
  `id_item` BIGINT NOT NULL ,
  `id_recipient` INT NOT NULL ,
  PRIMARY KEY (`id_shipment`) ,
  UNIQUE INDEX `id_shipment_UNIQUE` (`id_shipment` ASC) ,
  UNIQUE INDEX `id_item_UNIQUE` (`id_item` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Delivery`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Delivery` (
  `id_delivery` BIGINT NOT NULL AUTO_INCREMENT ,
  `date` DATETIME NOT NULL ,
  `id_item` BIGINT NOT NULL ,
  `id_supplier` INT NOT NULL ,
  PRIMARY KEY (`id_delivery`) ,
  UNIQUE INDEX `id_delivery_UNIQUE` (`id_delivery` ASC) ,
  UNIQUE INDEX `id_item_UNIQUE` (`id_item` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Supplier`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Supplier` (
  `id_supplier` INT NOT NULL AUTO_INCREMENT ,
  `suplier` TINYTEXT NOT NULL ,
  `address` TINYTEXT NOT NULL ,
  `id_director` INT NOT NULL ,
  PRIMARY KEY (`id_supplier`) ,
  UNIQUE INDEX `id_supplier_UNIQUE` (`id_supplier` ASC) ,
  CONSTRAINT `fk_Supplier_Delivery1`
    FOREIGN KEY (`id_supplier` )
    REFERENCES `Storehouse`.`Delivery` (`id_supplier` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Recipient`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Recipient` (
  `id_recipient` INT NOT NULL AUTO_INCREMENT ,
  `recipient` TINYTEXT NOT NULL ,
  `address` TINYTEXT NOT NULL ,
  `id_director` INT NOT NULL ,
  PRIMARY KEY (`id_recipient`) ,
  UNIQUE INDEX `id_recipient_UNIQUE` (`id_recipient` ASC) ,
  CONSTRAINT `fk_Recipient_Shipment1`
    FOREIGN KEY (`id_recipient` )
    REFERENCES `Storehouse`.`Shipment` (`id_recipient` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Storehouse`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Storehouse` (
  `id_item` BIGINT NOT NULL AUTO_INCREMENT ,
  `id_article` INT NOT NULL ,
  `id_place` INT NOT NULL ,
  `availability` TINYTEXT NOT NULL ,
  PRIMARY KEY (`id_item`) ,
  UNIQUE INDEX `id_item_UNIQUE` (`id_item` ASC) ,
  CONSTRAINT `fk_Storehouse_Shipment1`
    FOREIGN KEY (`id_item` )
    REFERENCES `Storehouse`.`Shipment` (`id_item` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Storehouse_Delivery1`
    FOREIGN KEY (`id_item` )
    REFERENCES `Storehouse`.`Delivery` (`id_item` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Article`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Article` (
  `id_article` INT NOT NULL AUTO_INCREMENT ,
  `name` TINYTEXT NOT NULL ,
  `id_firm` INT NOT NULL ,
  `id_subtype` INT NOT NULL ,
  `price` DOUBLE NOT NULL ,
  `size` FLOAT NOT NULL ,
  `id_unit` INT NOT NULL ,
  PRIMARY KEY (`id_article`) ,
  UNIQUE INDEX `id_article_UNIQUE` (`id_article` ASC) ,
  CONSTRAINT `fk_Article_Storehouse1`
    FOREIGN KEY (`id_article` )
    REFERENCES `Storehouse`.`Storehouse` (`id_article` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Firm`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Firm` (
  `id_firm` INT NOT NULL AUTO_INCREMENT ,
  `firm` TINYINT NOT NULL ,
  PRIMARY KEY (`id_firm`) ,
  UNIQUE INDEX `id_firm_UNIQUE` (`id_firm` ASC) ,
  UNIQUE INDEX `firma_UNIQUE` (`firm` ASC) ,
  CONSTRAINT `fk_Firm_Article`
    FOREIGN KEY (`id_firm` )
    REFERENCES `Storehouse`.`Article` (`id_firm` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Unit`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Unit` (
  `id_unit` INT NOT NULL AUTO_INCREMENT ,
  `unit` TINYTEXT NOT NULL ,
  PRIMARY KEY (`id_unit`) ,
  UNIQUE INDEX `id_unit_UNIQUE` (`id_unit` ASC) ,
  UNIQUE INDEX `unit_UNIQUE` (`unit` ASC) ,
  CONSTRAINT `fk_Unit_Article1`
    FOREIGN KEY (`id_unit` )
    REFERENCES `Storehouse`.`Article` (`id_unit` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Place`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Place` (
  `id_place` INT NOT NULL AUTO_INCREMENT ,
  `line` INT NOT NULL ,
  `point` INT NOT NULL ,
  PRIMARY KEY (`id_place`) ,
  UNIQUE INDEX `id_place_UNIQUE` (`id_place` ASC) ,
  CONSTRAINT `fk_Place_Storehouse1`
    FOREIGN KEY (`id_place` )
    REFERENCES `Storehouse`.`Storehouse` (`id_place` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Subtype`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Subtype` (
  `id_subtype` INT NOT NULL AUTO_INCREMENT ,
  `subtype` TINYTEXT NOT NULL ,
  `id_type` INT NOT NULL ,
  PRIMARY KEY (`id_subtype`) ,
  UNIQUE INDEX `id_subtype_UNIQUE` (`id_subtype` ASC) ,
  UNIQUE INDEX `subtype_UNIQUE` (`subtype` ASC) ,
  CONSTRAINT `fk_Subtype_Article1`
    FOREIGN KEY (`id_subtype` )
    REFERENCES `Storehouse`.`Article` (`id_subtype` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Type`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Type` (
  `id_type` INT NOT NULL AUTO_INCREMENT ,
  `type` TINYTEXT NOT NULL ,
  PRIMARY KEY (`id_type`) ,
  UNIQUE INDEX `id_type_UNIQUE` (`id_type` ASC) ,
  UNIQUE INDEX `type_UNIQUE` (`type` ASC) ,
  CONSTRAINT `fk_Type_Subtype1`
    FOREIGN KEY (`id_type` )
    REFERENCES `Storehouse`.`Subtype` (`id_type` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Storehouse`.`Director`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `Storehouse`.`Director` (
  `id_director` INT NOT NULL AUTO_INCREMENT ,
  `surname` TINYTEXT NOT NULL ,
  `name` TINYTEXT NOT NULL ,
  `patronymic` TINYTEXT NOT NULL ,
  PRIMARY KEY (`id_director`) ,
  UNIQUE INDEX `id_director_UNIQUE` (`id_director` ASC) ,
  CONSTRAINT `fk_Director_Recipient1`
    FOREIGN KEY (`id_director` )
    REFERENCES `Storehouse`.`Recipient` (`id_director` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Director_Supplier1`
    FOREIGN KEY (`id_director` )
    REFERENCES `Storehouse`.`Supplier` (`id_director` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
