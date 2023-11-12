#include <Arduino.h>

class TimeModel {
public:
    void start(unsigned long timeout, void (*callback)()) {
        timeoutMillis = timeout;
        startTime = millis();
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

    void update() {
        if (active && millis() - startTime >= timeoutMillis) {
            stop();
            if (callbackFunction) {
                callbackFunction();
            }
        }
    }

private:
    unsigned long startTime = 0;
    unsigned long timeoutMillis = 0;
    bool active = false;
    void (*callbackFunction)() = nullptr;
};
