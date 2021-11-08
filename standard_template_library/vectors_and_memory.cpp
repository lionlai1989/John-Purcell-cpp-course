#include <iostream>
#include <vector>

using namespace std;

int case_1() {
    vector<double> numbers(5);

    cout << "Size: " << numbers.size() << endl;

    int capacity = numbers.capacity();
    cout << "Capacity: " << capacity << endl;

    for (int i = 0; i <= 1000; i++) {
        if (numbers.capacity() != capacity) {
            capacity = numbers.capacity();
            cout << "Capacity: " << capacity << endl;
        }

        numbers.push_back(i);
    }
    return 0;
}

int case_2() {
    vector<double> numbers(0);

    cout << "Size: " << numbers.size() << endl;

    int capacity = numbers.capacity();
    cout << "Capacity: " << capacity << endl;

    for (int i = 0; i <= 1000; i++) {
        if (numbers.capacity() != capacity) {
            capacity = numbers.capacity();
            cout << "Capacity: " << capacity << endl;
        }

        numbers.push_back(i);
    }
    return 0;
}

int main() {
    // vector increase its real size based on the number of element in its.
    // vector.size(): the actual number of elements.
    // vector.capacity(): the size of the internal array of the vector has reserved.

    case_1();
    // Size: 5
    // Capacity: 5
    // Capacity: 10
    // Capacity: 20
    // Capacity: 40
    // Capacity: 80
    // Capacity: 160
    // Capacity: 320
    // Capacity: 640
    // Capacity: 1280

    case_2();
    // Size: 0
    // Capacity: 0
    // Capacity: 1
    // Capacity: 2
    // Capacity: 4
    // Capacity: 8
    // Capacity: 16
    // Capacity: 32
    // Capacity: 64
    // Capacity: 128
    // Capacity: 256
    // Capacity: 512
    // Capacity: 1024

    vector<double> numbers(0);

    cout << "Size: " << numbers.size() << endl;

    int capacity = numbers.capacity();
    cout << "Capacity: " << capacity << endl;

    for (int i = 0; i <= 1000; i++) {
        if (numbers.capacity() != capacity) {
            capacity = numbers.capacity();
            cout << "Capacity: " << capacity << endl;
        }

        numbers.push_back(i);
    }

    numbers.resize(100);
    cout << numbers[5] << endl;                         // 5
    cout << "Size: " << numbers.size() << endl;         // Size: 100
    cout << "Capacity: " << numbers.capacity() << endl; // Capacity: 1024

    numbers.reserve(2000);
    cout << numbers[7] << endl;                         // 7
    cout << "Size: " << numbers.size() << endl;         // Size: 100
    cout << "Capacity: " << numbers.capacity() << endl; // Capacity: 2000

    numbers.clear();
    cout << numbers[7] << endl;                         // 7. This should be illegal.
    cout << "Size: " << numbers.size() << endl;         // Size: 0
    cout << "Capacity: " << numbers.capacity() << endl; // Capacity: 2000
}
