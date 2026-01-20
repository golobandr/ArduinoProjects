#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
  private:
    byte pinForward;
    byte pinBackward;
  
  public:
    Motor()
    {
      // do not use
    }

    Motor(byte pinForward, byte pinBackward);

    void init();

    void forward();

    void backward();

    void stop();
};

#endif
