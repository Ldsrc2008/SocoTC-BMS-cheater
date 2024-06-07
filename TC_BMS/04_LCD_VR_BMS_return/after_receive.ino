void after_received(void) {

  // Serial.println("message receive");

  // Serial.write(returned_array, sizeof(returned_array));
  /* how to judage 4 diffferent message?
     0  1  2  3  4  5  6  7  8
    C5 5C DA AA 02 00 00 02 0D
     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    B6 6B AA DA 0A 01 00 00 00 00 17 00 00 02 01 1F 0D
     0  1  2  3  4  5  6  7  8
    C5 5C 5A AA 01 97 96 0D
     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    B6 6B AA 5A 0A 42 4D 1B 00 00 05 00 03 00 00 18 0D
    it seems index=0 and index =2 or 3 are good enough...
  */

  switch (returned_array[0])
  {
    case 0xB6: // returned message
      // Serial.println("0xB6 received");
      if (returned_array[3] == 0xDA) {// maybe controller return message
        byte chksum = returned_array[4];
        for (int i = 5; i < (5 + int(returned_array[4])) ; i++) {
          chksum = chksum ^ returned_array[i];
        }//end of for loop
        // if (chksum != returned_array[15]) Serial.println("chksum error");
        //take controller data out, no header, command type chksum
        for (int j = 0; j < 10 ; j++) {
          controller_data[j] = returned_array[j + 5];
        }// end of j loop
        // Serial.println("controller data updated");
        // Serial.write(controller_data, sizeof(controller_data));
      }// end of if DA
      if (returned_array[3] == 0x5A) { // BMS return message
        // check chksum
        byte chksum = returned_array[4];
        for (int i = 5; i < (5 + int(returned_array[4])) ; i++) {
          chksum = chksum ^ returned_array[i];
        }//end of for loop
        // if (chksum != returned_array[15]) Serial.println("chksum error");
        //take data out.....
        for (int j = 0; j < 10 ; j++) {
          BMS_data[j] = returned_array[j + 5];
        }// end of j loop
        //  Serial.println("BMS data received");
        // Serial.write(BMS_data, sizeof(BMS_data));
      }// end of if 5A
      break;

    case 0xC5: // query message
      if (returned_array[2] == 0xDA) {// maybe controller query
        //   Serial.println("controller query");
      }// end of if DA
      if (returned_array[2] == 0x5A) { // BMS query message
        // Serial.println("BMS query");
        digitalWrite(DE_RE, HIGH);
        delay(3);
        Master.write(testing_BMS_return, sizeof(testing_BMS_return));
        delay(3);
        digitalWrite(DE_RE, LOW);
      }// end of if 5A
      break;
  }// end of switch 0
  memset(returned_array, 0, sizeof(returned_array));// clear the array
  index = 0; // clear index
}// end of after receive
