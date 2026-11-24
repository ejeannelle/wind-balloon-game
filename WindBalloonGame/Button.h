#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button 
{
  private:
    int pin;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
    bool lastButtonState;
    bool buttonState;

  public:
    Button(int pinP);
    void begin();
    bool wasPressed();
};

#endif