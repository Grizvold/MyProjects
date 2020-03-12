/*CREATE DATABASE Computer_Firm;
USE Computer_Firm;
SOURCE /home..../computer_mysql_script;*/
/* Port: 3306 */
/* Database: Computer_Firm */
/* Username: root */
/* /home/student/.SQLTools/Connection Session.sql */

SHOW tables;
DESCRIBE PC;
DESCRIBE Product;
DESCRIBE Printer color;

/*  1   */
SELECT model, speed, hd FROM PC WHERE price < 500;

/*  2   */
SELECT DISTINCT maker from Product WHERE type = "Printer";

/*  3   */
SELECT model, ram, screen FROM Laptop WHERE price > 1000;

/*  4   */
SELECT color FROM Printer;
SELECT model FROM Printer WHERE color = 'y';

/*  5   */
SELECT cd FROM PC;
SELECT model, speed, hd FROM PC WHERE (cd = '12x' OR cd = '24x') AND price < 600;

/*  6   */
SELECT hd FROM Laptop;
SELECT maker, speed FROM Laptop JOIN Product USING(model) WHERE hd >= 10;

/*  7   */
SELECT maker FROM Product;
SELECT model, price FROM Product JOIN Laptop USING(model) WHERE maker = 'B'
        UNION
        SELECT model, price FROM Product JOIN PC USING(model) WHERE maker = 'B'
        UNION
        SELECT model, price FROM Product JOIN Printer USING(model) WHERE maker = 'B'

/*  8   */
SELECT DISTINCT maker FROM Product WHERE type = 'PC' 
        AND maker NOT IN(SELECT maker FROM Product WHERE type = 'Laptop'); 



        

