#include <bits/stdc++.h>
using namespace std;

bool evaluate(vector<long long>& numbers, long long targetValue, size_t currentIndex, long long currentResult) {
    if (currentIndex == numbers.size()) {
        return currentResult == targetValue;
    }
    if (evaluate(numbers, targetValue, currentIndex + 1, currentResult + numbers[currentIndex])) return true;
    if (evaluate(numbers, targetValue, currentIndex + 1, currentResult * numbers[currentIndex])) return true;
    return false;
}

int main() {
    ifstream inputFile("input.txt");
    long long targetValue;
    vector<long long> targetValues;   
    vector<vector<long long>> numberLists;  

    while (inputFile >> targetValue) {
        inputFile.ignore(1, ':');  
        vector<long long> numbers;
        long long number;
        
        while (inputFile >> number) {
            numbers.push_back(number);
            if (inputFile.peek() == '\n' || inputFile.eof()) break;
        }
        targetValues.push_back(targetValue);
        numberLists.push_back(numbers);
    }
    inputFile.close();

    long long totalCalibrationSum = 0;

    for (size_t i = 0; i < targetValues.size(); ++i) {
        long long targetValue = targetValues[i];
        vector<long long>& numbers = numberLists[i];

        if (evaluate(numbers, targetValue, 1, numbers[0])) {
            totalCalibrationSum += targetValue;
        }
    }
    cout << totalCalibrationSum << endl;

    return 0;
}
