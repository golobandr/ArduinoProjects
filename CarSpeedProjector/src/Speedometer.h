#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "SegmentLine.h"
#include <string.h>

#define RGBto565(r,g,b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

#define DARK_BLUE   RGBto565(0, 0, 240)
#define DARK_RED    RGBto565(240, 0, 0)
#define LIGHT_GREY  RGBto565(160, 160, 160)
#define BLACK       0x0000
#define WHITE       0xFFFF


class Speedometer
{
  private:
    String speedStr[3];
    byte speed;
    int temp;

    void drawSpeedImage(Adafruit_ST7789 &lcd);
    void drawTempImage(Adafruit_ST7789 &lcd, bool visible);
    void drawTempScale(Adafruit_ST7789 &lcd, bool visible);
    void drawTemp(Adafruit_ST7789 &lcd, int temp, bool visible);
    String convertDigit(byte speed);
    String segmentDiff(String strNew, String strOld);

  public:

    Speedometer();

    void init(Adafruit_ST7789 &lcd);
    void setSpeed(Adafruit_ST7789 &lcd, byte speed);
    void setTemp(Adafruit_ST7789 &lcd, int temp, bool visible);

};

#endif