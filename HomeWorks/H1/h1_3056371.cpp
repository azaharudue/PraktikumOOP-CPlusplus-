              /*************************************************
            Aufgabe Nr./Task No.: H1
            Nachname/Last,Family Name: Hossain
            Vorname/First,Given Name: Azahar
            Matrikelnummer/Matriculation number: 3056371
            Uni-Email: azahar.hossain@stud.uni-due.de
            Studiengang/Course of Studies: ISE CE
            *************************************************/
            #include <iostream>
            #include<string>
            #include<cstring>
            #include<iomanip>
            #include<cstdlib>
            #include <algorithm>
    using namespace std;
       //Subtask 1:enumeration for the type of contacts
    enum phoneNrType
                 {
                    fax,home,mobile,work,other
                  };
       //Subtask 2:  Struct with 2 strings and type of contacts
    struct Contact
                {
                    string name;
                    string number;
                    phoneNrType pType;
                };
                //constant integer initialized with>1
            int const Max_Contacts =5000;
            //Array of contacts with maximum number of contacts
            Contact ContactList[Max_Contacts];
            //Current or actual no
            int actualNO =0;
    //Subtask 3: A boolean function
    bool insertContacts()
    {        if (actualNO==Max_Contacts)
                    {
                        cout<<"Phonebook is full!!";
                         return false;
                     }

             else
                    {
                        Contact contact;
                        char p;
                                    cout << "please enter phone number: "<<endl; //Number input
                                    cin.ignore();
                                    getline(cin,contact.number);
                                    cin.sync();
                                    // name input
                                    cout << "please enter name: ";
                                    getline(cin, contact.name);
                                    cout << "type of number (f for fax, h for home, m for mobile, w for work, o for other): ";
                                    cin>>p;
                  //Checking the type of contacts
                                    switch(p){
                                     case  'F':
                                     case  'f':contact.pType=fax ;break;
                                     case  'h':
                                     case  'H':contact.pType=home ;break;
                                     case  'm':
                                     case  'M':contact.pType=mobile ;break;
                                     case  'w':
                                     case  'W':contact.pType=work ;break;
                                     case  'o':
                                     case  'O':contact.pType=other ;break;
                                     default : cout<<"No type like this!! Please check your input and try again .\n"<<endl;
                                       return false ;
                                       break;
                                        }

                    ContactList[actualNO]=contact;
                    actualNO++;

                    Contact temp;

                    for(int i =actualNO-1; i >= 1; i--){
                    if (ContactList[i].name < ContactList[i - 1].name)
                        {

                        temp = ContactList[i];
                        ContactList[i] = ContactList[i - 1];
                        ContactList[i - 1] = temp;
                    }
                    }

                return true;

            }
        }
        // Subtask :4  delete function with boolean return value
bool deleteContacts ()
    {

        cin.ignore();
        cout << "please enter name to delete: ";
	    string name;
	     getline(cin, name);
	Contact *end = std::remove_if(ContactList, ContactList + actualNO, [name](Contact c)  // using algorithm library
    {
		if (name == c.name) {
			return true;
		}
		return false;
	});
	if (end == ContactList + actualNO)

        {
		return false;
	    }
	actualNO -= ContactList + actualNO - end;
	return true;
    }

    //Subtask 5: Output saved contacts in formatted table
    void printContacts()
{

     cout<<setw(5)<<left<<"All Contacts:"<<endl;
     cout<<"------------------------------------------------------------------\n";
     cout<<"Name\t\t\t|| Number\t\t\t || Type\n\n";

    for (int i=0;i<actualNO;++i)
    {

        cout<<setw(30)<<left<<ContactList[i].name;
        cout<<setw(30)<<left<<ContactList[i].number;
        string pType;
        if (ContactList[i].pType == fax) {
			pType = "(fax)";
		}
        else if(ContactList[i].pType ==home)
			pType = "(home)";
		else if(ContactList[i].pType== mobile)
			pType = "(mobile)";
		else if(ContactList[i].pType== work)
			pType = "(work)";
		else
            pType = "(other)";


                cout<<(pType)<<endl;
        cout<<"..............................................................."<<endl;

    }
}
//Subtask 6:  main function
int main (void)

{     int s ;
 while (s!=0){

        cout << "*** " << actualNO << " contact entries ***";
        cout << "\n choose  any of the followings : \n";
        cout<<" 0 End "<<endl;
        cout<<" 1 to add new contact."<<endl;
        cout<<" 2 to delete contact."<<endl;
        cout<<" 3 to show all contacts."<<endl;
        cout<<" 9.to empty all contacts ."<<endl;
        cin.sync();
        cin>>s;
     switch (s)
    {        case 1 :if (insertContacts()){
                    cout<<"**Contact added successfully***\n";}

                    else cout<<" Storing the contact was failed !! "; //Error message
            break;
        case 2 :      if (deleteContacts()){
                            cout<<"Contact deleted successfully.\n\n";
                            }
                            else cout <<"Nothing deleted.\n"; //error message
                  break;
        case 3:printContacts(); break;
        case 9 : actualNO=0;
            cout<<"All contacts deleted.\n";
            break;
    }

 }
return EXIT_SUCCESS; //return with success

}
