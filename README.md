The socoTC system use rs485, master/slave protocol to communicate each other.
This is made with a 5V 328P, to response to master as a BMS
the detail of finding the protocol is here:
https://ldsrc.blogspot.com/2023/12/soco-tc-rs485-decode.html

here is the test result:
I use a usb to 485 to send query command to arduino, and the responce is now as soco TC battery pack.
![螢幕截圖 2024-06-07 14 27 22](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/639916b5-f4c2-47f3-9ffd-517efc392403)

Tested result: It does tell the system what I want it to be:

![PXL_20240611_083912003](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/f9dd01e6-ac8b-44b7-a225-73cca5294fa9)
![PXL_20240611_083917139](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/601f58ba-7e9a-4520-967c-6903a9424c81)
![PXL_20240611_083903441](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/dc775cb1-5328-49ec-8d7d-d4198ef10b43)
![PXL_20240611_083906114](https://github.com/Ldsrc2008/SocoTC-BMS-cheater/assets/2297151/71015fe7-20b4-405f-b538-319abc0e706c)
