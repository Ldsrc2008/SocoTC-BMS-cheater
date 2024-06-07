/*
  listen and decode TC 485 traffic

  query to BMS
  C5 5C 5A AA 01 97 96 0D
  below is a return form BMS
  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
  B6 6B AA 5A 0A 42 4D 1B 00 00 05 00 03 00 00 18 0D
  byte[4] is payload length, not including chksum(0x18) and end byte(0x0D)
  byte[5] is voltage
  byte[6] is percentage
  byte[7] maybe temp

  added IIC 16*2 LCD to show variable


*/
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // 設定i2c位址，一般情況就是0x27和0x3F兩種

// for BMS return data
byte voltage, percentage, temp;
const int analogInPin = A3;

void setup()
{
  lcd.begin(16, 2); // 初始化LCD


  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("V:");

  lcd.setCursor(7, 0);  //設定游標位置 (字,行)
  lcd.print("T:");



} // setup()

void loop()
{
  measurement();
  delay(10);
  lcd.setCursor(0, 1);
  lcd.print(percentage);
  lcd.print("%");
  lcd.setCursor(2, 0);  //設定游標位置 (字,行)
  lcd.print(voltage);
  lcd.setCursor(9, 0);  //設定游標位置 (字,行)
  lcd.print(temp);
} // loop()
