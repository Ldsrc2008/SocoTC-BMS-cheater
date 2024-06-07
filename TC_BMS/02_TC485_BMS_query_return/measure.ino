/*
  measure the voltage, percentage and temp..
  here I use a vr to map values


  voltage, percentage, temp;
*/


void measurement(void) {

  voltage = map(analogRead(analogInPin), 0, 1023, 0, 75);
  percentage = map(analogRead(analogInPin), 0, 1023, 0, 100);
  temp = map(analogRead(analogInPin), 0, 1023, 0, 100);
  testing_BMS_return[5] = voltage;
  testing_BMS_return[6] = percentage;
  testing_BMS_return[7] = temp;
}// end of measurement
