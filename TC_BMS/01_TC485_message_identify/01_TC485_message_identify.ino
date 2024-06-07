/*
  listen and decode TC 485 traffic
  
  query to BMS
  C5 5C 5A AA 01 97 96 0D
  B6 6B AA 5A 0A 42 4D 1B 00 00 05 00 03 00 00 18 0D
  
  unkonw query
  C5 5C DA AA 02 00 00 02 0D
  B6 6B AA DA 0A 01 00 00 00 00 17 00 00 02 01 1F 0D
 

  try2 take received byte into returned array
  and after receive takes the following action

This is what Ｉdid in2022,works to identify these 4 types of meesage.


*/
byte testing_BMS_return[17] = {0xB6, 0x6B, 0xAA, 0x5A, 0x0A, 0x42, 0x4D, 0x1B, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x18, 0x0D};

byte returned_array[17];
int index = 0;
int msg_received = 0;
byte BMS_data[10];
byte controller_data[10];


void setup() {
  Serial.begin(9600);
  delay(10);
  //Serial.println(testing_BMS_return[0],HEX); //this is the way to show hex in char
  //Serial.println(testing_BMS_return[0]);

}

void loop() {

  while (Serial.available()) {
    if (check_coming_byte(Serial.read()) == true)
    {
      after_received();
    }

  }// end of while


}

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
