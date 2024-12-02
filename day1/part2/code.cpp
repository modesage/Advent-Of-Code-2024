#include<bits/stdc++.h>
using namespace std;

const int INPUT_SIZE = 1000;

int main(){
    vector<int> list_1, list_2;
    for(int i = 0; i < INPUT_SIZE; i++){
        int x, y;
        cin >> x >> y;
        list_1.push_back(x);
        list_2.push_back(y);
    }
    map<int,int> freq_list;
    for(int i : list_2){
        freq_list[i]++;
    }
    long long score = 0;
    for(int i: list_1){
        score += (long long) i * freq_list[i];
    }
    cout << score << '\n';
    return 0;
}