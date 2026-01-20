#include "Car.h"

Car::Car(Motor &leftMotor, Motor &rightMotor, byte turnTime, byte moveBackwardTime)
{
  this->leftMotor = leftMotor;
  this->rightMotor = rightMotor;
  this->turnTime = turnTime;
  this->moveBackwardTime = moveBackwardTime;
}

void Car::init()
{
  leftMotor.init();
  rightMotor.init();
}

void Car::moveForward()
{
  leftMotor.forward();
  rightMotor.forward();
}

void Car::moveBackrward()
{
  leftMotor.backward();
  rightMotor.backward();
 }

void Car::turnLeft()
{
  rightMotor.forward();
  leftMotor.backward();
  delay(turnTime);
  stop();
}

void Car::turnRight()
{
  leftMotor.forward();
  rightMotor.backward();
  delay(turnTime);
  stop();
}

void Car::stop()
{
  leftMotor.stop();
  rightMotor.stop();
}
