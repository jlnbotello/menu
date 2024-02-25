#include <Arduino.h>
#include "src/app/app.h"

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