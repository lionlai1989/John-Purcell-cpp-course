#include <iostream>
#include <vector>

using namespace std;

int main() {
    // grid is a 2d array with 3 rows and each row has 4 columns. Thus, grid.size() = 3
    // Initialize all elements with 1.
    vector<vector<int>> grid(3, vector<int>(4, 1));

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            cout << grid[row][col] << flush;
        }
        cout << endl;
    }
    // 1111
    // 1111
    // 1111

    grid[1].push_back(2);
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            cout << grid[row][col] << flush;
        }
        cout << endl;
    }
    // 1111
    // 11112
    // 1111

    return 0;
}
