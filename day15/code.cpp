#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

vector<int> extractInts(const string& s) {
    vector<int> result;
    regex re("-?\\d+");
    auto begin = sregex_iterator(s.begin(), s.end(), re);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        result.push_back(stoi(it->str()));
    }
    return result;
}

int simulateMovement(vector<string> grid, const string& instructions, bool expanded) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (expanded) {
        vector<vector<char>> expandedGrid;
        for (int r = 0; r < rows; ++r) {
            vector<char> newRow;
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '#') {
                    newRow.push_back('#');
                    newRow.push_back('#');
                } else if (grid[r][c] == 'O') {
                    newRow.push_back('[');
                    newRow.push_back(']');
                } else if (grid[r][c] == '.') {
                    newRow.push_back('.');
                    newRow.push_back('.');
                } else if (grid[r][c] == '@') {
                    newRow.push_back('@');
                    newRow.push_back('.');
                }
            }
            expandedGrid.push_back(newRow);
        }
        grid = vector<string>(expandedGrid.size());
        for (int i = 0; i < expandedGrid.size(); ++i) {
            grid[i] = string(expandedGrid[i].begin(), expandedGrid[i].end());
        }
        cols *= 2;
    }

    int robotRow = 0, robotCol = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '@') {
                robotRow = r;
                robotCol = c;
                grid[r][c] = '.';
            }
        }
    }

    int row = robotRow, col = robotCol;
    for (char move : instructions) {
        if (move == '\n') continue;

        pair<int, int> direction;
        if (move == '^') direction = {-1, 0};
        else if (move == '>') direction = {0, 1};
        else if (move == 'v') direction = {1, 0};
        else if (move == '<') direction = {0, -1};

        int newRow = row + direction.first;
        int newCol = col + direction.second;
        
        if (grid[newRow][newCol] == '#') continue;
        else if (grid[newRow][newCol] == '.') {
            row = newRow;
            col = newCol;
        } else if (grid[newRow][newCol] == '[' || grid[newRow][newCol] == ']' || grid[newRow][newCol] == 'O') {
            deque<pair<int, int>> queue;
            set<pair<int, int>> visited;
            bool canMove = true;
            queue.push_back({row, col});

            while (!queue.empty()) {
                auto [currRow, currCol] = queue.front();
                queue.pop_front();

                if (visited.count({currRow, currCol})) continue;
                visited.insert({currRow, currCol});

                int nextRow = currRow + direction.first;
                int nextCol = currCol + direction.second;

                if (grid[nextRow][nextCol] == '#') {
                    canMove = false;
                    break;
                }
                if (grid[nextRow][nextCol] == 'O') queue.push_back({nextRow, nextCol});
                if (grid[nextRow][nextCol] == '[') {
                    queue.push_back({nextRow, nextCol});
                    assert(grid[nextRow][nextCol + 1] == ']');
                    queue.push_back({nextRow, nextCol + 1});
                }
                if (grid[nextRow][nextCol] == ']') {
                    queue.push_back({nextRow, nextCol});
                    assert(grid[nextRow][nextCol - 1] == '[');
                    queue.push_back({nextRow, nextCol - 1});
                }
            }

            if (!canMove) continue;

            while (!visited.empty()) {
                for (auto it = visited.begin(); it != visited.end(); ) {
                    auto [currRow, currCol] = *it;
                    int nextRow = currRow + direction.first;
                    int nextCol = currCol + direction.second;

                    if (!visited.count({nextRow, nextCol})) {
                        assert(grid[nextRow][nextCol] == '.');
                        grid[nextRow][nextCol] = grid[currRow][currCol];
                        grid[currRow][currCol] = '.';
                        it = visited.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

            row += direction.first;
            col += direction.second;
        }
    }

    int totalGPS = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '[' || grid[r][c] == 'O') {
                totalGPS += 100 * r + c;
            }
        }
    }

    return totalGPS;
}

int main() {
    ifstream input("input.txt");
    string data((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    size_t pos = data.find("\n\n");
    string gridPart = data.substr(0, pos);
    string instructions = data.substr(pos + 2);

    vector<string> grid;
    stringstream ss(gridPart);
    string line;
    while (getline(ss, line)) {
        grid.push_back(line);
    }

    cout << simulateMovement(grid, instructions, false) << endl;
    cout << simulateMovement(grid, instructions, true) << endl;

    return 0;
}
