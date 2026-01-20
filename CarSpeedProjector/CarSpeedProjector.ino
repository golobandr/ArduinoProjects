#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <mcp_can.h>
#include "src/Speedometer.h"


#define CAN_INT  2
#define TFT_DC   9
#define TFT_CS   7
#define TFT_RST  8
#define CAN_DC   10
#define INTERVAL_V 100
#define INTERVAL_T 30
#define INTERVAL_F 60
#define INTERVAL_TF 1000

Adafruit_ST7789 lcd = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
MCP_CAN mcp2515(CAN_DC);
Speedometer speedometer = Speedometer();
unsigned long previousMillis_V = millis();
unsigned long previousMillis_T = millis() + INTERVAL_T;
byte data[8] = {0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
bool mcp2515Init;
bool mcp2515Send;

void setup()
{
  Serial.begin(9600);
  speedometer.init(lcd);
  if(mcp2515.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
  {
    mcp2515Init = true;
    Serial.println("MCP2515 Initialized Successfully!");
    mcp2515.setMode(MCP_NORMAL);
    pinMode(CAN_INT, INPUT);
  }
  else
  {
    mcp2515Init = false;
    Serial.println("Error Initializing MCP2515...");
  }
  mcp2515Send = false;
}

void loop(void) 
{
  
  if (mcp2515Init == true)
  {
    if (mcp2515Send == false)
    {
      if (millis() - previousMillis_V >= INTERVAL_V)
      {
        previousMillis_V = millis();
        mcp2515Send = true;
        data[2] = 0x0D;
      }
      else if (millis() - previousMillis_T >= INTERVAL_TF)
      {
        previousMillis_T = millis();
        mcp2515Send = true;
        data[2] = 0x05;
      }

      if (mcp2515Send == true)
      {
        (void)mcp2515.sendMsgBuf(0x7DF, 0, 8, data);
        mcp2515Send = false;
      }
    }

    if (!digitalRead(CAN_INT))
    {
      mcp2515.readMsgBuf(&rxId, &len, rxBuf);

      if ((rxId == 0x7E8) && (rxBuf[1]!= 0x7F))
      {

        if (len> 0)
        {
          Serial.print(rxId);Serial.print(" ");Serial.print(len);Serial.print(": ");
        }
        for (byte i = 0; i <len; i++)
        {
          Serial.print(rxBuf[i]);Serial.print(" ");
        }
        Serial.println();

        switch (rxBuf[2])
        {
          case 0x0D:
          {
            speedometer.setSpeed(lcd, rxBuf[3]);
          }
          break;

          case 0x05:
          {
            speedometer.setTemp(lcd, rxBuf[3] - 40, true);
          }
          break;

          default:
          {
            // do nothing
          }
        }
      }
    }
  }
}


