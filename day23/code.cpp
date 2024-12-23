#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("input.txt");
    string line;

    unordered_map<string, unordered_set<string>> connections;

    while (getline(file, line)) {
        size_t dashPos = line.find('-');
        string computer1 = line.substr(0, dashPos);
        string computer2 = line.substr(dashPos + 1);
        connections[computer1].insert(computer2);
        connections[computer2].insert(computer1);
    }

    vector<string> computers;
    for (const auto &entry : connections) {
        computers.push_back(entry.first);
    }
    sort(computers.begin(), computers.end());

    int p1_count = 0;

    for (size_t i = 0; i < computers.size(); ++i) {
        const string &comp1 = computers[i];
        if (connections[comp1].size() < 2) continue; 
        for (size_t j = i + 1; j < computers.size(); ++j) {
            const string &comp2 = computers[j];
            if (!connections[comp1].count(comp2)) continue; 
            for (size_t k = j + 1; k < computers.size(); ++k) {
                const string &comp3 = computers[k];
                if (connections[comp1].count(comp3) && connections[comp2].count(comp3)) {
                    if (comp1[0] == 't' || comp2[0] == 't' || comp3[0] == 't') {
                        ++p1_count;
                    }
                }
            }
        }
    }
    cout << p1_count << endl;

    vector<string> largest_clique;
    vector<string> current_clique;
    vector<string> candidates;

    function<void(size_t)> findClique = [&](size_t idx) {
        if (idx == computers.size()) {
            if (current_clique.size() > largest_clique.size()) {
                largest_clique = current_clique;
            }
            return;
        }

        const string &comp = computers[idx];
        bool canAdd = true;
        for (const string &other : current_clique) {
            if (!connections[comp].count(other)) {
                canAdd = false;
                break;
            }
        }

        if (canAdd) {
            current_clique.push_back(comp);
            findClique(idx + 1);
            current_clique.pop_back();
        }
        findClique(idx + 1);
    };

    findClique(0);

    sort(largest_clique.begin(), largest_clique.end());
    for (size_t i = 0; i < largest_clique.size(); ++i) {
        if (i > 0) cout << ",";
        cout << largest_clique[i];
    }
    cout << endl;

    return 0;
}
