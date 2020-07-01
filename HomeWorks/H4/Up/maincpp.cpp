#include <iostream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

typedef unsigned int uint;

/* TIME CLASS */
class Time {
    private:
        uint minuteOfDay;
    public:
        Time(uint minuteOfDay = 0) {
            this->minuteOfDay = minuteOfDay % 1440;
        }

        Time(uint hour, uint minute) {
            SetTime(hour, minute);
        }

        Time operator+(const uint time) {
            return Time(minuteOfDay + time);
        }

        void SetTime(uint hour, uint minute) {
            if (hour > 23 || minute > 59) {
                minuteOfDay = 0;
                std::cerr << "Invalid arguments. Hours should be < 24 and minutes should be < 60" << std::endl;
                return;
            }
            minuteOfDay = hour * 60 + minute;
        }

        uint GetHour() {
            return minuteOfDay / 60;
        }

        uint GetMinute() {
            return minuteOfDay % 60;
        }

        uint GetMinuteOfDay() {
            return minuteOfDay;
        }

        friend std::istream& operator>>(std::istream& input, Time& time);
        friend std::ostream& operator<<(std::ostream& output, Time& time);
};

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

/* TRAIN CLASS */
class Train {
    private:
        const std::string no;
        const std::string to;
        const std::string over;
    public:
        Train(const std::string trainNum, const std::string destination, const std::string over) :
                                                    no(trainNum), to(destination), over(over) {};
        ~Train() {
            std::cout << "Train " << no << " to " << to << " deleted" << std::endl;
        }

        const std::string GetTrainNumber() {
            return no;
        }

        const std::string GetDestination() {
            return to;
        }

        const std::string GetOver() {
            return over;
        }

};

/* STATION CLASS */
class Station {
    private:
        const std::string station;
        const static uint platforms = 15;
        Train *schedule[platforms][24 * 60];
    public:
        Station(const std::string stationName) : station(stationName) {
            for (int i = 0; i < platforms; i++) {
                for (int j = 0; j < 24 * 60; j++) {
                    schedule[i][j] = nullptr;
                }
            }
        }

        ~Station() {
            for (int i = 0; i < platforms; i++) {
                for (int j = 0; j < 24 * 60; j++) {
                    if (schedule[i][j] == nullptr) {
                        continue;
                    }
                    Time time(j);
                    std::cout << time << " platform " << i << " ";
                    delete schedule[i][j];
                }
            }
        }

        void AddDeparture(Time time, uint platform, Train* train) {
            if (platform > platforms) {
                std::cerr << "Invalid arguments. Platform value must be < 15" << std::endl;
                return;
            }

            schedule[platform][time.GetMinuteOfDay()] = train;
        }

        void ShowDeparture(Time time, uint minutes) {
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

            bool nextDay = false;
            if (endTime.GetMinuteOfDay() < timeFrom) {
                nextDay = true;
            }

            if (nextDay) {
                // Get very last minute before next day
                Time midnightTime(24 * 60 - 1);
                for (int j = timeFrom; j <= midnightTime.GetMinuteOfDay(); j++) {
                    for (int i = 0; i < platforms; i++) {
                        if (schedule[i][j] == nullptr) {
                            continue;
                        }
                        Time time(j);
                        Train *train = schedule[i][j];

                        std::cout << std::left << setw(6) << time << setw(20) << train->GetTrainNumber()
                                << setw(60) << train->GetOver() << setw(20) << train->GetDestination()
                                << setw(20) << i << std::endl;
                    }
                }

                // Start with midnight
                midnightTime = midnightTime + 1;
                // Print trains schedule for the next day
                for (int j = midnightTime.GetMinuteOfDay(); j < endTime.GetMinuteOfDay(); j++) {
                    for (int i = 0; i < platforms; i++) {
                        if (schedule[i][j] == nullptr) {
                            continue;
                        }
                        Time time(j);
                        Train *train = schedule[i][j];

                        std::cout << std::left << setw(6) << time << setw(20) << train->GetTrainNumber()
                                << setw(60) << train->GetOver() << setw(20) << train->GetDestination()
                                << setw(20) << i << std::endl;
                    }
                }
            } else {
                for (int j = timeFrom; j < endTime.GetMinuteOfDay(); j++) {
                    for (int i = 0; i < platforms; i++) {
                        if (schedule[i][j] == nullptr) {
                            continue;
                        }
                        Time time(j);
                        Train *train = schedule[i][j];

                        std::cout << std::left << setw(6) << time << setw(20) << train->GetTrainNumber()
                                << setw(60) << train->GetOver() << setw(20) << train->GetDestination()
                                << setw(20) << i << std::endl;
                    }
                }
            }
            std::cout << "======================" << std::endl;
        }
};

/* MENU UTILS FUNCTIONS */
void FillPlatformsWithTrains(Station&);
int SelectMenu();
void ScheduleTrain(Station&);
void ShowSchedule(Station&);

/* MAIN FUNCTION */
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
    while (scheduleTime.GetHour() <= 23) {
        Train *train = new Train("S1", "Dortmund Hbf", "Muelheim(Ruhr)Styrum - Muelheim(Ruhr) - Essen");
        Time endTime(scheduleTime.GetMinuteOfDay());
        scheduleTime = scheduleTime + 20;
        if (scheduleTime.GetMinuteOfDay() > endTime.GetMinuteOfDay()) {
            station.AddDeparture(scheduleTime, platform, train);
        } else {
            break;
        }
    }

    platform = 5;
    minute = 15;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() <= 23) {
        Train *train = new Train("S1", "Solingen Hbf", "Duisburg-Schlenk - Duesseldorf Flughafen.");
        Time endTime(scheduleTime.GetMinuteOfDay());
        scheduleTime = scheduleTime + 20;
        if (scheduleTime.GetMinuteOfDay() > endTime.GetMinuteOfDay()) {
            station.AddDeparture(scheduleTime, platform, train);
        } else {
            break;
        }
    }

    platform = 2;
    minute = 35;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() <= 23) {
        Train *train = new Train("S2", "Dortmund Hbf", "Oberhausen - Gelsenkirchen - WanneEickel.");
        Time endTime(scheduleTime.GetMinuteOfDay());
        scheduleTime = scheduleTime + 60;
        if (scheduleTime.GetMinuteOfDay() > endTime.GetMinuteOfDay()) {
            station.AddDeparture(scheduleTime, platform, train);
        } else {
            break;
        }
    }

    platform = 4;
    minute = 22;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() <= 23) {
        Train *train = new Train("RE1", "Aachen Hbf", "Duesseldorf Flughafen - Duesseldorf - Koeln.");
        Time endTime(scheduleTime.GetMinuteOfDay());
        scheduleTime = scheduleTime + 60;
        if (scheduleTime.GetMinuteOfDay() > endTime.GetMinuteOfDay()) {
            station.AddDeparture(scheduleTime, platform, train);
        } else {
            break;
        }
    }

    platform = 10;
    minute = 24;
    scheduleTime.SetTime(0, minute);
    while (scheduleTime.GetHour() <= 23) {
        Train *train = new Train("RE2", "Muenster Hbf", "Muelheim(Ruhr) - Essen - Gelsenkirchen.");
        Time endTime(scheduleTime.GetMinuteOfDay());
        scheduleTime = scheduleTime + 60;
        if (scheduleTime.GetMinuteOfDay() > endTime.GetMinuteOfDay()) {
            station.AddDeparture(scheduleTime, platform, train);
        } else {
            break;
        }
    }
}
