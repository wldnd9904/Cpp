#include <iostream>
#include <queue>
using namespace std;
// 0: 제자리, 1~4: 주변 한칸, 5~12: 주변 두칸
const int dy[] = {0, -1, 1, 0, 0, -1, -1, 1, 1, -2, 2, 0, 0};
const int dx[] = {0, 0, 0, -1, 1, -1, 1, -1, 1, 0, 0, -2, 2};

queue<pair<int, int>> q;
// 0은 벽, 1은 빈칸, 2는 마킹 안된 사람, 3은 마킹된 사람, 4부터는 이동거리+3
int board[10][11] = {0};
void mark(int y, int x) {
  q.push({y, x});
  for (int dir = 1; dir <= 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (board[ny][nx] == 2) {
      board[ny][nx] = 3;
      mark(ny, nx);
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  for (int i = 1; i <= 8; i++)
    for (int j = 1; j <= 9; j++) {
      char c;
      cin >> c;
      switch (c) {
        case '#':
          board[i][j] = 2;
          break;
        case '_':
          board[i][j] = 1;
          break;
      }
    }
  bool marked = false;
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 9; j++) {
      if (board[i][j] == 2) {
        mark(i, j);
        marked = true;
        break;
      }
    }
    if (marked) break;
  }

  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    q.pop();
    int cur = board[y][x];
    for (int dir = 1; dir <= 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] == 2) {
        cout << cur - 3;
        return 0;
      }
      if (board[ny][nx] == 1) {
        board[ny][nx] = cur + 1;
        q.push({ny, nx});
      }
    }
  }

  return 0;
}
