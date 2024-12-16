#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

vector<int> parseNumbers(const string &s) {
    regex re("-?\\d+");
    sregex_iterator begin(s.begin(), s.end(), re), end;
    vector<int> nums;
    for (auto it = begin; it != end; ++it) {
        nums.push_back(stoi(it->str()));
    }
    return nums;
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<string> grid;

    while (getline(input, line)) {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    int startRow, startCol, endRow, endCol;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 'S') {
                startRow = r;
                startCol = c;
            }
            if (grid[r][c] == 'E') {
                endRow = r;
                endCol = c;
            }
        }
    }

    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;
    set<tuple<int, int, int>> visited;
    map<tuple<int, int, int>, int> distance;
    int bestScore = -1;

    pq.emplace(0, startRow, startCol, 1);

    while (!pq.empty()) {
        auto [dist, r, c, dir] = pq.top();
        pq.pop();

        if (distance.find({r, c, dir}) == distance.end()) {
            distance[{r, c, dir}] = dist;
        }

        if (r == endRow && c == endCol && bestScore == -1) {
            bestScore = dist;
        }

        if (visited.count({r, c, dir})) continue;
        visited.insert({r, c, dir});

        int dRow = DIRECTIONS[dir].first;
        int dCol = DIRECTIONS[dir].second;
        int newRow = r + dRow, newCol = c + dCol;

        if (0 <= newCol && newCol < cols && 0 <= newRow && newRow < rows && grid[newRow][newCol] != '#') {
            pq.emplace(dist + 1, newRow, newCol, dir);
        }

        pq.emplace(dist + 1000, r, c, (dir + 1) % 4);
        pq.emplace(dist + 1000, r, c, (dir + 3) % 4);
    }

    cout << bestScore << endl;

    pq = priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>>(); 
    visited.clear();
    map<tuple<int, int, int>, int> distance2;

    for (int dir = 0; dir < 4; ++dir) {
        pq.emplace(0, endRow, endCol, dir);
    }

    while (!pq.empty()) {
        auto [dist, r, c, dir] = pq.top();
        pq.pop();

        if (distance2.find({r, c, dir}) == distance2.end()) {
            distance2[{r, c, dir}] = dist;
        }

        if (visited.count({r, c, dir})) continue;
        visited.insert({r, c, dir});

        int dRow = DIRECTIONS[(dir + 2) % 4].first;
        int dCol = DIRECTIONS[(dir + 2) % 4].second;
        int newRow = r + dRow, newCol = c + dCol;

        if (0 <= newCol && newCol < cols && 0 <= newRow && newRow < rows && grid[newRow][newCol] != '#') {
            pq.emplace(dist + 1, newRow, newCol, dir);
        }

        pq.emplace(dist + 1000, r, c, (dir + 1) % 4);
        pq.emplace(dist + 1000, r, c, (dir + 3) % 4);
    }

    set<pair<int, int>> validTiles;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (int dir = 0; dir < 4; ++dir) {
                if (distance.find({r, c, dir}) != distance.end() && 
                    distance2.find({r, c, dir}) != distance2.end() && 
                    distance[{r, c, dir}] + distance2[{r, c, dir}] == bestScore) {
                    validTiles.insert({r, c});
                }
            }
        }
    }

    cout << validTiles.size() << endl;

    return 0;
}
