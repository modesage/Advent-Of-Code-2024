#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1000;  

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
        int length = report.size();
        bool isSafe = true;
        bool isIncreasing = (report[1] > report[0]);  
        bool isDecreasing = (report[1] < report[0]);

        for (int i = 1; i < length; i++) {
            if (abs(report[i] - report[i - 1]) < 1 || abs(report[i] - report[i - 1]) > 3) {
                isSafe = false;
                break;
            }

            if (isIncreasing && report[i] < report[i - 1]) {
                isSafe = false;
                break;
            } 
            if (isDecreasing && report[i] > report[i - 1]) {
                isSafe = false;
                break;
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
                isSafe = false;
                break;
            }
        }

        if (isSafe) {
            safeCount++;
        }
    }

    cout << safeCount << '\n';
    return 0;
}
