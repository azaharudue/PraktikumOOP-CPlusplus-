#include <iostream>
#include <cstring>

using namespace std;

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 0 : empty
class Date
{
public:
    int day, month, year;
public:
    Date ()
    {
        day = month = year = 0;
    }
    Date (const Date &d)
    {
        day = d.day;
        month = d.month;
        year = d.year;
    }
    Date operator + (int n)
    {
        Date tmp = *this;
        tmp.day += n;
        if (tmp.day > daysInMonth[month])
        {
            tmp.day -= daysInMonth[month];
            tmp.month ++;
            if (tmp.month > 12)
            {
                tmp.year ++;
                tmp.month = 1;
            }
        }
        return tmp;
    }
    Date* operator = (Date& d)
    {
        day = d.day;
        month = d.month;
        year = d.year;
        return this;
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
public:
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
    ~Hotel ()
    {
        cout<<"destructor hotel "<<name<<" "<<arrival<<" for "<<get_guests()<<" guests done"<<endl;
    }
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
        return singles * 1 + doubles * 2;
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
        cout<<arrival<<" "<<name<<" for "<<nights<<" night(s) ";
        if (doubles >= 0)
            cout<<doubles<<" double bed room(s) ";
        if (singles >= 0)
            cout<<singles<<" single bed room(s) ";
        cout<<boardstr[board]<<endl;
    }
};

class Transport
{
public:
    Transport () {}
    virtual ~Transport()
    {
        cout<<"destructor Transport done"<<endl;
    }
    virtual bool withTransfer () = 0;
    virtual double get_price () = 0;
    virtual void print () = 0;
    virtual void input () = 0;
};

class Selforganised : public Transport
{
public:
    Selforganised () {}
    ~Selforganised ()
    {
        cout<<"destructor SelfOrganised done"<<endl;
    }
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
    string trcode, from, to;
    double priceOneSeat;
    bool firstClass;
public:
    Publictransport () {}
    Publictransport (class Date d)
    {
        depature = d;
    }
    ~Publictransport()
    {
        cout<<"destructor PublicTransport "<<trcode<<" at "<<depature<<" done"<<endl;
    }
    Publictransport (class Date d, string c, string f, string t, double pos = 0, bool fc = false)
    {
        depature = d;
        trcode = c;
        from = f;
        to = t;
        priceOneSeat = pos;
        firstClass = fc;
    }
};

class Flight : public Publictransport
{
    bool transfer;
public:
    Flight () {}
    Flight (class Date d)
    {
        depature = d;
    }
    Flight (class Date d, string c, string f, string t, double pos = 0, bool fc = false, bool tr = true)
    {
        depature = d;
        trcode = c;
        from = f;
        to = t;
        priceOneSeat = pos;
        firstClass = fc;
        transfer = tr;
    }
    ~Flight ()
    {
        cout<<"destructor Flight done"<<endl;
    }
    bool withTransfer ()
    {
        return true;
    }
    double get_price ()
    {
        if (firstClass == true)
            return priceOneSeat * 2;
        return priceOneSeat;
    }
    void print ()
    {
        cout<<"flight "<<depature<<" "<<trcode<<" from "<<from<<" to "<<to<<endl;
    }
    void input()
    {
        getline(cin, trcode);
        cout<<"code of flight: ";
        getline(cin, trcode);
        cout<<"airport of departure: ";
        getline(cin, from);
        cout<<"airport of arrival: ";
        getline(cin, to);
        cout<<"price for one passenger: ";
        cin>>priceOneSeat;
    }
};

class Train : public Publictransport
{
public:
    Train () {}
    Train (class Date d)
    {
        depature = d;
    }
    Train (class Date d, string c, string f, string t, double pos = 0, bool fc = false)
    {
        depature = d;
        trcode = c;
        from = f;
        to = t;
        priceOneSeat = pos;
        firstClass = fc;
    }
    ~Train ()
    {
        cout<<"destructor Train done"<<endl;
    }
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
        cout<<"train "<<depature<<" "<<trcode<<" from "<<from<<" to "<<to<<endl;
    }
    virtual void input ()
    {
        getline(cin, trcode);
        cout<<"code of train: ";
        getline(cin, trcode);
        cout<<"main train station of departure: ";
        getline(cin, from);
        cout<<"main train station of arrival: ";
        getline(cin, to);
        cout<<"price for one passenger: ";
        cin>>priceOneSeat;
    }
};
int lastNo = 0;
class Trip
{
public:
    int no;
    int travellers;
    class Hotel* hotel;
    class Transport* transportOutward;
    class Transport* transportBack;
    class Trip* next;
public:
    Trip(int trav = 1, class Hotel *ht = NULL, class Transport* to = NULL, class Transport* tb = NULL, class Trip* n = NULL)
    {
        travellers = trav;
        hotel = ht;
        transportOutward = to;
        transportBack = tb;
        next = n;
        lastNo ++;
        no = lastNo;
    }
    ~Trip()
    {
        delete hotel;
        delete transportOutward;
        delete transportBack;
        cout<<"destructor Trip done"<<endl;
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
        cout<<total<<endl;
        total += transportOutward->get_price();
        total += transportBack->get_price();
        if (transportBack->withTransfer())
            total += (transportBack->get_price() + transportOutward->get_price()) / 2;
        return total * hotel->nights;
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
            transportOutward->input();
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
            transportBack->input();
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
        if (transportOutward->withTransfer() || transportBack->withTransfer())
            cout<<"transfer included"<<endl;
        else
            cout<<"no transfer"<<endl;
        cout<<"price: "<<get_price()<<" EUR"<<endl<<endl;
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
        t->next = trips;
        trips = t;
    }
    void remove (class Trip* t)
    {
        class Trip* it = trips;
        if (trips == NULL || t == NULL)
            return;
        if (trips == t)
        {
            trips = trips->next;
            delete t;
            return;
        }
        for ( ; it->next != NULL; it = it->next)
        {
            if (it->next == t)
            {
                it->next = t-> next;
                delete t;
                return;
            }
        }
    }
    class Trip* search (int num)
    {
        if (trips == NULL)
            return NULL;
        class Trip* it = trips;
        for ( ; it != NULL; it = it->next)
        {
            if (it->no == num)
            {
                it->print();
                cout<<"(d)elete or (n)ot: ";
                char choise;
                cin>>choise;
                if (choise == 'd')
                {
                    remove(it);
                    break;
                }
                return it;
            }
        }
        return NULL;
    }
    void printAllTrips()
    {
        class Trip* it = trips;
        for ( ; it != NULL; it = it->next)
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
        cout<<endl<<"HOTLINE TRAVEL AGENCY"<<endl;
        cout<<"0 end"<<endl;
        cout<<"1 new trip"<<endl;
        cout<<"2 search trip"<<endl;
        cout<<"3 show all trip offers"<<endl;
        cout<<"your choice: ";
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
            if (travelagency.search(num) == NULL)
                cout<<"trip not found"<<endl;
            break;
        case '3':
            travelagency.printAllTrips();
            break;
        }
    }
}
