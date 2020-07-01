  /*************************************************
Aufgabe Nr./Task No.: H5
Nachname/Last,Family Name: Hossain
Vorname/First,Given Name: Azahar
Matrikelnummer/Matriculation number: 3056371
Studiengang/Degree Programme: ISE CE
*************************************************/

        #include <iostream>
        #include <iomanip>
        using namespace std;






/*SUBTASK 01:CLASS DATE*/
 class Date
 { private : unsigned short int day,month,year;
   public : Date(unsigned short int d,unsigned short int m,unsigned short int y)
                {day=d;month=m;year=y;} //Date constructor with three attributes
            Date operator +(const Date&); // + operator
            friend iostream& operator >>(); //friend operator in
            friend ostream& operator <<();//friend operator out
};
/*SUBTASK 02:           */
/*SUBTASK 03:           */
/*SUBTASK 04:           */
/*SUBTASK 05:           */

