#ifndef TIME_H
#define TIME_H

#include <iostream>

typedef unsigned int uint;

class Time {
    private:
        uint minuteOfDay;
    public:
        Time(uint minuteOfDay = 0);
        Time(uint hour, uint minute);
        Time operator+(const uint term);
        void SetTime(uint hour, uint minute);
        uint GetHour();
        uint GetMinute();
        uint GetMinuteOfDay();

        friend std::istream& operator>>(std::istream& input, Time& time);
        friend std::ostream& operator<<(std::ostream& output, Time& time);
};
#endif