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
    
    // regex pattern to match "do()" or "don't()" or "mul(x, y)" where x and y are 1 to 3 digit numbers.
    regex pattern(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");

    auto begin = sregex_iterator(input.begin(), input.end(), pattern);
    auto end = sregex_iterator();
    
    long long totalSum = 0;
    bool isEnabled = true;
    
    for (auto it = begin; it != end; ++it) {
        smatch match = *it;

        //match[0] will be don't() or do() or mul(x,y)
        //match[1] will be x
        //match[2] will be y
        
        if(match[0].str() == "don't()"){
            isEnabled = false;
        }
        else if(match[0].str() == "do()"){
            isEnabled = true;
        }
        else if(isEnabled){
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());
            totalSum += static_cast<long long>(x) * y; 
        }
    }
    
    cout << totalSum << endl;
    
    return 0; 
}
