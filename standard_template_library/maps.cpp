#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

int main() {
    map<string, int> ages;

    ages["Mike"] = 40;
    ages["Raj"] = 20;
    ages["Vicky"] = 30;

    ages["Mike"] = 70;

    cout << ages["Raj"] << endl; // 20

    // It returns 0. However, Sue is not in the map. Sue is being created as soon as Sue is being
    // accessed. Thus, it's not a right way to check if Sue is in the map.
    cout << ages["Sue"] << endl;

    // It's the right way to check if a key is in a map.
    if (ages.find("Vicky") != ages.end()) {
        cout << "Found Vikcy" << endl;
    } else {
        cout << "Key not found" << endl;
    }

    cout << "Iterate through an map object." << endl;
    for (map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
    // Mike: 70
    // Raj: 20
    // Sue: 0
    // Vicky: 30

    cout << "The other ways of inserting elements in a map. Map actually stores pair object." << endl;
    pair<string, int> add_to_map("Peter", 100);
    ages.insert(add_to_map);
    ages.insert(pair<string, int>("Zion", 101));
    ages.insert(make_pair("Josh", 102));

    cout << "Another way of iterating through map." << endl;
    for (map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
        pair<string, int> age = *it;
        cout << age.first << ": " << age.second << endl;
    }
    // Josh: 102
    // Mike: 70
    // Peter: 100
    // Raj: 20
    // Sue: 0
    // Vicky: 30
    // Zion: 101

    return 0;
}
