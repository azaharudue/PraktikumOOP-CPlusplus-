#include "time.h"
#include "train.h"
#include "station.h"
#include <iostream>

void FillPlatformsWithTrains(Station&);
int SelectMenu();
void ScheduleTrain(Station&);
void ShowSchedule(Station&);

int main() {
    Station duisburg("Main station");
    FillPlatformsWithTrains(duisburg);
    while (true) {
        int task = SelectMenu();
        switch (task) {
            case 0:
                // End the program
                return 0;
                break;
            case 1:
                // Schedule train
                ScheduleTrain(duisburg);
                break;
            
            case 2:
                // Show schedule
                ShowSchedule(duisburg);
                break;
        }
    }
    return 0;
}

int SelectMenu() {
    while (true) {
        std::cout << "0 end" << '\n' 
                << "1 schedule train" << '\n'
                << "2 show schedule" << '\n' << std::endl;
        int task = -1;
        std::string line;
        std::cout << ">> ";

        if (!std::getline(std::cin, line)) {
            std::cerr << "Input failed. Abort." << std::endl;
            exit(1);
        }
        try {
            task = std::stoi(line);
            return task;
        } catch (std::invalid_argument) {
            std::cerr << "Invalid command. Please try again" << std::endl;
        }
    }
}

void ScheduleTrain(Station& station) {
    bool departureEntered = false;
    bool platformEntered = false;
    Time time(0);
    uint platform = 0;
    Train *train;

    std::cout << std::endl;
    while (true) {

        if (!departureEntered) {
            std::cout << "Enter time of departure: ";
            try { 
                std::cin >> time;
            } catch (std::invalid_argument) {
                std::cerr << "Invalid input. Please try again" << std::endl;
                continue;
            }
            departureEntered = true;
            std::cin.ignore();
        }

        if (!platformEntered) {
            std::cout << "Enter platform number: ";
            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cerr << "Input failed. Abort." << std::endl;
                exit(1);
            }

            try {
                platform = std::stoi(line);
            } catch (std::invalid_argument) {
                std::cerr << "Should be a number value. Please try again" << std::endl;
                continue;
            }
            platformEntered = true;
        }

        std::string trainNum;
        std::string trainTo;
        std::string trainOver;

        std::cout << "Enter train number: ";
        if (!std::getline(std::cin, trainNum)) {
            std::cerr << "Input failed. Abort." << std::endl;
            exit(1);
        }

        std::cout << "Enter train destination: ";
        if (!std::getline(std::cin, trainTo)) {
            std::cerr << "Input failed. Abort." << std::endl;
            exit(1);
        }

        std::cout << "Enter train over: ";
        if (!std::getline(std::cin, trainOver)) {
            std::cerr << "Input failed. Abort." << std::endl;
            exit(1);
        }

        train = new Train(trainNum, trainTo, trainOver);
        station.AddDeparture(time, platform, train);
        break;
    }
    std::cout << std::endl;
}

void ShowSchedule(Station& station) {
    bool startingTimeEntered = false;
    Time time(0);
    uint minutes = 0;

    std::cout << std::endl;
    while (true) {
        if (!startingTimeEntered) {
            std::cout << "Enter departures starting time: ";
            try {
                std::cin >> time;
            } catch (std::invalid_argument) {
                std::cerr << "Invalid input. Please try again" << std::endl;
                continue;
            }
            startingTimeEntered = true;
            std::cin.ignore();
        }

        std::string line;
        std::cout << "Enter for how many next minutes: ";
        if (!std::getline(std::cin, line)) {
            std::cerr << "Input failed. Abort." << std::endl;
            exit(1);
        }
        try {
            minutes = std::stoi(line);
        } catch (std::invalid_argument) {
            std::cerr << "Should be a number value. Please try again" << std::endl;
            continue;
        }

        station.ShowDeparture(time, minutes);
        break;
    }
    std::cout << std::endl;
}

void FillPlatformsWithTrains(Station& station) {
    uint platform = 0;
    uint minute = 0;


    minute = 7;
    platform = 9;
    Time scheduleTime(minute);
    while (scheduleTime.GetHour() < 23) {
        Train *train = new Train("S1", "Dortmund Hbf", "Muelheim(Ruhr)Styrum - Muelheim(Ruhr) - Essen");
        station.AddDeparture(scheduleTime, platform, train);
        scheduleTime = scheduleTime + 30;
    }

    platform = 5;
    minute = 15;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() < 23) {
        Train *train = new Train("S1", "Solingen Hbf", "Duisburg-Schlenk - Duesseldorf Flughafen.");
        station.AddDeparture(scheduleTime, platform, train);
        scheduleTime = scheduleTime + 20;
    }

    platform = 2;
    minute = 35;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() < 23) {
        Train *train = new Train("S2", "Dortmund Hbf", "Oberhausen - Gelsenkirchen - WanneEickel.");
        station.AddDeparture(scheduleTime, platform, train);
        scheduleTime = scheduleTime + 60;
    }

    platform = 4;
    minute = 22;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() < 23) {
        Train *train = new Train("RE1", "Aachen Hbf", "Duesseldorf Flughafen - Duesseldorf - Koeln.");
        station.AddDeparture(scheduleTime, platform, train);
        scheduleTime = scheduleTime + 60;
    }

    platform = 10;
    minute = 24;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() < 23) {
        Train *train = new Train("RE2", "Muenster Hbf", "Muelheim(Ruhr) - Essen - Gelsenkirchen.");
        station.AddDeparture(scheduleTime, platform, train);
        scheduleTime = scheduleTime + 60;
    }
}