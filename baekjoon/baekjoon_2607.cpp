
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int ret = 0;

    int N;
    cin >> N;
    string first;
    cin >> first;
    vector<int> firstChars(26, 0);
    for (char c : first) firstChars[c - 'A']++;

    for (int i = 0; i < N - 1; i++) {
        string s;
        cin >> s;
        vector<int> chars(26, 0);

        // 기저) 길이 차이 두개 이상 나면 안 됨
        if (abs((int)(first.size() - s.size())) > 1) continue;

        // 같은 구성 체크
        for (char c : s) chars[c - 'A']++;
        bool minusOne = false, plusOne = false;
        for (int i = 0; i < 26; i++) {
            if (firstChars[i] != chars[i]) {
                if (firstChars[i] - chars[i] == 1) {
                    if (plusOne) break;
                    plusOne = true;
                } else if (firstChars[i] - chars[i] == -1) {
                    if (minusOne) break;
                    minusOne = true;
                } else
                    break;
            }
            if (i == 25) ret++;
        }
    }

    cout << ret;
    return 0;
}