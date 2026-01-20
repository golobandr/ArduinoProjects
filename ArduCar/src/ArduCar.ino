#include <Servo.h>
#include "Motor.h"
#include "Car.h"
#include "Driver.h"

// Car
#define LeftMotorForwardPin 2
#define LeftMotorBackwardPin 6
#define RightMotorForwardPin 5
#define RightMotorBackwardPin 7
#define TurnTime 200
#define MoveBackwardTime 200

//Driver
#define BuzzerPin 3
#define PirPin 4
#define ServoPin 8
#define EchoPin A1
#define TrigPin A0
#define ServoCenterAngle 90
#define ServoLookAngle 60

Servo servo;
Motor leftMotor(LeftMotorForwardPin, LeftMotorBackwardPin);
Motor rightMotor(RightMotorForwardPin, RightMotorBackwardPin);
Car car(leftMotor, rightMotor, TurnTime, MoveBackwardTime);
Driver driver(ServoPin, EchoPin, TrigPin, BuzzerPin, PirPin, ServoCenterAngle, ServoLookAngle);

void setup()
{
  Serial.begin(9600);
  car.init();
  driver.init();
}

void loop() 
{
  
  if (driver.move())
  {
    car.moveForward();
  }
  else {
    driver.turnCar(car);
  }
 
}