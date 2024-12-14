#include <bits/stdc++.h>
using namespace std;

const int GRID_WIDTH = 101;
const int GRID_HEIGHT = 103;
const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

tuple<int, int, int, int> parseLine(const string &line)
{
    stringstream ss(line);
    vector<int> values;
    string temp;
    size_t start = 0;
    while ((start = line.find_first_of("-0123456789", start)) != string::npos)
    {
        size_t end = line.find_first_not_of("-0123456789", start);
        values.push_back(stoi(line.substr(start, end - start)));
        start = end;
    }
    return {values[0], values[1], values[2], values[3]};
}

int main()
{
    ifstream inputFile("input.txt");
    string line;

    vector<tuple<int, int, int, int>> robots;
    while (getline(inputFile, line))
    {
        auto [px, py, vx, vy] = parseLine(line);
        robots.emplace_back(px, py, vx, vy);
    }

    int quadrant1Count = 0, quadrant2Count = 0, quadrant3Count = 0, quadrant4Count = 0;
    vector<vector<char>> grid(GRID_HEIGHT, vector<char>(GRID_WIDTH, '.'));

    for (int time = 1; time < 1'000'000; ++time)
    {
        for (auto &robot : robots)
        {
            auto &[px, py, vx, vy] = robot;
            px = (px + vx + GRID_WIDTH) % GRID_WIDTH;
            py = (py + vy + GRID_HEIGHT) % GRID_HEIGHT;
            grid[py][px] = '#';
        }

        if (time == 100)
        {
            quadrant1Count = quadrant2Count = quadrant3Count = quadrant4Count = 0;
            int midX = GRID_WIDTH / 2;
            int midY = GRID_HEIGHT / 2;

            for (const auto &robot : robots)
            {
                auto [px, py, vx, vy] = robot;
                if (px < midX && py < midY)
                    ++quadrant1Count;
                else if (px >= midX && py < midY)
                    ++quadrant2Count;
                else if (px < midX && py >= midY)
                    ++quadrant3Count;
                else if (px >= midX && py >= midY)
                    ++quadrant4Count;
            }

            cout << "Safety Factor: " << quadrant1Count * quadrant2Count * quadrant3Count * quadrant4Count << endl;
        }

        set<pair<int, int>> visited;
        int components = 0;

        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            for (int x = 0; x < GRID_WIDTH; ++x)
            {
                if (grid[y][x] == '#' && visited.find({x, y}) == visited.end())
                {
                    ++components;
                    deque<pair<int, int>> queue;
                    queue.push_back({x, y});

                    while (!queue.empty())
                    {
                        auto [cx, cy] = queue.front();
                        queue.pop_front();

                        if (visited.find({cx, cy}) != visited.end())
                            continue;
                        visited.insert({cx, cy});

                        for (const auto &[dx, dy] : DIRECTIONS)
                        {
                            int nx = (cx + dx + GRID_WIDTH) % GRID_WIDTH;
                            int ny = (cy + dy + GRID_HEIGHT) % GRID_HEIGHT;
                            if (grid[ny][nx] == '#' && visited.find({nx, ny}) == visited.end())
                            {
                                queue.push_back({nx, ny});
                            }
                        }
                    }
                }
            }
        }

        if (components <= 200)
        {
            cout << "Time: " << time << endl;
            break;
        }

        for (auto &row : grid)
            fill(row.begin(), row.end(), '.');
    }

    return 0;
}
