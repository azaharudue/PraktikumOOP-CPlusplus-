#include <iostream>
#include <cstring>

using namespace std;

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 0 : empty
class Date
{

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
    int get_nights ()
    {
        return nights;
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
    class Date& get_departure()     { return depature;  }
    string& get_code()              { return trcode;    }
    string& get_from ()             { return from;      }
    string& get_to ()               { return to;        }
    double& get_priceoneseat()      { return priceOneSeat; }
    bool& get_firstclass()          { return firstClass; }
    void set_departure(class Date d) { depature = d;    }
    void set_code(string c)         { trcode = c;       }
    void set_from (string f)        { from = f;         }
    void set_to (string t)          { to = t;           }
    void set_priceoneseat(double p) { priceOneSeat = p; }
    void set_firstclass(bool f)     { firstClass = f;   }
};

class Flight : public Publictransport
{
    bool transfer;
public:
    Flight () {}
    Flight (class Date d)
    {
        set_departure (d);
    }
    Flight (class Date d, string c, string f, string t, double pos = 0, bool fc = false, bool tr = true)
    {
        set_departure (d);
        set_code (c);
        set_from (f);
        set_to (t);
        set_priceoneseat (pos);
        set_firstclass (fc);
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
        if (get_firstclass() == true)
            return get_priceoneseat() * 2;
        return get_priceoneseat();
    }
    void print ()
    {
        cout<<"flight "<<get_departure()<<" "<<get_code()<<" from "<<get_from()<<" to "<<get_to()<<endl;
    }
    void input()
    {
        getline(cin, get_code());
        cout<<"code of flight: ";
        getline(cin, get_code());
        cout<<"airport of departure: ";
        getline(cin, get_from());
        cout<<"airport of arrival: ";
        getline(cin, get_to());
        cout<<"price for one passenger: ";
        cin>>get_priceoneseat();
    }
};

class Train : public Publictransport
{
public:
    Train () {}
    Train (class Date d)
    {
        set_departure (d);
    }
    Train (class Date d, string c, string f, string t, double pos = 0, bool fc = false)
    {
        set_departure (d);
        set_code (c);
        set_from (f);
        set_to (t);
        set_priceoneseat (pos);
        set_firstclass (fc);
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
        if (get_firstclass() == true)
            return get_priceoneseat() * 1.5;
        return get_priceoneseat();
    }
    void print ()
    {
        cout<<"train "<<get_departure()<<" "<<get_code()<<" from "<<get_from()<<" to "<<get_to()<<endl;
    }
    virtual void input ()
    {
        getline(cin, get_code());
        cout<<"code of flight: ";
        getline(cin, get_code());
        cout<<"airport of departure: ";
        getline(cin, get_from());
        cout<<"airport of arrival: ";
        getline(cin, get_to());
        cout<<"price for one passenger: ";
        cin>>get_priceoneseat();
    }
};
int lastNo = 0;
class Trip
{
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
        total += transportOutward->get_price();
        total += transportBack->get_price();
        if (transportBack->withTransfer())
            total += (transportBack->get_price() + transportOutward->get_price()) / 2;
        return total * hotel->get_nights();
    }
    void input()
    {
        hotel = new Hotel();
        hotel->input();
        travellers = hotel->get_guests();
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
        t->set_next(trips);
        trips = t;
    }
    void remove (class Trip* t)
    {
        class Trip* it = trips;
        if (trips == NULL || t == NULL)
            return;
        if (trips == t)
        {
            trips = trips->get_next();
            delete t;
            return;
        }
        for ( ; it->get_next() != NULL; it = it->get_next())
        {
            if (it->get_next() == t)
            {
                it->set_next(t->get_next());
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
        for ( ; it != NULL; it = it->get_next())
        {
            if (it->get_no() == num)
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
        for ( ; it != NULL; it = it->get_next())
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