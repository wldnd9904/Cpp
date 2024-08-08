#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int T, D, W, K;  // 테스트 케이스, 두께, 가로사이즈, 통과조건(이상)
int ret;
bool board[13][20];
int injected[13];  // 0은 주사안함, 1(0) 또는 2(1)는 주사함

bool check() {
  for (int x = 0; x < W; ++x) {
    bool checked = false;
    int curType = -1;
    int curCnt = 0;
    for (int y = 0; y < D; ++y) {
      if (injected[y] == -1) {
        if (board[y][x] == curType) {
          ++curCnt;
          if (curCnt == K) {
            checked = true;
            break;
          }
        } else {
          curCnt = 1;
          curType = board[y][x];
        }
      } else {
        if (injected[y] == curType) {
          ++curCnt;
          if (curCnt == K) {
            checked = true;
            break;
          }
        } else {
          curCnt = 1;
          curType = injected[y];
        }
      }
    }
    if (!checked) return false;
  }
  return true;
}

void solve(int cur, int cnt, int curUsed) {
  if (ret == cnt) return;
  if (cnt == curUsed) {
    if (check()) ret = cnt;
    return;
  }
  if (cur == D) return;
  solve(cur + 1, cnt, curUsed);
  injected[cur] = 0;
  solve(cur + 1, cnt, curUsed + 1);
  injected[cur] = 1;
  solve(cur + 1, cnt, curUsed + 1);
  injected[cur] = -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T;

  for (int test_case = 1; test_case <= T; ++test_case) {
    // 입력받기
    cin >> D >> W >> K;
    for (int i = 0; i < D; ++i)
      for (int j = 0; j < W; ++j) cin >> board[i][j];

    // 전역변수 초기화
    for (int i = 0; i < D; ++i) injected[i] = -1;
    ret = -1;

    int cnt = 0;
    if (K <= 1) ret = 0;
    while (cnt <= K) {
      if (ret >= 0) break;
      solve(0, cnt, 0);
      ++cnt;
    }
    cout << "#" << test_case << " " << ret << "\n";
  }

  return 0;
}