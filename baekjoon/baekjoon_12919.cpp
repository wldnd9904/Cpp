#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

string S, T;

bool solved = false;

void solve(string str) {
    if (str == S) solved = true;
    if (solved) return;
    if (str.length() == 1) return;
    if (str[0] == 'B') {
        string tmp = str.substr(1, str.length() - 1);
        reverse(tmp.begin(), tmp.end());
        solve(tmp);
    }
    if (solved) return;
    if (str[str.length() - 1] == 'A') {
        string tmp = string(str);
        tmp.erase(tmp.length() - 1);
        solve(tmp);
    }
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> S >> T;
    solve(T);
    cout << (solved ? 1 : 0) << '\n';

    return 0;
}
