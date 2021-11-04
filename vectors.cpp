#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Presize vector of 5 strings.
    vector<string> strings(5);
    strings.push_back("one"); // like append in python.
    strings.push_back("two");
    strings.push_back("three");

    strings[3] = "dog";
    cout << strings[3] << endl;     // dog
    cout << strings.size() << endl; // 8

    // No presize. Empty vector.
    vector<string> str;
    str.push_back("one"); // like append in python.
    str.push_back("two");
    str.push_back("three");
    str.push_back("four");

    cout << str[0] << endl;     // one
    cout << str.size() << endl; // 4

    // Iterate through vector.
    for (int i = 0; i < str.size(); i++) {
        cout << str[i] << endl;
    }

    // Use iterator object.
    vector<string>::iterator it = str.begin();
    cout << *it << endl; // one
    it++;
    cout << *it << endl; // two
    it = it + 2;
    cout << *it << endl; // four

    // Use iterator object to iterate vector.
    for (vector<string>::iterator it = str.begin(); it != str.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}
