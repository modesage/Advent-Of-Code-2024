#include <bits/stdc++.h>
using namespace std;

// Directions for up, right, down, left (used to explore neighbors)
const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main() {
    // Open the input file and read the grid
    ifstream inputFile("input.txt");
    string line;
    vector<string> grid;

    // Reading the grid from the input file into the vector
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }

    int rows = grid.size();  // Number of rows in the grid
    int cols = grid[0].size();  // Number of columns in the grid

    set<pair<int, int>> visited;  // Set to track visited cells
    long long totalPrice1 = 0, totalPrice2 = 0;  // Variables to store the total price for both methods

    // Loop through each cell of the grid
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {

            // Skip the cell if it has already been visited
            if (visited.count({r, c})) {
                continue;
            }

            // Initialize a queue for BFS traversal of a region
            queue<pair<int, int>> q;
            q.push({r, c});
            long long area = 0;  // Variable to store the area of the current region
            long long perimeter = 0;  // Variable to store the perimeter of the current region
            map<pair<int, int>, set<pair<int, int>>> perimeterPoints;  // Store points contributing to the perimeter

            // Perform a BFS to explore the current region and calculate area and perimeter
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                // Skip if the cell has already been visited
                if (visited.count({x, y})) {
                    continue;
                }

                // Mark the cell as visited and increase the area
                visited.insert({x, y});
                area++;

                // Check the four neighboring cells (up, right, down, left)
                for (auto [dx, dy] : DIRECTIONS) {
                    int nx = x + dx;  // Neighbor's x-coordinate
                    int ny = y + dy;  // Neighbor's y-coordinate

                    // If the neighbor is within bounds and belongs to the same region, add it to the queue
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == grid[x][y]) {
                        q.push({nx, ny});
                    } else {
                        // If it's out of bounds or belongs to a different region, it's part of the perimeter
                        perimeter++;
                        // Record the perimeter point (neighbor's direction)
                        if (!perimeterPoints.count({dx, dy})) {
                            perimeterPoints[{dx, dy}] = {};
                        }
                        perimeterPoints[{dx, dy}].insert({x, y});
                    }
                }
            }

            // Variable to store the number of unique sides of the region
            long long sides = 0;

            // For each direction (from perimeterPoints), count the unique sides
            for (auto &[direction, points] : perimeterPoints) {
                set<pair<int, int>> visitedPerimeter;  // Set to track visited perimeter cells
                long long prevSides = sides;  // Keep track of previous side count

                // For each point in the perimeter set, explore it and count the sides
                for (auto [px, py] : points) {
                    // Skip if the perimeter point has already been processed
                    if (visitedPerimeter.count({px, py})) {
                        continue;
                    }

                    sides++;  // Increment side count for this perimeter point
                    queue<pair<int, int>> q;
                    q.push({px, py});

                    // Perform BFS to explore the perimeter region
                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        // Skip if the perimeter point has already been visited
                        if (visitedPerimeter.count({x, y})) {
                            continue;
                        }

                        visitedPerimeter.insert({x, y});

                        // Explore neighboring points in the perimeter set
                        for (auto [dx, dy] : DIRECTIONS) {
                            int nx = x + dx;
                            int ny = y + dy;

                            if (points.count({nx, ny})) {
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }

            // Calculate the price for this region using perimeter (totalPrice1)
            totalPrice1 += area * perimeter;

            // Calculate the price for this region using number of sides (totalPrice2)
            totalPrice2 += area * sides;
        }
    }

    // Output the total prices calculated by both methods
    cout << totalPrice1 << endl;  // Output price using area and perimeter
    cout << totalPrice2 << endl;  // Output price using area and number of sides

    return 0;
}
