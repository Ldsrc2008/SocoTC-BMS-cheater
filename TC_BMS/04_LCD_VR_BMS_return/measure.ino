void measurement(void) {

  voltage = map(analogRead(analogInPin), 0, 1023, 50, 75);
  percentage = map(analogRead(analogInPin), 0, 1023, 10, 99);
  temp = map(analogRead(analogInPin), 0, 1023, 10, 80);
  testing_BMS_return[5] = voltage;
  testing_BMS_return[6] = percentage;
  testing_BMS_return[7] = temp;
}// end of measurement

void  ShowLED(void) {

  lcd.setCursor(2, 1);
  lcd.print(temp);

  lcd.setCursor(2, 0);  //設定游標位置 (字,行)
  lcd.print(voltage);
  lcd.setCursor(9, 0);  //設定游標位置 (字,行)
  lcd.print(percentage);
    lcd.print("%");
}// end of show led
