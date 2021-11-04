#include <fstream>
#include <iostream>

using namespace std;

#pragma pack(push, 1) // Turn on packing.
struct Person {
    // It uses
    // char name[50], instead of
    // "string name", because the object of the string class contains a pointer. When using a string
    // object to store some text, that text is not stored directly in the variable here. When we
    // declare a variable in c/c++, it is stored on an area of memory, known as stack, which is used
    // to store local variable and function calls. string class does not know how much/long memory
    // you need to store some text. string class has a pointer inside it and it uses New to allocate
    // some memory on the heap. Thus, "string name" cannot be used here, because it does not store
    // the actual text but pointer.

    // In theory, the size of it is 62 bytes. BUT, c/c++ actually pads struct to make struct more
    // efficient to tranfer to/from memory. E.g., sizeof(Person) == 64. Hence, we need to turn off
    // padding to write this struct to a file. We can use a preprocessor directive "pragma" here.
    char name[50]; // 50 bytes
    int age;       // 4 bytes
    double height; // 8 bytes
};
#pragma pack(pop) // Turn off packing. Make packing only effective in struct.

int main() {
    // Write struct to binary file.
    string filename = "test.bin";
    ofstream output_file;
    output_file.open(filename, ios::binary);
    // fstream io_file;
    // io_file.open(filename, ios::binary | ios::out); // Use ios::out due to fstream.

    Person someone = {"Frodo", 220, 0.8};

    if (output_file.is_open()) {
        // Get the address of someone and convert to char pointer which write() expects.
        output_file.write(reinterpret_cast<char *>(&someone), sizeof(Person)); // Better way?
        // output_file.write((char *)&someone, sizeof(Person)); // Old way used in c.

        output_file.close();
    } else {
        cout << "Could not create file " + filename << endl;
    }

    // Read binary file.
    Person someone_else = {};
    ifstream input_file;
    input_file.open(filename, ios::binary);
    if (input_file.is_open()) {
        input_file.read(reinterpret_cast<char *>(&someone_else), sizeof(Person));
        input_file.close();
    } else {
        cout << "Could not read file " + filename << endl;
    }

    cout << someone_else.name << ", " << someone_else.age << ", " << someone_else.height << endl;
    return 0;
}
