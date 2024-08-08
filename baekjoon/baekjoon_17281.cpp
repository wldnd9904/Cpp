#include <iostream>
using namespace std;
int N;
int score[51][10];
int maxScore = -2147483648;

bool visited[10];
int taja[10];

void solve() {
  int ret = 0, turn = 0, curTaja = 0;

  while (turn < N) {
    int out = 0;
    bool roo[3] = {false};
    while (out < 3) {
      if (score[turn][taja[curTaja]] == 0) {
        out++;
      } else {
        // 다른 주자들 전진
        for (int i = 2; i >= 0; i--) {
          if (roo[i]) {
            roo[i] = false;
            if (i + score[turn][taja[curTaja]] > 2) {
              ret++;
            } else {
              roo[i + score[turn][taja[curTaja]]] = true;
            }
          }
        }
        // 타자 전진
        if (score[turn][taja[curTaja]] == 4)
          ret++;
        else
          roo[score[turn][taja[curTaja]] - 1] = true;
      }
      curTaja++;
      if (curTaja == 9) curTaja = 0;
    }
    turn++;
  }
  maxScore = maxScore > ret ? maxScore : ret;
}

// dfs로 퍼뮤테이션 완전탐색
void dfs(int cnt) {
  if (cnt == 9) {  // 팀 꾸려졌으면 계산
    solve();
    return;
  }
  if (cnt == 3) {  // 4번타자는 고정
    dfs(cnt + 1);
    return;
  }
  for (int i = 1; i < 9; i++) {
    if (visited[i]) continue;
    visited[i] = true;
    taja[cnt] = i;
    dfs(cnt + 1);
    visited[i] = false;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  taja[3] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 9; j++) {
      cin >> score[i][j];
    }
  }
  dfs(0);
  cout << maxScore;
  return 0;
}