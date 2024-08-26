#include <stdlib.h>

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int N, M;
int board[52][52];
int visited[52][52] = {0};
int bfsCnt = 0;
int startY, startX;

bool canCollectGem(int power) {  // power이하로만 수직이동 가능
  bfsCnt++;
  queue<pair<pair<int, int>, int>> q;  //{y,x},현재 수직이동 수치
  q.push({{startY, startX}, 0});
  visited[startY][startX] = bfsCnt;
  while (!q.empty()) {
    int y = q.front().first.first;
    int x = q.front().first.second;
    int curFloat = q.front().second;
    q.pop();
    int dirLimit = board[y][x] == 0 ? 2 : 4;
    for (int dir = 0; dir < dirLimit; dir++) {
      if ((dir == 0 || dir == 1) && curFloat == power) continue;
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      int nFloat = curFloat;
      if (visited[ny][nx] >= bfsCnt) continue;
      if (board[ny][nx] == 3) return true;
      if (board[ny][nx] == 0) {
        if (dir == 2 || dir == 3) continue;
        nFloat++;
      } else {
        nFloat = 0;
      }
      visited[ny][nx] = bfsCnt;
      q.push({{ny, nx}, nFloat});
    }
  }
  return false;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;

  for (int i = 1; i <= N; i++) {
    visited[i][0] = 999999;
    visited[i][M + 1] = 999999;
  }
  for (int i = 1; i <= M; i++) {
    visited[N + 1][i] = 999999;
    visited[0][i] = 999999;
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      cin >> board[i][j];
      if (board[i][j] == 2) {
        startY = i;
        startX = j;
        board[i][j] = 1;
      }
    }
  }

  for (int i = 0; i <= 50; i++) {
    if (canCollectGem(i)) {
      cout << i;
      return 0;
    }
  }
  return 0;
}
