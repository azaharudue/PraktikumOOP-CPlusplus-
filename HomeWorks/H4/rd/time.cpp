#include "time.h"

Time::Time(uint minuteOfDay) {
    this->minuteOfDay = minuteOfDay % 1440;
}

Time::Time(uint hour, uint minute) {
    SetTime(hour, minute);
}

void Time::SetTime(uint hour, uint minute) {
    if (hour > 23 || minute > 59) {
        minuteOfDay = 0;
        std::cerr << "Invalid arguments. Hours should be < 24 and minutes should be < 60" << std::endl;
        return;
    }
    minuteOfDay = hour * 60 + minute;
}

uint Time::GetHour() {
    return minuteOfDay / 60;
}

uint Time::GetMinute() {
    return minuteOfDay % 60;
}

uint Time::GetMinuteOfDay() {
    return minuteOfDay;
}

Time Time::operator+(const uint time) {
    return Time(minuteOfDay + time);
}

std::ostream& operator<<(std::ostream& output, Time& time) {
    uint hour = time.GetHour();
    uint minute = time.GetMinute();
    std::string timeString;
    if (hour < 10) {
        timeString += '0';
    }
    
    timeString += std::to_string(hour);
    timeString += ':';

    if (minute < 10) {
        timeString += '0';
    }
    timeString += std::to_string(minute);
    output << timeString;
    return output;
}

std::istream& operator>>(std::istream& input, Time& time) {
    bool parseError = false;
    std::string inputString;
    char delimiter = ':';

    input >> inputString;
    int delimiterPos = inputString.find(delimiter);
    if (delimiterPos == -1) {
        parseError = true;
        
    }

    std::string hour = inputString.substr(0, delimiterPos);
    std::string minute = inputString.substr(delimiterPos + 1, inputString.size());
    uint hour_size = hour.size();
    uint minute_size = minute.size();
    if (hour_size != 2 && minute_size != 2) {
        parseError = true;
    }

    uint parsedHour = 0;
    uint parsedMinute = 0;
    try {
        parsedHour = std::stoi(hour);
        parsedMinute = std::stoi(minute);
    } catch (std::invalid_argument) {
        parseError = true;
    }

    time.SetTime(parsedHour, parsedMinute);

    if (parseError) {
        throw std::invalid_argument("Invalid input. Input should match hh:mm pattern.");
    }

    return input;
}