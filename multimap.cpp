#include <iostream>
#include <map>
using namespace std;

int main() {
    multimap<int, string> lookup;
    // multimap does not have an overloaded array operator "[]". Thus, insert is used here.
    lookup.insert(make_pair(30, "Mike"));
    lookup.insert(make_pair(10, "Vikcy"));
    lookup.insert(make_pair(30, "Raj"));
    lookup.insert(make_pair(20, "Bob"));

    cout << "case 1" << endl;
    for (multimap<int, string>::iterator it = lookup.begin(); it != lookup.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
    // 10: Vikcy
    // 20: Bob
    // 30: Mike // The duplicated keys are stored.
    // 30: Raj

    cout << "case 2" << endl;
    for (multimap<int, string>::iterator it = lookup.find(20); it != lookup.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
    // 20: Bob // The starting value is 20.
    // 30: Mike
    // 30: Raj

    cout << "case 3" << endl;
    for (multimap<int, string>::iterator it = lookup.find(10); it != lookup.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
    // 10: Vikcy // THe starting value is 10.
    // 20: Bob
    // 30: Mike
    // 30: Raj

    cout << "case 4" << endl;
    pair<multimap<int, string>::iterator, multimap<int, string>::iterator> its = lookup.equal_range(30);
    // its.first gives the start of the range. its.second gives the end of the range.
    for (multimap<int, string>::iterator it = its.first; it != its.second; it++) {
        cout << it->first << ": " << it->second << endl;
    }
    // 30: Mike
    // 30: Raj

    cout << "case 5" << endl;
    pair<multimap<int, string>::iterator, multimap<int, string>::iterator> its2 = lookup.equal_range(20);
    for (multimap<int, string>::iterator it = its2.first; it != its2.second; it++) {
        cout << it->first << ": " << it->second << endl;
    }
    // 20: Bob

    // Use c++11!!!
    cout << "case 6" << endl;
    auto its3 = lookup.equal_range(30);
    for (multimap<int, string>::iterator it = its3.first; it != its3.second; it++) {
        cout << it->first << ": " << it->second << endl;
    }

    return 0;
}
