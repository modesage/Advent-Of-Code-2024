#include <bits/stdc++.h>
using namespace std;

int rows, cols;
vector<vector<int>> heightMap;

int countTrailsFrom(int startRow, int startCol) {
    queue<pair<int, int>> q;
    q.push({startRow, startCol});
    int trailCount = 0;
    set<pair<int, int>> visited;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (visited.count({r, c})) {
            continue;
        }
        visited.insert({r, c});

        if (heightMap[r][c] == 0) {
            trailCount++;
        }

        for (auto [dr, dc] : vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
            int newRow = r + dr;
            int newCol = c + dc;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && heightMap[newRow][newCol] == heightMap[r][c] - 1) {
                q.push({newRow, newCol});
            }
        }
    }

    return trailCount;
}

map<pair<int, int>, int> memo;

int countDistinctTrails(int row, int col) {
    if (heightMap[row][col] == 0) {
        return 1;
    }

    if (memo.count({row, col})) {
        return memo[{row, col}];
    }

    int trailCount = 0;

    for (auto [dr, dc] : vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
        int newRow = row + dr;
        int newCol = col + dc;
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && heightMap[newRow][newCol] == heightMap[row][col] - 1) {
            trailCount += countDistinctTrails(newRow, newCol);
        }
    }

    memo[{row, col}] = trailCount;
    return trailCount;
}

int main(int argc, char* argv[]) {
    ifstream input("input.txt");
    string line;
    vector<string> mapData;
    while (getline(input, line)) {
        mapData.push_back(line);
    }
    input.close();

    rows = mapData.size();
    cols = mapData[0].size();
    heightMap.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            heightMap[i][j] = mapData[i][j] - '0'; // Convert char to int
        }
    }

    int totalPart1 = 0, totalPart2 = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (heightMap[r][c] == 9) {
                totalPart1 += countTrailsFrom(r, c);
                totalPart2 += countDistinctTrails(r, c);
            }
        }
    }

    cout << totalPart1 << endl;
    cout << totalPart2 << endl;

    return 0;
}
