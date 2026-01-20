#include "Motor.h"

Motor::Motor(byte pinForward, byte pinBackward)
{
  this->pinForward = pinForward;
  this->pinBackward = pinBackward;
}

void Motor::init()
{
  pinMode(pinForward, OUTPUT);
  pinMode(pinBackward, OUTPUT);
}

void Motor::forward()
{
  digitalWrite(pinBackward, LOW);
  digitalWrite(pinForward, HIGH);
}

void Motor::backward()
{
  digitalWrite(pinForward, LOW);
  digitalWrite(pinBackward, HIGH);
}

void Motor::stop()
{
  digitalWrite(pinBackward, LOW);
  digitalWrite(pinForward, LOW);
}
