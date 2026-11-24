#ifndef FAN_H
#define FAN_H

#include <Arduino.h>

class Fan {
  private:
    int pin;
    bool active;
    unsigned long startTime;
    unsigned long duration;
    unsigned long lastActivationTime;

  public:
    Fan();
    void begin(int pinP);
    void turnOn(unsigned long activeDuration);
    void turnOff();
    bool isActive();
    bool hasExpired() const;
    unsigned long getLastActivationTime() const;
};

#endif