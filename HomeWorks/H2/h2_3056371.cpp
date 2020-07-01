  /*************************************************
        Task No.: H2
        Last,Family Name: Hossain
        First,Given Name: Azahar
        Matriculation number: 3056371
        Uni-Email: azahar.hossain@stud.uni-due.de
        Course of Studies: ISE CE
*************************************************/


    #include <iostream>
    #include <iomanip>

    using namespace std;

// Task 1
struct CFNode {
  int value;
  CFNode* next;

  CFNode(int v) {
    value = v;
    next = nullptr;
  }
};

// Task 2
CFNode* append(CFNode* list, int value) {
  auto p = list;
  while (p->next) {
    p = p->next;
  }
  p->next = new CFNode(value);
  return list;
}

// Task 3
void remove(CFNode* list) {
  cout << "delete:";
  while (list) {
    auto p = list->next;
	  cout << " " << list->value;
    delete list;
    list = p;
  }
  cout << endl;
}

// Task 4
double calculate(CFNode* list) {
  double result = list->value;
  if (list->next) {
    result += 1.0 / calculate(list->next);
  }
  return result;
}

// Task 5
CFNode* build() {
  cout << fixed << setprecision(15);
  cout << "continued fraction, enter first value f_0: ";
  int f;
  cin >> f;
  auto result = new CFNode(f);
  for (int i = 1, f = 1; f > 0; i++) {
    cout << "enter next part denominator f_" << i << " (<= 0 for end): ";
    cin >> f;
    if (f > 0) {
      append(result, f);
    }
  }
  return result;
}

// Task 6
int main() { while (true){
  auto cf1 = append(append(append(append(new CFNode(1), 4), 2), 1), 7);
  cout << "cf1 = 123/100 = " << calculate(cf1) << endl;
  remove(cf1);

  auto cf2 = append(append(append(new CFNode(1), 1), 2), 3);
  cout << "cf2 = 17/10 = " << calculate(cf2) << endl;
  remove(cf2);

  auto cf3 = build();
  cout << "value inputted continued fraction cf3 = " << calculate(cf3) << endl;
  remove(cf3);
}
}
