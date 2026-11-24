#include "Button.h"
#include "config.h"

Button::Button(int pinP) 
{
  pin = pinP;
  debounceDelay = DEBOUNCE_DELAY;
  lastButtonState = HIGH;
  buttonState = HIGH;
  lastDebounceTime = 0;
}

void Button::begin() 
{
  pinMode(pin, INPUT_PULLUP);
}

bool Button::wasPressed() 
{
  bool pressed = false;
  int currentState = digitalRead(pin);

  // Si l'état a changé (bruit ou appui réel)
  if (currentState != lastButtonState) 
  {
    lastDebounceTime = millis();
  }

  // Si le délai anti-rebond est dépassé
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (currentState != buttonState) 
    {
      buttonState = currentState;
      // Avec INPUT_PULLUP, un appui amène la broche à LOW
      if (buttonState == LOW) 
      {
        pressed = true;
      }
    }
  }

  lastButtonState = currentState;
  return pressed;
}