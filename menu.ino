#include <Arduino.h>
#include <avr/pgmspace.h>
#include "MemoryFree.h"

#include "app.hpp"

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  App_setup();  
}

void loop()
{
  App_loop();  
}