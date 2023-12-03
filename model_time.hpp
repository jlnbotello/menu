#ifndef __MODEL_TIME_HPP__
#define __MODEL_TIME_HPP__

#include <Arduino.h>

#define HH_MM_SS_TO_MS(hh, mm, ss) ((3600*hh + 60*mm + ss) * (unsigned long) 1000)

class TimeModel 
{
public:
    TimeModel(int m, int s): minutes(m), seconds(s) {};

    void start(unsigned long timeout, void (*callback)()) {
        timeoutMillis = timeout;
        Serial.print("timeout: ");
        Serial.println(timeout);
        startTime = millis();
        Serial.print("starttime: ");
        Serial.println(startTime);
        callbackFunction = callback;
        active = true;
    }

    void stop() {
        active = false;
    }

    void reset() {
        active = false;
        startTime = 0;
        timeoutMillis = 0;
        callbackFunction = nullptr;
    }

    bool is_enabled()
    {
        return active;
    }

    void update() {
        if (active) 
        {
            if(millis() >= (startTime + timeoutMillis))
            {
                stop();
                if (callbackFunction) {
                    callbackFunction();
                }
            }
        }
    }

    unsigned long getRemaining()
    {
        remaning = (startTime + timeoutMillis) - millis();
        return remaning > 0 ? remaning : 0 ;
    }


private:
    unsigned long startTime = 0;
    unsigned long timeoutMillis = 0;
    unsigned long remaning = 0;
    bool active = false;
    void (*callbackFunction)() = nullptr;
    int minutes = 0;
    int seconds = 0;
};

#endif /* __MODEL_TIME_HPP__ */