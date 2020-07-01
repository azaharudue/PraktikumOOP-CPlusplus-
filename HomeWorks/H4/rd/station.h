#ifndef STATION_H
#define STATION_H

#include "train.h"
#include "time.h"
#include <string>

class Station {
    private:
        const std::string station;
        const uint platforms = 15;
        Train *shedule[15][24*60] = { nullptr };
    public:
        Station(const std::string stationName);
        ~Station();
        void AddDeparture(Time time, uint platform, Train* train);
        void ShowDeparture(Time time, uint minutes); 
};

#endif