#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string presets1[15] = {"0",  "0",  "1",  "7",  "4",  "2",  "6", "8",
                       "10", "18", "22", "20", "28", "68", "88"};
string presets2[8] = {"108", "188", "200", "208", "288", "688", "888"};

string matchMin(int n) {
    if (n < 15) return presets1[n];
    int digits = n / 7 + (n % 7 > 0);  // 자리수
    string s = "";
    s += (presets2[(n - 15) % 7]);
    digits -= 3;
    while (digits--) s += '8';
    return s;
}

string matchMax(int n) {
    string s = "";
    if (n & 1) {
        s += '7';
        n -= 3;
    }
    while (n >= 2) {
        s += '1';
        n -= 2;
    }
    return s;
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << matchMin(n) << " " << matchMax(n) << '\n';
    }
    return 0;
}