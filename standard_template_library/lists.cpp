#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    list<int> numbers;

    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_front(0);

    list<int>::iterator it = numbers.begin();
    it++;
    cout << "Element: " << *it << endl; // 1
    numbers.insert(it, 4);
    it--;
    cout << "Insert: " << *it << endl; // 4

    list<int>::iterator erase_it = numbers.begin();
    erase_it++;
    // erase_it must catch the returned valid iterator of erase(), because erase() will invalidate
    // the parameter pointer, which means erase_it will become invalid.
    erase_it = numbers.erase(erase_it);
    cout << "Erase: " << *erase_it << endl; // 1

    for (list<int>::iterator it = numbers.begin(); it != numbers.end();) {
        if (*it == 2) {
            numbers.insert(it, 1234);
        }
        if (*it == 1) {
            it = numbers.erase(it);
        } else {
            it++;
        }
    }

    for (list<int>::iterator it = numbers.begin(); it != numbers.end(); it++) {
        cout << *it << endl;
    }
}
