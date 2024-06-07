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

  I want to control these 3 with VR


*/
byte testing_BMS_return[17] = {0xB6, 0x6B, 0xAA, 0x5A, 0x0A, 0x42, 0x4D, 0x1B, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x18, 0x0D};
//                                                           ^^^^  ^^^^  ^^^^
byte returned_array[17];
int index = 0;
int msg_received = 0;
byte BMS_data[10];
byte controller_data[10];

// for BMS return data
byte voltage, percentage, temp;

const int analogInPin = A0;


void setup() {
  Serial.begin(9600);
  delay(10);
  //Serial.println(testing_BMS_return[0],HEX); //this is the way to show hex in char
  //Serial.println(testing_BMS_return[0]);

}

void loop() {
  measurement();
  while (Serial.available()) {
    if (check_coming_byte(Serial.read()) == true)
    {
      after_received();
    }
  }// end of while


}// end of loop

//decode function
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
