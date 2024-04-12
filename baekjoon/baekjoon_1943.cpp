#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int N, sum;
bool solved;
pair<int, int> v[101];
bool dp[50001][101];
void solve(int curSum, int idx) {
    auto [coin,cnt] = v[idx];
    if (solved || idx == N) return;
    if (dp[curSum][idx]) return;
    dp[curSum][idx] = true;
    solve(curSum, idx + 1);
    for (int i = 0; i < v[idx].second; i++) {
        curSum += v[idx].first;
        if (curSum > sum) return;
        if (curSum == sum) {
            solved = true;
            return;
        }
        solve(curSum, idx + 1);
    }
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    int TC = 3;
    while (TC--) {
        cin >> N;
        sum = 0;
        solved = false;
        for (int i = 0; i < N; i++) {
            int penny, count;
            cin >> penny >> count;
            sum += penny * count;
            v[i] = {penny, count};
        }
        for (int i = 0; i <= 50000; i++) {
            for (int j = 0; j <= N; j++) {
                dp[i][j] = false;
            }
        }
        //sort(v, v + N);
        // 홀수면 안됨
        if (sum & 1) {
            cout << false << '\n';
            continue;
        };
        sum /= 2;
        solve(0, 0);
        cout << solved << '\n';
    }

    return 0;
}
