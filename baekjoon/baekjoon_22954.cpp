#include <iostream>
#include <vector>
using namespace std;
int N, S;
vector<int> v;
int visitCnt[7000001] = {
    0,
};
long long cnt = 0;
void solve1(int sum, int idx) {
    for (int i = idx + 1; i < N / 2; i++) {
        int nextSum = sum + v[i];
        if (nextSum == S) cnt++;
        visitCnt[nextSum + 3500000]++;
        solve1(nextSum, i);
    }
}
void solve2(int sum, int idx) {
    for (int i = idx + 1; i < N; i++) {
        int nextSum = sum + v[i];
        if (nextSum == S) cnt++;
        cnt += visitCnt[S - nextSum + 3500000];
        solve2(nextSum, i);
    }
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> S;
    v = vector<int>(N);
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        v[i] = num;
    }
    solve1(0, -1);
    solve2(0, N / 2 - 1);
    cout << cnt << '\n';
    return 0;
}