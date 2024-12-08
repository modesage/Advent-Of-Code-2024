#include <bits/stdc++.h>
using namespace std;

// Struct to represent a unique point
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int main() {
    ifstream input("input.txt");
    string line;
    vector<string> map;
    while (getline(input, line)) {
        map.push_back(line);
    }
    input.close();

    set<Point> antinodes;

    // Iterate through all pairs of antenna positions
    for (int y1 = 0; y1 < map.size(); y1++) {
        for (int x1 = 0; x1 < map[y1].size(); x1++) {
            char freq1 = map[y1][x1];
            if (freq1 == '.') continue;

            // Iterate through all other antenna positions
            for (int y2 = y1; y2 < map.size(); y2++) {
                for (int x2 = (y2 == y1) ? x1 + 1 : 0; x2 < map[y2].size(); x2++) {
                    if (x1 == x2 && y1 == y2) continue; // Skip the same antenna
                    char freq2 = map[y2][x2];
                    if (freq1 != freq2) continue; // Antennas must have the same frequency

                    // Calculate vector between the two antennas
                    int dx = x2 - x1;
                    int dy = y2 - y1;

                    // Calculate the antinodes on either side of the line segment
                    int ax1 = x1 - dx; // Antinode 1
                    int ay1 = y1 - dy;
                    int ax2 = x2 + dx; // Antinode 2
                    int ay2 = y2 + dy;

                    // Check if the antinodes are within bounds and add to the set
                    if (ax1 >= 0 && ax1 < map[0].size() && ay1 >= 0 && ay1 < map.size()) {
                        antinodes.insert(Point(ax1, ay1));
                    }
                    if (ax2 >= 0 && ax2 < map[0].size() && ay2 >= 0 && ay2 < map.size()) {
                        antinodes.insert(Point(ax2, ay2));
                    }
                }
            }
        }
    }

    // Output the number of unique antinode locations
    cout << antinodes.size() << '\n';

    return 0;
}
