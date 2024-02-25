#ifndef __DEBOUNCER_H__
#define __DEBOUNCER_H__
#include "NoDelay.h"

class Debouncer
{
private:
  noDelay *_delay;

public:
  Debouncer();
  bool filter(bool input);
  bool onFallingEdge(bool input);
  bool onRisingEdge(bool input);
};

Debouncer::Debouncer()
{
  _delay = new noDelay(50); // 50ms
}

bool Debouncer::filter(bool input)
{
  static bool output;
  static bool lastInput;
  static bool firstTime = true;

  if (firstTime)
  {
    output = input;
    firstTime = false;
  }
  else
  {
    if (input != lastInput)
    { // input changed
      _delay->start();
      // Serial.println(millis());
    }
    else
    { // input not changed
      if (_delay->update())
      {                 // input not changed during delay
        output = input; // change output
        // Serial.println(millis());
        _delay->stop();
      }
    }
  }

  lastInput = input;

  return output;
}

bool Debouncer::onFallingEdge(bool input)
{
  static bool firstTime = true;
  static bool lastInput;
  bool fired = false;

  input = this->filter(input);

  if (!firstTime)
  {
    if (lastInput == HIGH && input == LOW)
    {
      fired = true;
    }
  }
  else
  {
    firstTime = false;
  }

  lastInput = input;

  return fired;
}

bool Debouncer::onRisingEdge(bool input)
{
  static bool firstTime = true;
  static bool lastInput;
  bool fired = false;

  input = this->filter(input);

  if (!firstTime)
  {
    if (lastInput == LOW && input == HIGH)
    {
      fired = true;
    }
  }
  else
  {
    firstTime = false;
  }

  lastInput = input;

  return fired;
}

#endif /* __DEBOUNCER_H__ */