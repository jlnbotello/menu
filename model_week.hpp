#ifndef __MODEL_WEEK_HPP__
#define __MODEL_WEEK_HPP__

#include "stdint.h"

class WeekModel {
public:
    enum class Day {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    WeekModel() : weekMask(0) {}

    void setDay(Day day);
    void clearDay(Day day);
    bool isDaySelected(Day day);
    void toggleDay(Day day);

private:
    uint8_t weekMask;

    uint8_t getDayMask(Day day);
};

#endif /* MODEL_WEEK_HPP */