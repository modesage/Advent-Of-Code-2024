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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(input[i][j] == 'X'){
                //diagonal up left
                if(i-3 >= 0 && j-3 >= 0 && input[i-3][j-3] == 'S' && input[i-2][j-2] == 'A' && input[i-1][j-1] == 'M') count++;
                //diagonal up right
                if(i-3 >= 0 && j+3 < cols && input[i-3][j+3] == 'S' && input[i-2][j+2] == 'A' && input[i-1][j+1] == 'M') count++;
                //diagonal down left
                if(i+3 < rows && j-3 >= 0 && input[i+3][j-3] == 'S' && input[i+2][j-2] == 'A' && input[i+1][j-1] == 'M') count++;
                //diagonal down right
                if(i+3 < rows && j+3 < cols && input[i+3][j+3] == 'S' && input[i+2][j+2] == 'A' && input[i+1][j+1] == 'M') count++;
                //horizontal left
                if(j-3 >= 0 && input[i][j-3] == 'S' && input[i][j-2] == 'A' && input[i][j-1] == 'M') count++;
                //horizontal right
                if(j+3 < cols && input[i][j+3] == 'S' && input[i][j+2] == 'A' && input[i][j+1] == 'M') count++;
                //vertical up
                if(i-3 >= 0 && input[i-3][j] == 'S' && input[i-2][j] == 'A' && input[i-1][j] == 'M') count++;
                //vertical down
                if(i+3 < cols && input[i+3][j] == 'S' && input[i+2][j] == 'A' && input[i+1][j] == 'M') count++;
            }
        }
    }
    cout << count << '\n';

    return 0;
}
