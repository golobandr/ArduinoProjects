#include "Speedometer.h"

Speedometer::Speedometer()
{
  speedStr[0] = "";
  speedStr[1] = "";
  speedStr[2] = "012456";
  speed = 0;
  temp = 0;
}

void Speedometer::init(Adafruit_ST7789 &lcd)
{
  lcd.init(240, 320);
  lcd.setRotation(1);
  lcd.fillScreen(BLACK);
  lcd.setFont(&SegmentLine);
  lcd.setTextWrap(false);
  drawTempImage(lcd, true);
  drawSpeedImage(lcd);
}

void Speedometer::drawTempImage(Adafruit_ST7789 &lcd, bool visible)
{
  if (visible == true)
  {
    lcd.setTextColor(WHITE);
  }
  else
  {
    lcd.setTextColor(BLACK);
  }
  lcd.setTextSize(1);
  lcd.setCursor(235, 190);
  lcd.print("J");
  drawTempScale(lcd, visible);
  lcd.setTextSize(2);
  lcd.setCursor(280, 200);
  lcd.print("@C");
  lcd.setCursor(280, 180);
  lcd.print("LMK");
  lcd.setCursor(280, 100);
  lcd.print("OK");
  lcd.setCursor(280, 20);
  lcd.print("NK");
  lcd.setTextSize(1);
  setTemp(lcd, this->temp, visible);
}

void Speedometer::drawTempScale(Adafruit_ST7789 &lcd, bool visible)
{
  lcd.setTextSize(1);
  if (visible == true)
  {
    lcd.setTextColor(LIGHT_GREY);
  }
  else
  {
    lcd.setTextColor(BLACK);
  }
  for (byte i = 0; i < 8; i++)
  {
    lcd.setCursor(250, 30 + i * 20);
    lcd.print("?");
  }
  if (visible == true)
  {
    lcd.setTextColor(ST77XX_WHITE);
  }
  else
  {
    lcd.setTextColor(BLACK);
  }
  lcd.setCursor(250, 51);
  for (byte i = 0; i < 9; i++)
  {
    lcd.setCursor(250, 20 + i * 20);
    lcd.print("=");
  }
  for (byte i = 0; i < 3; i++)
  {
    lcd.setCursor(250, 20 + i * 80);
    lcd.print("<");
  }
}

void Speedometer::setSpeed(Adafruit_ST7789 &lcd, byte speed)
{
  if (speed != this->speed)
  {
    this->speed = speed;
    String speedTmpStr[3] = {"", "", ""};
    String speedWrtStr[3] = {"", "", ""};
    String speedClrStr[3] = {"", "", ""};
    String newStr;
    String oldStr;
    for (byte i = 0; i < 3; i++)
    {
      speedTmpStr[2 - i] = convertDigit((byte) (speed % 10));
      speed = (byte) ((speed - (speed % 10)) / 10);
      if (speed == 0)
      {
        break;
      }
    }
    for (byte i = 0; i < 3; i++)
    {
      speedClrStr[2 - i] = segmentDiff(speedStr[2 - i], speedTmpStr[2 - i]);
      speedWrtStr[2 - i] = segmentDiff(speedTmpStr[2 - i], speedStr[2 - i]);
    }
    lcd.setTextColor(ST77XX_BLACK);
    lcd.setTextSize(2);
    lcd.setCursor(0, 80);
    lcd.print(speedClrStr[0] + "7" + speedClrStr[1] + "7" + speedClrStr[2]);
    lcd.setTextColor(ST77XX_WHITE);
    lcd.setCursor(0, 80);
    lcd.print(speedWrtStr[0] + "7" + speedWrtStr[1] + "7" + speedWrtStr[2]);
    speedStr[0] = speedTmpStr[0];
    speedStr[1] = speedTmpStr[1];
    speedStr[2] = speedTmpStr[2];
  }
}

String Speedometer::segmentDiff(String strNew, String strOld)
{
  String retStr = "";
  for (byte j = 0; j < strNew.length(); j++)
  {
    if (strOld.indexOf(strNew[j]) == -1)
    {
      retStr = retStr + strNew[j];
    }
  }
  return retStr;
}

void Speedometer::setTemp(Adafruit_ST7789 &lcd, int temp, bool visible)
{
  if (temp < 40)
  {
    temp = 40;
  }
  else if (temp > 120)
  {
    temp = 120;
  }
  if (temp != this->temp)
  {
    drawTemp(lcd, this->temp, !visible);
    drawTempScale(lcd, visible);
    drawTemp(lcd, temp, visible);
    this->temp = temp;
  }
}

void Speedometer::drawTemp(Adafruit_ST7789 &lcd, int temp, bool visible)
{
  lcd.setTextSize(1);
  if (visible == true)
  {
    if (temp < 110)
    {
      lcd.setTextColor(DARK_BLUE);
    }
    else
    {
      lcd.setTextColor(DARK_RED);
    }
  }
  else
  {
    lcd.setTextColor(ST77XX_BLACK);
  }
  lcd.setCursor(240, 20 + 2 * (temp - 40));
  lcd.print(">");
}

String Speedometer::convertDigit(byte speed)
{
  String retVal;
  switch (speed)
  {
    case 0:
    {
      retVal = "012456";
    }
    break;
    
    case 1:
    {
      retVal = "25";
    }
    break;
    
    case 2:
    {
      retVal = "01356";
    }
    break;
    
    case 3:
    {
      retVal = "02356";
    }
    break;
    
    case 4:
    {
      retVal = "2345";
    }
    break;
    
    case 5:
    {
      retVal = "02346";
    }
    break;
    
    case 6:
    {
      retVal = "012346";
    }
    break;
    
    case 7:
    {
      retVal = "256";
    }
    break;
    
    case 8:
    {
      retVal = "0123456";
    }
    break;
    
    default:
    {
      retVal = "023456";
    }
    break;
  }
  return retVal;
}

void Speedometer::drawSpeedImage(Adafruit_ST7789 &lcd)
{
  lcd.setTextColor(ST77XX_WHITE);
  lcd.setTextSize(2);
  lcd.setCursor(0, 80);
  lcd.print(speedStr[0] + "7" + speedStr[1] + "7" + speedStr[2]);
  lcd.setCursor(100, 20);
  lcd.print("9:8;");
}

