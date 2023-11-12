#include "model_week.hpp"

uint8_t WeekModel::getDayMask(Day day) {
    return static_cast<uint8_t>(1 << static_cast<uint8_t>(day));
}

void WeekModel::setDay(Day day) {
    weekMask |= getDayMask(day);
}

void WeekModel::clearDay(Day day) {
    weekMask &= ~getDayMask(day);
}

bool WeekModel::isDaySelected(Day day) {
    return (weekMask & getDayMask(day)) != 0;
}

void WeekModel::toggleDay(Day day) {
    if (isDaySelected(day)) {
        clearDay(day);
    } else {
        setDay(day);
    }
}