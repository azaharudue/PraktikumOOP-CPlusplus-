       /******************************************************
Aufgabe Nr./Task No.:          H3
Nachname/Last,Family Name:     Hossain
Vorname/First,Given Name:      Azahar
Matr.-nr./Matr.-no.:           3056371
Uni-Email:                     azahar.hossain@stud.uni-due.de
Studiengang/Course of Studies: ISE CE
*******************************************************/



        #include <iostream>
        #include <fstream>
        #include <cstring>

using namespace std;

// 1. Define a data structure ...
struct Icd {
	string code, diagnosis;
	Icd *next;

	Icd(string code, string diagnosis) :
		code(code),
		diagnosis(diagnosis),
		next(nullptr) {
	}
};

// 2. Write a function reading a complete file ...
Icd *readFile() {
	Icd *head = nullptr, *tail = nullptr;
	ifstream file("Section111ValidICD10-2018.csv");
	if (file.is_open()) {
		string line;
		getline(file, line); // skip header
		while (getline(file, line)) {
			string code, diagnosis;
			size_t i = 0;
			while ((i < line.size()) && (line[i] != ';')) {
				code += line[i++]; // read code
			}
			if (i >= line.size()) {
				break; // failed to read code
			}
			i++;
			while ((i < line.size()) && (line[i] != ';')) {
				diagnosis += line[i++]; // read diagnosis
			}
			if (i >= line.size()) {
				break; // failed to read diagnosis
			}
			auto icd = new Icd(code, diagnosis);
			if (head == nullptr) {
				head = tail = icd;
			}
			else {
				tail->next = icd;
				tail = icd;
			}
		}
		file.close();
	}
	return head;
}

// functions searching for a substring in a string
bool isContain(string text, string subject) {
	if (text.size() >= subject.size()) { // check length
		for (size_t i = 0; i < text.size() - subject.size() + 1; i++) {
			auto found = true;
			for (size_t j = 0; j < subject.size(); j++) {
				if (toupper(text[i + j]) != toupper(subject[j])) {
					found = false;
					break; // not matched
				}
			}
			if (found) {
				return true; // matched
			}
		}
	}
	return false; // not found
}

// 3. Define a function with a pointer to the list ...
void search(Icd *list, string subject, bool searchCode) {
	auto entries = 0;
	for (auto p = list; p != nullptr; p = p->next) {
		if (isContain(searchCode ? p->code : p->diagnosis, subject)) {
			entries++; // found
			cout << p->code << "\t" << p->diagnosis << endl;
		}
	}
	if (entries <= 0) {
		cout << "\"" << subject << "\" not found" << endl;
	}
	else if (entries <= 1) {
		cout << "one entry found" << endl;
	}
	else {
		cout << entries << " entries found" << endl;
	}
}

int main()
{
	cout << "World Health Institution (WHO)" << endl;
	cout << "International Classification of Diseases (ICD)" << endl;
	auto list = readFile();
	auto quit = false;
	do {
		cout << "0 end" << endl;
		cout << "1 search for ICD code(s) (e.g. G4453)" << endl;
		cout << "2 search for diagnosis(s) (e.g. angina, Ebola, horse, malaria, wheelchair)" << endl;
		cout << ">> ";
		int choice;
		if (!(cin >> choice) || (choice < 0) || (choice > 2)) {
			cin.clear();
			cin.ignore(); // ignore error
			cout << "ERROR" << endl;
		}
		else if (choice == 0) {
			quit = true;
		}
		else if (choice == 1) {
			string code;
			cout << "to search for ICD code: ";
			cin >> code;
			search(list, code, true);
		}
		else if (choice == 2) {
			string diagnosis;
			cout << "to search for diagnosis: ";
			cin >> diagnosis;
			search(list, diagnosis, false);
		}
		cout << endl;
	} while (!quit);
	// delete list
	auto p = list;
	while (p != nullptr) {
		auto next = p->next;
		delete p;
		p = next;
	}
}
