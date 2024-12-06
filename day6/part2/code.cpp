#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> grid;
    ifstream infile("input.txt");
    string line;
    while(getline(infile,line)){
        grid.push_back(line);
    }

    int numRows = grid.size();
    int numCols = grid[0].size();

    int startRow = -1, startCol = -1;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col] == '^') {
                startRow = row;
                startCol = col;
                break;
            }
        }
        if (startRow != -1) break;
    }

    // Define movement directions: up, right, down, left
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    int obstructionCount = 0; // Counter for valid obstruction positions

    // Iterate over all grid cells as potential obstruction positions
    for (int originRow = 0; originRow < numRows; originRow++) {
        for (int originCol = 0; originCol < numCols; originCol++) {
            int currentRow = startRow, currentCol = startCol;
            int directionIndex = 0; // 0=up, 1=right, 2=down, 3=left

            set<tuple<int, int, int>> visitedStates; // Track visited states (row, col, direction)
            set<pair<int, int>> visitedPositions;   // Track visited positions (row, col)

            // Simulate the guard's movement
            while (true) {
                // Check if the current state has already been visited
                if (visitedStates.find({currentRow, currentCol, directionIndex}) != visitedStates.end()) {
                    obstructionCount++;
                    break;
                }

                // Mark the current state and position as visited
                visitedStates.insert({currentRow, currentCol, directionIndex});
                visitedPositions.insert({currentRow, currentCol});

                // Calculate the next position
                int deltaRow = directions[directionIndex].first;
                int deltaCol = directions[directionIndex].second;
                int nextRow = currentRow + deltaRow;
                int nextCol = currentCol + deltaCol;

                // Check if the next position is out of bounds
                if (nextRow < 0 || nextRow >= numRows || nextCol < 0 || nextCol >= numCols) {
                    break; // Stop simulation if out of bounds
                }

                // Check if the next position is an obstacle or loops back to the origin
                if (grid[nextRow][nextCol] == '#' || (nextRow == originRow && nextCol == originCol)) {
                    directionIndex = (directionIndex + 1) % 4; // Turn right
                } else {
                    // Move to the next position
                    currentRow = nextRow;
                    currentCol = nextCol;
                }
            }
        }
    }

    cout << obstructionCount;

    return 0;
}
