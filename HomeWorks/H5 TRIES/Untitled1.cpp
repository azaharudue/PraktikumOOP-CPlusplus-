#include <iostream>
#include <cstring>

using namespace std;

class Date
{
public:
    int daysInMonth[13]; // 0 : empty
    int day, month, year;
public:
    Date ()
    {
        daysInMonth[1] = 31;
        daysInMonth[2] = 28;
        daysInMonth[3] = 31;
        daysInMonth[4] = 30;
        daysInMonth[5] = 31;
        daysInMonth[6] = 30;
        daysInMonth[7] = 31;
        daysInMonth[8] = 31;
        daysInMonth[9] = 30;
        daysInMonth[10] = 31;
        daysInMonth[11] = 30;
        daysInMonth[12] = 31;
        day = month = year = 0;
    }
    Date operator + (int n)
    {
        Date tmp = *this;
        tmp.day += n;
        if (tmp.day > tmp.daysInMonth[month])
        {
            tmp.day -= tmp.daysInMonth[month];
            tmp.month ++;
            if (tmp.month > 12)
            {
                tmp.year ++;
                tmp.month = 1;
            }
        }
        return tmp;
    }
    friend istream& operator >> (istream& is, Date& date);
    friend ostream& operator << (ostream& os, Date& date);
};
istream& operator >> (istream& is, Date& date)
{
    scanf ("%d.%d.%d", &date.day, &date.month, &date.year);
    return is;
}
ostream& operator << (ostream& os, Date& date)
{
    printf ("%d.%d.%d", date.day, date.month, date.year);
    return os;
}

enum Board
{
    noMeals,
    breakfast,
    halfBoard,
    allInclusive
};
string boardstr[4] = {"without meals", "with breakfast", "with halfboard", "all inclusive"};

class Hotel
{
    string name;
    int nights, singles, doubles;
    double priceNightSingle;
    double priceNightDouble;
    bool parking;
    class Date arrival;
    Board board;
public:
    Hotel()
    {
        priceNightSingle = 100;
        priceNightDouble = 150;
    }
    ~Hotel () {}
    double get_price ()
    {
        return priceNightDouble * doubles + priceNightSingle * singles + 10 * parking;
    }
    class Date get_arrival ()
    {
        return arrival;
    }
    class Date get_checkout ()
    {
        return arrival + nights;
    }
    int get_guests ()
    {
        return 0;
    }
    void input()
    {
        cout<<"name of hotel: ";
        cin>>name;
        cout<<"arrival on: ";
        cin>>arrival;
        cout<<"how many nights: ";
        cin>>nights;
        cout<<"how many single bed rooms: ";
        cin>>singles;
        cout<<"how many double bed rooms: ";
        cin>>doubles;
        cout<<"a all inclusive"<<endl<<"b breakfast"<<endl<<"h half board"<<endl<<"w without meals"<<endl;
        char temp;
        cin>>temp;
        switch (temp)
        {
        case 'a':
            board = allInclusive; break;
        case 'b':
            board = breakfast; break;
        case 'h':
            board = halfBoard; break;
        case 'w':
            board = noMeals; break;
        }
        cout<<"price one night in single bed room: ";
        cin>>priceNightSingle;
        cout<<"price one night in double bed room: ";
        cin>>priceNightDouble;
        cout<<"with parking (y(es) or n(o)): ";
        cin>>temp;
        if (temp == 'y')
            parking = true;
        else
            parking = false;
    }
    void print ()
    {
        cout<<arrival<<" "<<name<<" for "<<nights<<" night(s) "<<doubles<<" double bed room(s) "<<singles<<" single bed room(s) ";
        cout<<boardstr[board]<<endl;
    }
};

class Transport
{
public:
//    Transport () {}
//    virtual ~Transport() = 0;
    virtual bool withTransfer () = 0;
    virtual double get_price () = 0;
    virtual void print () = 0;
    virtual void input () = 0;
};

class Selforganised : public Transport
{
public:
//    Selforganised () {}
//    ~Selforganised ()
//    {
//        cout<<"self des"<<endl;
//    }
    bool withTransfer ()
    {
        return false;
    }
    double get_price ()
    {
        return 0;
    }
    void print ()
    {
        printf ("selforganised transport\n");
    }
    void input ()
    {
    }
};

class Publictransport : public Transport
{
public:
    class Date depature;
    string code, from, to;
    double priceOneSeat;
    bool firstClass;
public:
    Publictransport (class Date d, string c = NULL, string f = NULL, string t = NULL, double pos = 0, bool fc = false)
    {
        depature = d;
        code = c;
        from = f;
        to = t;
        priceOneSeat = pos;
        firstClass = fc;
    }
//    virtual ~Publictransport() = 0;
//    virtual void print () = 0;
//    virtual void input() = 0;
};

class Flight : public Publictransport
{
    bool transfer;
public:
    Flight (class Date d, string c = NULL, string f = NULL, string t = NULL, double pos = 0, bool fc = false, bool tr = true)
         : Publictransport (d, c, f, t, pos, fc)
    {
        transfer = tr;
    }
//    ~Flight () {}
    bool withTransfer ()
    {
        return transfer;
    }
    double get_price ()
    {
        if (firstClass == true)
            return priceOneSeat * 2;
        return priceOneSeat;
    }
    void print ()
    {
        printf ("flight\n");
    }
    void input()
    {
        cout<<"code of flight: ";
        cin>>code;
        cout<<"airport of departure: ";
        cin>>from;
        cout<<"airport of arrival: ";
        cin>>to;
        cout<<"price for one passenger: ";
        cin>>priceOneSeat;
    }
};

