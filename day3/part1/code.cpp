#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inputFile("input.txt");

    string input;
    string line;
    
    while (getline(inputFile, line)) {
        input += line;
    }
    inputFile.close();
    
    // regex pattern to match 'mul(x, y)' where x and y are 1 to 3 digit numbers.
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    
    // create an iterator to search for matches of the regular expression in the 'input' string.
    // 'begin' points to the first match in the string.
    auto begin = sregex_iterator(input.begin(), input.end(), pattern);
    
    // 'end' points to one past the last match.
    // this helps mark the end of the range for matching.
    auto end = sregex_iterator();
    
    long long totalSum = 0;
    
    // iterate through all matches found by the regex iterator.
    // the iterator 'it' will point to each match as we loop through.
    for (auto it = begin; it != end; ++it) {
        // 'match' stores the details of the current match found by the iterator.
        // 'it' is dereferenced to access the match information.
        smatch match = *it;
        
        // extract the first captured group (the first number 'x') from the match.
        int x = stoi(match[1].str());

        // extract the second captured group (the second number 'y') from the match.
        int y = stoi(match[2].str());
        
        // casting the product to a 'long long' using c++ cast operator explicitly to ensure there is no overflow.
        totalSum += static_cast<long long>(x) * y;
    }
    
    cout << totalSum << endl;
    
    return 0; 
}
