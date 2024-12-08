#include <bits/stdc++.h>
using namespace std;

// Struct to represent a unique point
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    
    // Overload operator< to allow for Point to be inserted in a set
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

bool isInLine(Point p1, Point p2, Point p) {
    // Check if points p1, p2, p are collinear by checking cross product
    return (p2.y - p1.y) * (p.x - p1.x) == (p2.x - p1.x) * (p.y - p1.y);
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<string> map;
    while (getline(input, line)) {
        map.push_back(line);
    }
    input.close();

    // Store positions of antennas, grouped by frequency
    unordered_map<char, vector<Point>> antennas;

    // Parse the map and collect antenna positions
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x] != '.') {
                antennas[map[y][x]].emplace_back(x, y);
            }
        }
    }

    set<Point> antinodes;

    // Process each frequency group
    for (const auto& [freq, points] : antennas) {
        int n = points.size();
        // For each pair of antennas, find all points in line with them
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Point p1 = points[i], p2 = points[j];
                // Mark every point in line between p1 and p2
                for (int y = 0; y < map.size(); y++) {
                    for (int x = 0; x < map[y].size(); x++) {
                        Point p(x, y);
                        if (isInLine(p1, p2, p)) {
                            antinodes.insert(p);
                        }
                    }
                }
            }
        }
    }

    // Output the number of unique antinodes
    cout << antinodes.size() << '\n';

    return 0;
}