class Train : public Publictransport
{
public:
    Train (class Date d, string c = NULL, string f = NULL, string t = NULL, double pos = 0, bool fc = false)
         : Publictransport (d, c, f, t, pos, fc)
    {
    }
//    ~Train () {}
    bool withTransfer ()
    {
        return false;
    }
    double get_price ()
    {
        if (firstClass == true)
            return priceOneSeat * 1.5;
        return priceOneSeat;
    }
    void print ()
    {
        printf ("train\n");
    }
    virtual void input ()
    {
        cout<<"code of train: ";
        cin>>code;
        cout<<"main train station of departure: ";
        cin>>from;
        cout<<"main train station of arrival: ";
        cin>>to;
        cout<<"price for one passenger: ";
        cin>>priceOneSeat;
    }
};

class Trip
{
public:
    int no;
    int lastNo;
    int travellers;
    class Hotel* hotel;
    class Transport* transportOutward;
    class Transport* transportBack;
    class Trip* next;
public:
    Trip(int trav = 0, class Hotel *ht = NULL, class Transport* to = NULL, class Transport* tb = NULL, class Trip* n = NULL)
    {
        travellers = trav;
        hotel = ht;
//        transportOutward = new Train();
//        transportBack = new Transport();
        next = n;
    }
    ~Trip()
    {
//        delete hotel;
//        delete transportOutward;
//        delete transportBack;
        //output message
    }
    int get_no ()
    {
        return no;
    }
    class Trip* get_next ()
    {
        return next;
    }
    void set_next(class Trip* n)
    {
        next = n;
    }
    double get_price ()
    {
        double total = hotel->get_price();
        total += transportOutward->get_price();
        total += transportBack->get_price();
        return total;
    }
    void input()
    {
        hotel = new Hotel();
        hotel->input();
        cout<<"please choose transport for outward journey"<<endl;
        cout<<"0 self organised"<<endl;
        cout<<"1 by flight"<<endl;
        cout<<"2 by train"<<endl;
        cout<<"your choice: ";
        char temp = '0';
        cin>>temp;
        switch (temp)
        {
        case '0':
            transportOutward = new Selforganised();
//            transportOutward->input();
            break;
        case '1':
            transportOutward = new Flight(hotel->get_arrival());
            transportOutward->input();
            break;
        case '2':
            transportOutward = new Train(hotel->get_arrival());
            transportOutward->input();
            break;
        }
        cout<<"please choose transport for journey back"<<endl;
        cout<<"0 self organised"<<endl;
        cout<<"1 by flight"<<endl;
        cout<<"2 by train"<<endl;
        cout<<"your choice: ";
        cin>>temp;
        switch (temp)
        {
        case '0':
            transportBack = new Selforganised();
//            transportBack->input();
            break;
        case '1':
            transportBack = new Flight(hotel->get_checkout());
            transportBack->input();
            break;
        case '2':
            transportBack = new Train(hotel->get_checkout());
            transportBack->input();
            break;
        }
    }
    void print()
    {
        cout<<"trip inquiry "<<no<<" for "<<travellers<<" person(s)"<<endl;
        cout<<"check-in: hotel ";
        hotel->print();
        cout<<"outward journey: ";
        transportOutward->print();
        cout<<"journey back: ";
        transportBack->print();
        if (transportOutward->withTransfer())
            cout<<"transfer included"<<endl;
        else
            cout<<"no transfer"<<endl;
        cout<<"price: "<<get_price()<<" EUR"<<endl;
    }
};

class TravelAgency
{
    class Trip* trips;
public:
    TravelAgency (class Trip* t = NULL)
    {
        trips = t;
    }
    void add (class Trip* t)
    {
        class Trip* it = trips;
        for ( ; it->next != NULL; it = it->next);
        it->next = t;
    }
    void remove (class Trip* t)
    {
        class Trip* it = trips;
        if (trips == t)
        {
            trips = trips->next;
            return;
        }
        for ( ; it->next != NULL; it = it->next)
        {
            if (it->next == t)
            {
                it->next = t-> next;
                return;
            }
        }
    }
    class Trip* search (int num)
    {
        class Trip* it = trips;
        for ( ; it->next != NULL; it = it->next)
        {
            if (it->no == num)
            {
                return it;
            }
        }
        return NULL;
    }
    void printAllTrips()
    {
        class Trip* it = trips;
        for ( ; it->next != NULL; it = it->next)
        {
            it->print();
        }
    }
};

int main ()
{
    class TravelAgency travelagency;
    char choise;
    int num;
    while (1)
    {
        printf ("HOTLINE TRAVEL AGENCY\n");
        printf ("0 end\n1 new trip\n2 search trip\n3 show all trip offers\nyour choice: ");
        cin>>choise;
        switch (choise)
        {
        case '0':
            return 0;
        case '1':
            {
                class Trip* temp = new Trip();
                temp->input();
                travelagency.add(temp);
            }
            break;
        case '2':
            cout<<"number of trip: ";
            cin>>num;
            travelagency.search(num)->print();
            break;
        case '3':
            travelagency.printAllTrips();
            break;
        }
    }
}
