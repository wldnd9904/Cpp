#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N;
int v[1000], score[201], cnt[201], fifth[201];

int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    cin >> test_case;
    for (int tc = 0; tc < test_case; tc++) {
        for (int i = 1; i <= 200; i++) {
            score[i] = 0;
            cnt[i] = 0;
            fifth[i] = 0;
        }
        cin >> N;
        for (size_t i = 0; i < N; i++) {
            cin >> v[i];
            cnt[v[i]] += 1;
        }

        int scoreCnt = 0;
        for (size_t i = 0; i < N; i++) {
            int x = v[i];
            if (cnt[x] < 6) continue;
            ++scoreCnt;
            cnt[x]++;
            switch (cnt[x]) {
                case 7:
                case 8:
                case 9:
                case 10:
                    score[x] += scoreCnt;
                    break;
                case 11:
                    fifth[x] = scoreCnt;
                    break;
                default:
                    break;
            }
        }
        int win;
        for (int i = 0; i <= 200; i++) {
            if (cnt[i] == 12) {
                win = i;
                break;
            }
        }
        for (int i = win + 1; i <= 200; i++) {
            if (cnt[i] != 12) continue;
            if (score[i] < score[win])
                win = i;
            else if (score[i] == score[win]) {
                if (fifth[i] < fifth[win]) win = i;
            }
        }
        cout << win << '\n';
    }

    return 0;
}