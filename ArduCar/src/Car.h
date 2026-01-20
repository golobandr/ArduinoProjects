#ifndef CAR_H
#define CAR_H

#include <Arduino.h>
#include "Motor.h"

class Car
{
  private:
    Motor leftMotor;
    Motor rightMotor;
    byte turnTime;
    byte moveBackwardTime;
  
  public:
    Car()
    {
      // do not use
    }

    Car(Motor &leftMotor, Motor &rightMotor, byte turnTime, byte moveBackwardTime);

    void init();

    void moveForward();

    void moveBackrward();

    void turnLeft();

    void turnRight();

    void stop();
};

#endif