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
    sort(list_1.begin(), list_1.end());
    sort(list_2.begin(), list_2.end());
    long long sum = 0;
    for(int i = 0; i < INPUT_SIZE; i++){
        sum += abs(list_1[i] - list_2[i]);
    }
    cout << sum << "\n";
    return 0;
}