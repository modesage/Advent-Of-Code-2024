#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream infile("input.txt");
    string line;
    vector<string> input;

    while(getline(infile, line)){
        input.push_back(line);
    }

    int rows = input.size();  
    int cols = input[0].size(); 

    int count = 0;
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){

            // Only check for patterns if we have enough space in the grid to check diagonals and other patterns
            if(i + 2 < rows && j + 2 < cols){
                // Check for the first diagonal pattern (M -> A -> S in diagonal down-right)
                if(input[i][j] == 'M' && input[i + 1][j + 1] == 'A' && input[i + 2][j + 2] == 'S'){
                    // Check for the corresponding "MAS" pattern on the opposite diagonal
                    if(input[i + 2][j] == 'M' && input[i][j + 2] == 'S'){  // diagonal down-left
                        count++;  // Pattern found, increment count
                    }
                    if(input[i + 2][j] == 'S' && input[i][j + 2] == 'M'){  // diagonal up-left
                        count++;  // Pattern found, increment count
                    }
                }

                // Check for the second diagonal pattern (S -> A -> M in diagonal down-right)
                if(input[i][j] == 'S' && input[i + 1][j + 1] == 'A' && input[i + 2][j + 2] == 'M'){
                    // Check for the corresponding "MAS" pattern on the opposite diagonal
                    if(input[i + 2][j] == 'M' && input[i][j + 2] == 'S'){  // diagonal down-left
                        count++;  // Pattern found, increment count
                    }
                    if(input[i + 2][j] == 'S' && input[i][j + 2] == 'M'){  // diagonal up-left
                        count++;  // Pattern found, increment count
                    }
                }
            }
        }
    }

    cout << count << '\n';

    return 0;
}
