#include <math.h>

#include <iostream>
#include <queue>
using namespace std;

int H, K, R;
int total = 0;
queue<int> q[2048][2];  // 왼쪽이 0, 오른쪽이 1

void toss(int cur, int curHeight, int maxHeight, bool isRight) {
  // 부서장은 일 끝내기
  if (cur == 1) {
    if (!q[1][isRight].empty()) {
      total += q[1][isRight].front();
      q[1][isRight].pop();
    }
  } else {
    // 일 올리기
    if (!q[cur][isRight].empty()) {
      int task = q[cur][isRight].front();
      q[cur][isRight].pop();
      q[cur / 2][cur & 1].push(task);
    }
  }
  if (curHeight == maxHeight) return;
  toss(cur * 2, curHeight + 1, maxHeight, isRight);
  toss(cur * 2 + 1, curHeight + 1, maxHeight, isRight);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("input.txt", "r", stdin);
  cin >> H >> K >> R;
  int base = pow(2, H);
  for (int i = 0; i < base; i++) {
    for (int j = 0; j < K; j++) {
      int task;
      cin >> task;
      q[base + i][j & 1].push(task);
    }
  }

  for (int i = 0; i < R; i++) {
    toss(1, 0, H, i & 1);
  }
  cout << total;
  return 0;
}