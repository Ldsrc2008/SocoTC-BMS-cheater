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
LiquidCrystal_PCF8574 lcd(0x27);  // 設定i2c位址

byte testing_BMS_return[17] = {0xB6, 0x6B, 0xAA, 0x5A, 0x0A, 0x42, 0x4D, 0x1B, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x18, 0x0D};
//                                                           ^^^^  ^^^^  ^^^^
byte returned_array[17];
int index = 0;
int msg_received = 0;
byte BMS_data[10];
byte controller_data[10];

// for BMS return data
byte voltage, percentage, temp;
const int analogInPin = A3;
// for RS485 connected on software serial 10/11
#include <SoftwareSerial.h>
SoftwareSerial Master(10, 11);//rx,tx
int DE_RE = 2;


void setup()
{
  Serial.begin(9600);
  delay(10);
  Master.begin(9600);

  pinMode(DE_RE, OUTPUT);

  digitalWrite(DE_RE, LOW);

  lcd.begin(16, 2); // 初始化LCD
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("V:");
  lcd.setCursor(0, 1);  //設定游標位置 (字,行)
  lcd.print("T:");


} // setup()

void loop()
{
  measurement();
  delay(10);
  ShowLED();
  while (Master.available()) {
    if (check_coming_byte(Master.read()) == true)
    {
      after_received();
    }
  }// end of while


} // loop()
// decode function
/* get bytes from serial and fill in to buffer base on header

*/
bool check_coming_byte(byte c) {
  switch (c)
  {
    case 0x0D: // end of messge

      returned_array[index] = c;
      index = 0; //
      return true; // we should have a message in array
      break;

    default:// normal bytes

      returned_array[index] = c;
      ++index;
      return false;
  }// end of switch
}// end of check coming byte
