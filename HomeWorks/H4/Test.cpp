

     #include <iostream>
     #include<vector> /* For setw */
     #include<cmath> /* For fmod*/

    #include <iomanip>
    #include <iostream>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string>


    using namespace std;


//Task 1: Defining a class ::Time

         class Time
         {
                private :
                   unsigned  int minuteOfDay;

                public :
                    Time(unsigned int minuteOfDay=0)
                    {

                       Time Time::fmod(1440,60);

                    }
                    Time(unsigned int hour, unsigned int minute)

                    {
                        set_time(hour,minute);
                    }

               void set_time(unsigned int hour, unsigned int minute)
                    {   if((hour>23||minute>59)
                           {
                        minuteOfDay=0;
                        std::cerr << "Invalid arguments. Hours should be < 24 and minutes should be < 60" << std::endl;
                        return;
                           }
                           minuteOfDay=hour*60+minute;
                    }

                  unsigned int  get_hour()
                    {
                       return  minuteOfDay/60;
                    }

                    get_minute()
                    {
                       return minuteOfDay%60;
                    }

                    get_minuteOfDay()
                    {
                      return minuteOfDay;
                    ]
           Time operator+(const uint time)
           {
            return Time(minuteOfDay + time);
            }
            friend std::istream& operator>>(std::istream& input, Time& time);
            friend std::ostream& operator<<(std::ostream& output, Time& time);
         };

//Task 2:: input operator
      istream& operator>>(istream&in,Time&time)
       {
           bool temp =false;
           string inputString;
           char colon=':';
        in>>inputString;
        int colonCheck=inputString.find(colon);
         if (colonCheck==-1)
          {
              temp=true;
          }
          String hour=inputString.substr(0,colon);
          String minute=inputString.substr(colonCheck+1,inputString.size());
         unsigned int hour_size=hour.size();
         unsigned int minute_size=minute.size();
         if(hour_size!=2&&minute_size!=2)
            { temp=true;}
         unsigned int tempHour=0;
         unsigned int tempMinute=0;
         try {
        tempHour = stoi(hour);
        tempMinute = stoi(minute);
    } catch (invalid_argument) {
        temp = true;
    }

    Time.set_time(tempHour, tempMinute);

    if (temp) {
        throw invalid_argument("Invalid input. Input should match hh:mm pattern.");
    }

    return in;


       }
//Task 3 ::Output Operator
       ostream& operator<<(ostream& out,Time &time)
       {
           unsigned int hour =time.get_hour();
        unsigned int  minute = time.get_minute;
    string timeString;
    if (hour < 10) {
        timeString += '0';
    }

    timeString += to_string(hour);
    timeString += ':';

    if (minute < 10) {
        timeString += '0';
    }
    timeString += to_string(minute);
    out << timeString;
    return out;
       }
//Task 4 :: Class Train

    class Train
    {
        private:
         const string no,to,over ;

        public:
            Train(const string no ,const string to ,const string over);
            ~Train(){
                cout << "Train " << no << " to " << to << " deleted" << endl;
                   }
       const   string  get_no(){return no;}
       const    string   get_to(){return to;}
       const    string  get_over(){return over;}

    };

    /** another possibility??
    Train(string a,string b,string c):

         no(a),
         to(b),
         over(c)
     {}
     ~Train()
     {
        cout<<setw(4)<<setfill('0')<<hour<<':'<<setfill('0')<<minute
         <<setw(2)<<no
         <<setw(2)<<over
         <<setw(2)<<to
         <<setw(2)<<platform<<<deleted<endl;
     }
        string Train::get_no()
        {
            return no;
        }
         string Train::get_over()
        {
            return over;
        }
        string Train::get_to()
        {
            return to;
        }


        **/
//Task 5 :: Station class
class Station:
    {
        private: const string station;
                   const static unsigned int platforms=15;
                        Train*schedule[platformms][24*60];
        public :
            Station(const string stationName):
                station(stationName){
            for (int i = 0; i < platforms; i++) {
                for (int j = 0; j < 24 * 60; j++) {
                    schedule[i][j] = nullptr;
                }
            }
        }
            ~station(){
            for (int i = 0; i < platforms; i++) {
                for (int j = 0; j < 24 * 60; j++) {
                    if (schedule[i][j] == nullptr) {
                        continue;
                    }
                    Time time(j);
                    cout << time << " platform " << i << " ";
                    delete schedule[i][j];
                }
            }
        }



            void addDeparture(Time time ,unsigned int platform,Train*train)
                {
                   if (platform > platforms) {
                cerr << "Invalid arguments. Platform value must be < 15" << std::endl;
                return;
                }
                schedule[platform][time.get_minuteOfDay]=train;
                }
            void  showDepartures(Time time,unsigned int minutes)
                {
            unsigned int timeFrom = time.GetMinuteOfDay();
            unsigned int timeTo = time.GetMinuteOfDay() + minutes;
            Time endTime(time.GetMinuteOfDay());
            endTime = time + minutes;

            using setw;

            cout << station << endl;
            cout << "Departures " << time << '-' << endTime << std::endl;
            cout << "======================" << endl;
            cout << left << setw(6) << "Time " << setw(20) << "Train "
                    << setw(60) << "Over " << setw(20) << "To "
                    << setw(20) << "Platform " << std::endl;

            for (int i = 0; i < platforms; i++) {
                for (int j = timeFrom; j < timeTo; j++) {
                    if (schedule[i][j] == nullptr) {
                        continue;
                    }
                    Time time(j);
                    Train *train = schedule[i][j];

                    std::cout << std::left << setw(6) << time << setw(20) << train->get_no()
                            << setw(60) << train->get_over() << setw(20) << train->get_to()
                            << setw(20) << i << std::endl;
                }
            }
            std::cout << "======================" << std::endl;
        }

        };
//Main function
    int main(void)
    {Station duisburg("Main station");
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
