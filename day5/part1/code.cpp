#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputfile("input.txt");

    vector<pair<int, int>> pairs;
    vector<vector<int>> numbers;

    string line;

    while (getline(inputfile, line)) {
        if (line.empty()) break;

        stringstream ss(line);
        string part;
        int num1, num2;

        getline(ss, part, '|');
        num1 = stoi(part);

        getline(ss, part);
        num2 = stoi(part);

        pairs.push_back({num1, num2});
    }

    while (getline(inputfile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string part;
        vector<int> row;

        while (getline(ss, part, ',')) {
            row.push_back(stoi(part));
        }

        numbers.push_back(row);
    }

    inputfile.close();


    int sum = 0;

    for (auto &v : numbers) {
        bool canPass = true;
        
        for (auto &p : pairs) {
            auto it1 = find(v.begin(), v.end(), p.first);
            auto it2 = find(v.begin(), v.end(), p.second);
            
            if (it1 != v.end() && it2 != v.end()) {
                if (it1 > it2) {
                    canPass = false;
                    break;
                }
            }
        }

        if (canPass) {
            int mid_index = v.size() / 2;
            sum += v[mid_index];
        }
    }

    cout << sum << '\n';

    return 0;
}
