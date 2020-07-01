#include "station.h"
#include "time.h"
#include "train.h"
#include <iostream>
#include <iomanip>

Station::Station(const std::string stationName) : station(stationName)  {

}

Station::~Station() {
    for (int i = 0; i < platforms; i++) {
        for (int j = 0; j < 24 * 60; j++) {
            if (shedule[i][j] == nullptr) {
                continue;
            }
            Time time(j);
            std::cout << time << " platform " << i << " ";
            delete shedule[i][j];
        }
    }
}

void Station::AddDeparture(Time time, uint platform, Train* train) {
    if (platform > platforms) {
        std::cerr << "Invalid arguments. Platform value must be < 15" << std::endl;
        return;
    }

    shedule[platform][time.GetMinuteOfDay()] = train;
}

void Station::ShowDeparture(Time time, uint minutes) {
    uint timeFrom = time.GetMinuteOfDay();
    uint timeTo = time.GetMinuteOfDay() + minutes;
    Time endTime(time.GetMinuteOfDay());
    endTime = time + minutes;

    using std::setw;

    std::cout << station << std::endl;
    std::cout << "Departures " << time << '-' << endTime << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << std::left << setw(6) << "Time " << setw(20) << "Train " 
              << setw(60) << "Over " << setw(20) << "To " 
              << setw(20) << "Platform " << std::endl;
     
    for (int i = 0; i < platforms; i++) {
        for (int j = timeFrom; j < timeTo; j++) {
            if (shedule[i][j] == nullptr) {
                continue;
            }
            Time time(j);
            Train *train = shedule[i][j];

            std::cout << std::left << setw(6) << time << setw(20) << train->GetTrainNumber() 
                      << setw(60) << train->GetOver() << setw(20) << train->GetDestination() 
                      << setw(20) << i << std::endl;
        }
    }
    std::cout << "======================" << std::endl;
}