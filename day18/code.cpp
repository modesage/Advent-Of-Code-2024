#include <bits/stdc++.h>
using namespace std;

const int GRID_SIZE = 71;
const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left directions

// Function to parse input and return coordinates
vector<pair<int, int>> parseInput(const string &filename) {
    ifstream file(filename);
    string line;
    vector<pair<int, int>> coordinates;

    while (getline(file, line)) {
        istringstream ss(line);
        int x, y;
        char comma;
        ss >> x >> comma >> y;
        coordinates.emplace_back(x, y);
    }

    return coordinates;
}

// Function to check if a position is valid
bool isValid(int x, int y, const vector<vector<char>> &grid) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[y][x] != '#';
}

// BFS to find shortest path
int bfs(const vector<vector<char>> &grid) {
    queue<tuple<int, int, int>> q; // {distance, row, col}
    vector<vector<bool>> visited(GRID_SIZE, vector<bool>(GRID_SIZE, false));

    q.emplace(0, 0, 0);
    visited[0][0] = true;

    while (!q.empty()) {
        auto [dist, row, col] = q.front();
        q.pop();

        if (row == GRID_SIZE - 1 && col == GRID_SIZE - 1) {
            return dist;
        }

        for (const auto &[dr, dc] : DIRECTIONS) {
            int newRow = row + dr;
            int newCol = col + dc;

            if (isValid(newCol, newRow, grid) && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                q.emplace(dist + 1, newRow, newCol);
            }
        }
    }

    return -1; // Path not found
}

// Check if path is blocked
bool isPathBlocked(const vector<vector<char>> &grid) {
    return bfs(grid) == -1;
}

int main() {
    vector<pair<int, int>> bytes = parseInput("input.txt");
    vector<vector<char>> grid(GRID_SIZE, vector<char>(GRID_SIZE, '.'));

    for (size_t idx = 0; idx < bytes.size(); ++idx) {
        int x = bytes[idx].first;
        int y = bytes[idx].second;

        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
            grid[y][x] = '#';
        }

        if (idx == 1023) {
            int steps = bfs(grid);
            if (steps != -1) {
                cout << "Minimum steps: " << steps << endl;
            } else {
                cout << "No path found." << endl;
            }
        }

        if (isPathBlocked(grid)) {
            cout << "First byte blocking path: " << x << "," << y << endl;
            break;
        }
    }

    return 0;
}
