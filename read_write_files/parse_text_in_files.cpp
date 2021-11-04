#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // Write files.
    string output_filename = "text.txt";

    // ofstream or fstream can both be used.
    // ofstream out_file;
    // out_file.open(output_filename);
    fstream out_file;
    out_file.open(output_filename, ios::out);

    if (out_file.is_open()) {
        out_file << "Hello there" << endl;
        out_file << 123 << endl;
        out_file.close();
    } else {
        cout << "Could not create file: " << output_filename << endl;
    }

    // Read files.
    string input_filename = "test.txt";
    ifstream in_file;
    in_file.open(input_filename);

    if (in_file.is_open()) {
        string line;

        // in_file is self-checking itself if it reaches the end of file.
        while (in_file) {
            getline(in_file, line);
            cout << line << endl;
        }
        in_file.close();
    } else {
        cout << "Cannot open file: " << input_filename << endl;
    }

    // Parse files.
    string filename = "stats.txt";
    ifstream input;

    input.open(filename);

    if (!input.is_open()) {
        return 1;
    }

    while (input) {
        string line;
        getline(input, line, ':');

        int population;
        input >> population;
        input >> ws; // ws in c++11 means whatever whitespaces is there.
        // break the while loop when it reaches the 3rd line.
        if (!input) {
            break;
        }

        cout << "'" << line << "'"
             << " -- "
             << "'" << population << "'" << endl;
    }

    input.close();

    return 0;
}
