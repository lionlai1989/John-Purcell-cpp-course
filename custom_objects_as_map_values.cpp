#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

class Person {
  private:
    string name;
    int age;

  public:
    // I define my own constructor that has parameters. I lose the default implementation of the
    // constructor with no parameters. Here, the map needs the constructor with no parameters,
    // because it needs to construct an object people[0], and Person("Mike", 40) is assigned to the
    // object people[0].
    Person(string name, int age) : name(name), age(age) {
    }

    // Fix the above issue with creating a construtor without parameters. The default parameters ""
    // and 0 is essential if no parameter is sent.
    Person() : name(""), age(0) {
    }

    // Provide a copy constructor. &other here is a reference.
    Person(const Person &other) {
        cout << "Copy constructor running" << endl;
        name = other.name;
        age = other.age;
    }

    void print() {
        cout << name << ": " << age << endl;
    }
};
int main() {
    map<int, Person> people;
    // map constructs an object with the construtor without passing parameters in and uses assignment
    // operator to assign values to that object. Be careful about what is actually happening here is
    // that by default c++ gives your classes "shallow copy". "shallow copy" copys the values of instance
    // variables, name and age, from the object, Person("Mike", 40), that you set the object,
    // people[0], equal to. Sometimes we do not want that because if there is a pointer in the
    // instance variables, and this pointer points to the memory allocated in the class. But we
    // don't want to copy the pointer in an object because we want to allocate more memory for this
    // pointer. In general, we do not want to copy pointers when copying objects, because we just
    // get a pointer pointing to the same place that the pointer in the other object points to. In
    // that case, we need to overwrite the assignment operator.
    people[49] = Person("Mike", 40);
    people[29] = Person("Raj", 20);
    people[19] = Person("Vicky", 30);
    people.insert(make_pair(55, Person("Babe", 45)));
    people.insert(make_pair(50, Person("Zion", 29)));
    for (map<int, Person>::iterator it = people.begin(); it != people.end(); it++) {
        cout << it->first << ": " << flush;
        it->second.print();
    }
    // 19: Vicky: 30
    // 29: Raj: 20
    // 49: Mike: 40
    // 50: Zion: 29
    // 55: Babe: 45

    return 0;
}
