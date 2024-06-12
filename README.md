The socoTC system use rs485, master/slave protocol to communicate each other.
This is made with a 5V 328P, to response to master as a BMS
the detail of finding the protocol is here:
https://ldsrc.blogspot.com/2023/12/soco-tc-rs485-decode.html

here is the test result:
I use a usb to 485 to send query command to arduino, and the responce is now as soco TC battery pack.
![螢幕截圖 2024-06-07 14 27 22](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/639916b5-f4c2-47f3-9ffd-517efc392403)

Tested result: It does tell the system what I want it to be, I use a VR to change values and see if the system figure changes.

![PXL_20240611_083912003](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/f9dd01e6-ac8b-44b7-a225-73cca5294fa9)
![PXL_20240611_083917139](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/601f58ba-7e9a-4520-967c-6903a9424c81)
![PXL_20240611_083903441](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/dc775cb1-5328-49ec-8d7d-d4198ef10b43)
![PXL_20240611_083906114](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/71015fe7-20b4-405f-b538-319abc0e706c)

I found this git, who has more info than I have: https://github.com/stprograms/SuperSoco485Monitor/tree/main
I will do a fork from this one, to do more things I need.
## Decoded telegrams
The following telegrams and packages of read responses are already decoded.

### BMS Status (Read Response 0xAA5A)

| Byte (len=10) |    0    |   1   |   2   |   3    |   4    |   5    |   6   |   7   |    8     |    9     |
| ------------- | :-----: | :---: | :---: | :----: | :----: | :----: | :---: | :---: | :------: | :------: |
|               | Voltage |  SoC  | Temp  | Charge | CycleH | CycleL |   ?   |   ?   | VBreaker | Charging |

#### Description of the variables
| Variable   | Description                                  | Unit                                                                                              | Data Type     |
| ---------- | -------------------------------------------- | ------------------------------------------------------------------------------------------------- | ------------- |
| Voltage    | current Voltage of the Battery in V          | Volts[V]                                                                                          | unsigned byte |
| SoC        | State of Charge in %                         | Percent [%]                                                                                       | unsigned byte |
| Temp       | current temperatur of the BMS                | Degree C [°C]                                                                                     | signed byte   |
| Charge     | current charging or discharging current in A | Ampere [A]                                                                                        | signed byte   |
| Cycle[H/L] | Number of loading cycles                     |                                                                                                   | unsigned word |
| VBreaker   |                                              | 0 = OK<br>1 = bms stopped charge<br>2 = too high charge current<br>4 = too high discharge current | unsigned byte |
| Charging   | Battery is currently charging                | 1 = charge<br>4 = discharge                                                                       | unsigned byte |

### ECU Status (Read Response 0xAADA)
| Byte (len=10) |   0   |    1     |    2     |   3    |   4    |    5     |   6   |   7   |    8    |   9   |
| ------------- | :---: | :------: | :------: | :----: | :----: | :------: | :---: | :---: | :-----: | :---: |
|               | Mode  | CurrentH | CurrentL | SpeedH | SpeedL | ECU Temp |   ?   |   ?   | Parking |   ?   |


#### Description of the variables
| Variable      | Description         | Unit                | Data Type     |
| ------------- | ------------------- | ------------------- | ------------- |
| Mode          | Speed Mode          | 1 - 3               | unsigned byte |
| Current [H/L] | Current consumption | [mA] ?              | unsigned word |
| Speed [H/L]   | Current speed       | [km/h] ?            | unsigned word |
| ECU Temp      | Temperature of ECU  | Degree Celcius [°C] | signed byte   |
| Parking       | Parking mode        | 2 = on<br>1 = off   | unsigned byte |
