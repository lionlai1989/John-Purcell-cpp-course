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
    Person(string name, int age) : name(name), age(age) {
    }

    Person() : name(""), age(0) {
    }

    // Provide a copy constructor. &other here is a reference.
    Person(const Person &other) {
        cout << "Copy constructor running" << endl;
        name = other.name;
        age = other.age;
    }

    // When Person object is used as keys, the map object does not want you to go it there and alter
    // the key value, it->first is returned as const value. Thus, print() is not allowed to change
    // the key. Hence, const is used.
    // void print() {
    //     cout << name << ": " << age << flush;
    // }
    void print() const {
        cout << name << ": " << age << flush;
    }

    // If Person object is used as key in map, the c++ needs to compare different objects of Person
    // class in order to sort the keys in the map in the right order. Ultimately, c++ uses less than
    // "<" operator to compare. Eg,
    // string test1 = "Mike";
    // string test2 = "Bob";
    // assert test2 < test1
    // Here, operator "<" behaves like a method of string object test1, test2 is a parameter passed
    // to the method. That means we have to implement "<" operator in Person class in order to use
    // Person object as key in the map so that map can sort it. ie, overload operator "<".
    bool operator<(const Person &other) const {
        // The implementation of "<"
        return name < other.name; // compare string object.
    }
    // bool: return True/False
    // const Person &other: the parameter that this operator accepts, which is another Person. And
    // it must be const because it would be crazy that the "<" operator changes the object on which
    // it operates. We use reference &other for efficiency instead of copy the object.
    // const in the end: the whole method must also be const because the Peron object itself should
    // not be changed either.
};

class Person1 {
  private:
    string name;
    int age;

  public:
    Person1(string name, int age) : name(name), age(age) {
    }

    Person1() : name(""), age(0) {
    }

    // Provide a copy constructor. &other here is a reference.
    Person1(const Person1 &other) {
        cout << "Copy constructor running" << endl;
        name = other.name;
        age = other.age;
    }
    void print() const {
        cout << name << ": " << age << flush;
    }

    bool operator<(const Person1 &other) const {
        // To demonstrate another way of overloading operator.
        if (name == other.name) {
            return age < other.age;
        } else {
            return name < other.name;
        }
    }
};

int main() {
    map<Person, int> people;

    cout << "case 1" << endl;
    people[Person("Mike", 40)] = 49;
    people[Person("Raj", 20)] = 29;
    people[Person("Vicky", 30)] = 30;
    for (map<Person, int>::iterator it = people.begin(); it != people.end(); it++) {
        cout << it->second << ": " << flush;
        it->first.print();
        cout << endl;
    }
    // 49: Mike: 40
    // 29: Raj: 20
    // 30: Vicky: 30

    cout << "case 2" << endl;
    people[Person("Mike", 40)] = 49;
    people[Person("Mike", 40)] = 123;
    people[Person("Raj", 20)] = 29;
    people[Person("Vicky", 30)] = 30;
    for (map<Person, int>::iterator it = people.begin(); it != people.end(); it++) {
        cout << it->second << ": " << flush;
        it->first.print();
        cout << endl;
    }
    // 123: Mike: 40. people[Person("Mike", 40)] is updated.
    // 29: Raj: 20
    // 30: Vicky: 30

    cout << "case 3" << endl;
    people[Person("Mike", 40)] = 49;
    people[Person("Mike", 444)] = 123;
    people[Person("Raj", 20)] = 29;
    people[Person("Vicky", 30)] = 30;
    for (map<Person, int>::iterator it = people.begin(); it != people.end(); it++) {
        cout << it->second << ": " << flush;
        it->first.print();
        cout << endl;
    }
    // 123: Mike: 40. The key is not updated in people[Person("Mike", 40)]. What is happening here
    // is that Person("Mike", 444) is the same as key Person("Mike", 40), because we overload the
    // operator "<". Therefore, key Person("Mike", 40) is not updated but the value is updated with 123.
    // 29: Raj: 20
    // 30: Vicky: 30

    cout << "case 4" << endl;
    map<Person1, int> people1;
    people1[Person1("Mike", 40)] = 49;
    people1[Person1("Mike", 444)] = 123;
    people1[Person1("Raj", 20)] = 29;
    people1[Person1("Vicky", 30)] = 30;
    for (map<Person1, int>::iterator it = people1.begin(); it != people1.end(); it++) {
        cout << it->second << ": " << flush;
        it->first.print();
        cout << endl;
    }
    // 49: Mike: 40
    // 123: Mike: 444 // Now Person1("Mike", 444) is added because the operator "<" of Person1
    // determines that Person1("Mike", 444) and Person1("Mike", 40) are different
    // 29: Raj: 20
    // 30: Vicky: 30

    return 0;
}
