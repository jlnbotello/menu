#ifndef __WEEK_MODEL_H__
#define __WEEK_MODEL_H__

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
        Sunday,
        AllDays
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

#endif /* __WEEK_MODEL_H__ */