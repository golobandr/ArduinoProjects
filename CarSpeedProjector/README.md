# CarSpeedProjector
Project, aimed to create digital speedometer and project it to the front window of automobile.

-------------------------------------------------------------------------------  

## Notes:
1. It is considered to use some simple MCU. So, memory consumption has to be taken into account
2. For testing purpose TFT 2.0 IC ST7789V 240x320 is proposed
3. Screen rendering time has to be taken into account

-------------------------------------------------------------------------------  

## Compiling in Arduino IDE:
1. Download all files
2. Open "CarSpeedProjector.ino" in Arduino IDE
3. Install "Adafruit_GFX" library: Tools->Manage Libraries...->Adafruit GFX Library
4. Install "Adafruit_ST7789" library: Tools->Manage Libraries...->Adafruit ST7735 and ST7789 Library
5. Install "mcp_can" library: Tools->Manage Libraries...->mcp_can
6. Select Tools->Board->Arduino Uno
