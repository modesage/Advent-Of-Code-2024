#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<string> v;
    ifstream infile("input.txt");
    string line;
    while(getline(infile,line)){
        v.push_back(line);
    }

    int length_v = v.size();
    int length_pathline = v[0].size();
    
    bool up = true;
    bool right = false;
    bool down = false;
    bool left = false;

    bool dontExit = true;

    int distinct_pos = 0;

    map<pair<int, int>, int> mpp;

    for(int i = 0; dontExit && i < length_v; i++){
        for(int j = 0; dontExit && j < length_pathline; j++){
            if(v[i][j] == '^'){
                mpp[{i,j}] = 1;
                distinct_pos++;
                while(true){
                    if(up && i == 0 || right && j == length_pathline - 1 || down && i == length_pathline - 1 || left && j == 0){
                        dontExit = false;
                        break;
                    }
                    else if(i > 0 && up && v[i - 1][j] != '#'){
                        i--;
                        if(mpp[{i,j}] == 0){
                            distinct_pos++;
                            mpp[{i,j}] = 1;
                        }
                    }
                    else if(i > 0 && up && v[i - 1][j] == '#'){
                        up = false;
                        right = true;
                    }
                    else if(j < length_pathline - 1 && right && v[i][j + 1] != '#'){
                        j++;
                        if(mpp[{i,j}] == 0){
                            distinct_pos++;
                            mpp[{i,j}] = 1;
                        }
                    }
                    else if(j < length_pathline - 1 && right && v[i][j + 1] == '#'){
                        right = false;
                        down = true;
                    }
                    else if(i < length_pathline - 1 && down && v[i + 1][j] != '#'){
                        i++;
                        if(mpp[{i,j}] == 0){
                            distinct_pos++;
                            mpp[{i,j}] = 1;
                        }
                    }
                    else if(i < length_pathline - 1 && down && v[i + 1][j] == '#'){
                        down = false;
                        left = true;
                    }
                    else if(j > 0 && left && v[i][j - 1] != '#'){
                        j--;
                        if(mpp[{i,j}] == 0){
                            distinct_pos++;
                            mpp[{i,j}] = 1;
                        }
                    }
                    else if(j > 0 && left && v[i][j - 1] == '#'){
                        left = false;
                        up = true;
                    }
                }
            }
        }        
    }

    cout << distinct_pos;

    return 0;
}
