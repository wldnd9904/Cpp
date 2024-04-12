#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, K;
vector<string> stringv;
vector<vector<bool>> boolv;
vector<int> eof26;


void solve(int left){
    
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        stringv.push_back(tmp);
    }
    int base = 1;
    for (int i = 0; i <= 50; i++) {
        eof26.push_back(base);
        base *= 26;
        base %= 1000003;
    }
    return 0;
}