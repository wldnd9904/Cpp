#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int T, N, M, C;
int board[10][10];
int dp[10][10];

void getMax(int y, int x, int cnt, int sum, int squareSum) {
  if (cnt == M) {
    dp[y][x] = max(dp[y][x], squareSum);
    return;
  }
  if (sum + board[y][x + cnt] <= C)
    getMax(y, x, cnt + 1, sum + board[y][x + cnt],
           squareSum + board[y][x + cnt] * board[y][x + cnt]);
  getMax(y, x, cnt + 1, sum, squareSum);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T;

  for (int test_case = 1; test_case <= T; ++test_case) {
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) cin >> board[i][j];

    for (int i = 0; i < N; i++)
      for (int j = 0; j <= N - M; j++) {
        dp[i][j] = 0;
        getMax(i, j, 0, 0, 0);
      }

    int maxY, maxX, maxSum = -1;
    int maxY2, maxX2, maxSum2 = -1;

    // 일단 제일 큰거 찾기
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= N - M; j++) {
        if (dp[i][j] > maxSum) {
          maxY = i;
          maxX = j;
          maxSum = dp[i][j];
        }
      }
    }

    // 그다음으로 큰거 찾기
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= N - M; j++) {
        if (i == maxY && abs(maxX - j) < M) continue;
        if (dp[i][j] > maxSum2) {
          maxY2 = i;
          maxX2 = j;
          maxSum2 = dp[i][j];
        }
      }
    }
    cout << "#" << test_case << " " << maxSum + maxSum2 << "\n";
  }

  return 0;
}