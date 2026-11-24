#include "Fan.h"

Fan::Fan() 
{
  pin = -1;
  active = false;
  startTime = 0;
  duration = 0;
  lastActivationTime = millis();
}

void Fan::begin(int pinP) 
{
  pin = pinP;
  pinMode(pin, OUTPUT);
  turnOff();
}

void Fan::turnOn(unsigned long activeDuration) 
{
  digitalWrite(pin, HIGH);
  active = true;
  startTime = millis();
  duration = activeDuration;
  lastActivationTime = millis();
}

void Fan::turnOff() 
{
  digitalWrite(pin, LOW); 
  active = false;
}

bool Fan::isActive() {
  return active;
}

bool Fan::hasExpired() const {
  if (!active) return false;
  return (millis() - startTime >= duration);
}

unsigned long Fan::getLastActivationTime() const 
{
  return startTime;
}