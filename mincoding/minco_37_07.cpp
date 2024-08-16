#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

int board[22][22];
int wall[22][22] = {false};
int visited1[22][22] = {false};
int visited2[22][22] = {false};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    wall[i][0] = 1;
    wall[i][M + 1] = 1;
  }
  for (int i = 1; i <= M; i++) {
    wall[0][i] = 1;
    wall[N + 1][i] = 1;
  }

  int sY, sX, cY, cX, eY, eX;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      char c;
      cin >> c;
      switch (c) {
        case 'S':
          sY = i;
          sX = j;
          break;
        case 'D':
          eY = i;
          eX = j;
          break;
        case 'C':
          cY = i;
          cX = j;
          break;
        case 'x':
          wall[i][j] = true;
          break;
      }
    }
  q.push({sY, sX});
  board[sY][sX] = 0;
  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    int cur = board[y][x];
    if (y == cY && x == cX) {
      q = queue<pair<int, int>>();
      q.push({y, x});
      break;
    }
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (wall[ny][nx]) continue;
      if (visited1[ny][nx]) continue;
      visited1[ny][nx] = true;
      board[ny][nx] = cur + 1;
      q.push({ny, nx});
    }
  }

  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    int cur = board[y][x];
    if (y == eY && x == eX) {
      cout << cur;
      return 0;
    }
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (wall[ny][nx]) continue;
      if (visited2[ny][nx]) continue;
      visited2[ny][nx] = true;
      board[ny][nx] = cur + 1;
      q.push({ny, nx});
    }
  }
  return 0;
}
