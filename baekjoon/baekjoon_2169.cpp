#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int Y, X;
vector<vector<int>> v;

int solve() {
    vector<int> tmp(X);  // 한 줄에서의 최댓값들
    // 첫줄에서는 오른쪽으로만 갈 수 있음
    tmp[0] = v[0][0];
    for (int i = 1; i < X; i++) tmp[i] = tmp[i - 1] + v[0][i];

    // 다음줄부터는 모든 칸의 좌우방향에 대해 한번씩 훑기
    for (int y = 1; y < Y; y++) {
        int curMax = tmp[X - 1];
        vector<int> leftTmp(X, -2147483647);
        vector<int> rightTmp(X, -2147483647);
        // 왼쪽(오른쪽끝에서출발)
        for (int x = X - 1; x >= 0; x--) {
            curMax = max(curMax, tmp[x]) + v[y][x];
            curMax = leftTmp[x] = max(leftTmp[x], curMax);
        }
        // 반대로
        curMax = tmp[0];
        for (int x = 0; x < X; x++) {
            curMax = max(curMax, tmp[x]) + v[y][x];
            curMax = rightTmp[x] = max(rightTmp[x], curMax);
        }
        // 합치기
        for (int x = 0; x < X; x++) {
            tmp[x] = max(leftTmp[x], rightTmp[x]);
        }
    }
    return tmp[X - 1];
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> Y >> X;
    v = vector<vector<int>>(Y, vector<int>(X));
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            int i;
            cin >> i;
            v[y][x] = i;
        }
    }
    cout << solve() << '\n';

    return 0;
}