#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1000;

bool isSafe(const vector<int>& report) {
    int length = report.size();
    bool isIncreasing = (report[1] > report[0]);
    bool isDecreasing = (report[1] < report[0]);

    for (int i = 1; i < length; i++) {
        if (abs(report[i] - report[i - 1]) < 1 || abs(report[i] - report[i - 1]) > 3) {
            return false;
        }

        if (isIncreasing && report[i] < report[i - 1]) {
            return false;
        } 
        if (isDecreasing && report[i] > report[i - 1]) {
            return false;
        }

        if (report[i] > report[i - 1]) {
            isDecreasing = false;
            isIncreasing = true;
        } 
        if (report[i] < report[i - 1]) {
            isIncreasing = false;
            isDecreasing = true;
        }

        if (report[i] == report[i - 1]) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<vector<int>> v;
    string line;


    for (int i = 0; i < SIZE; i++) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> report;
        int num;
        while (ss >> num) {
            report.push_back(num);
        }
        v.push_back(report);
    }

    int safeCount = 0;

    for (const auto& report : v) {
        if (isSafe(report)) {
            safeCount++;
            continue;
        }

        bool canBeSafe = false;
        for (int i = 0; i < report.size(); i++) {
            vector<int> modifiedReport = report;
            modifiedReport.erase(modifiedReport.begin() + i);  

            if (isSafe(modifiedReport)) {
                canBeSafe = true;
                break;
            }
        }

        if (canBeSafe) {
            safeCount++;
        }
    }

    cout << safeCount << '\n';
    return 0;
}
