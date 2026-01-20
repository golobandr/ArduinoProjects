#include "Driver.h"

Driver::Driver(byte servoPin, byte echoPin, byte triggerPin, byte buzzerPin, byte pirPin, byte centerAngle, byte turnAngle)
{
  this->servoPin = servoPin;
  this->echoPin = echoPin;
  this->triggerPin = triggerPin;
  this->buzzerPin = buzzerPin;
  this->pirPin = pirPin;
  this->centerAngle = centerAngle;
  this->turnAngle = turnAngle;
}

void Driver::init()
{
  servo.attach(servoPin);
  servo.write(centerAngle);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);
  say(phraseHello, sizeof(phraseHello)/sizeof(phraseHello[0]), 1200);
}

byte Driver::checkDistance()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  int cm = (int)(pulseIn(echoPin, HIGH) / 58);
  if (cm > 255)
  {
    cm = 255;
  }
  return (byte)(cm);
}

byte Driver::checkDistance(int angle)
{
  turnHead(centerAngle + angle);
  byte cm = checkDistance();
  turnHead(centerAngle);
  return (byte)(cm);
}

bool Driver::move()
{
  bool retVal = true;
  byte dst = checkDistance();
  if (checkDistance() < MinDistance)
  {
    retVal =  false;
  }
  return retVal;
}

void Driver::turnHead(byte desiredAngle)
{
  servo.write(desiredAngle);
  delay(250);
}

void Driver::say(int *phrase, byte phraseSize, int tempo)
{
  int duration = 0;
  Serial.print(phraseSize);
  Serial.print(',');
  for (int thisNote = 0; thisNote < phraseSize; thisNote += 2)
  {
    duration = tempo / abs(phrase[thisNote + 1]);
    if (phrase[thisNote + 1] < 0)
    {
      duration *= 1.5;
    }
    tone(buzzerPin, phrase[thisNote], duration * 0.9);
    delay(duration);
    Serial.print(phrase[thisNote]);
    Serial.print(',');
  }
  noTone(buzzerPin);
  Serial.println();
}

void Driver::turnCar(Car &car)
{
  car.stop();
  bool movementF = digitalRead(pirPin);
  Serial.print(movementF);
  Serial.print(',');
  byte lft = checkDistance(turnAngle); //look left
  bool movementL = digitalRead(pirPin);
  Serial.print(movementL);
  Serial.print(',');
  byte rgh = checkDistance(- turnAngle); //look right
  bool movementR = digitalRead(pirPin);
  Serial.print(movementR);
  Serial.println(',');
  if ((movementF) || (movementL) || (movementR))
  {
    say(phraseGO, sizeof(phraseGO)/sizeof(phraseGO[0]), 1200);
  }
  if ((lft < MinDistance) && (rgh < MinDistance))
  {
    car.moveBackrward();
    say(phrasePop, sizeof(phrasePop)/sizeof(phrasePop[0]), 1200);
    car.stop();
    turnCar(car);
  }
  else if ((lft > rgh) || (movementR))
  {
    car.turnLeft();
  }
  else 
  {
    car.turnRight();
  }

}