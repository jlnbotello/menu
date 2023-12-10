#include "model_week.hpp"

#define ALL_DAYS_MASK 0x7F

uint8_t WeekModel::getDayMask(Day day)
{
    if (day >= WeekModel::Day::Monday && day <= WeekModel::Day::AllDays)
    {
        return static_cast<uint8_t>(1 << static_cast<uint8_t>(day));
    }

    return 0;
}

void WeekModel::setDay(Day day)
{
    if (day == WeekModel::Day::AllDays)
    {
        weekMask |= 0xFF;
    }
    else
    {
        weekMask |= getDayMask(day);
    }
    
    if((weekMask & ALL_DAYS_MASK) == ALL_DAYS_MASK)
    {
        weekMask |= getDayMask(WeekModel::Day::AllDays);
    }
}

void WeekModel::clearDay(Day day)
{
    if (day == WeekModel::Day::AllDays)
    {
        weekMask &= 0x00;
    }
    else
    {
        weekMask &= ~getDayMask(day);
    }

    if((weekMask & ALL_DAYS_MASK) != ALL_DAYS_MASK)
    {
        weekMask &= ~getDayMask(WeekModel::Day::AllDays);
    }
}

bool WeekModel::isDaySelected(Day day)
{
    return (weekMask & getDayMask(day)) != 0;
}

void WeekModel::toggleDay(Day day)
{
    if (isDaySelected(day))
    {
        clearDay(day);
    }
    else
    {
        setDay(day);
    }
}