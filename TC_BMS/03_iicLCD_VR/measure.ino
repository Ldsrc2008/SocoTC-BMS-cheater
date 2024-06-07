void measurement(void) {

  voltage = map(analogRead(analogInPin), 0, 1023, 50, 75);
  percentage = map(analogRead(analogInPin), 0, 1023, 10, 99);
  temp = map(analogRead(analogInPin), 0, 1023, 10, 80);
//  testing_BMS_return[5] = voltage;
 // testing_BMS_return[6] = percentage;
 // testing_BMS_return[7] = temp;
}// end of measurement
