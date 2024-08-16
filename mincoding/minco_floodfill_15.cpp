#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

int N;
char board[52][52] = {0};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];
  int y, x;
  cin >> y >> x;
  queue<pair<int, int>> q;
  if (board[y + 1][x + 1] == 'M')
    board[y + 1][x + 1] = 'X';
  else if (board[y + 1][x + 1] == 'E') {
    int cnt = 0;
    for (int dir2 = 0; dir2 < 8; dir2++) {
      int nny = y + 1 + dy[dir2];
      int nnx = x + 1 + dx[dir2];
      if (board[nny][nnx] == 'M') cnt++;
    }
    if (cnt == 0) {
      board[y + 1][x + 1] = 'B';
      q.push({y + 1, x + 1});
    } else {
      board[y + 1][x + 1] = '0' + cnt;
    }
  }
  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    q.pop();
    for (int dir = 0; dir < 8; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] == 'E') {
        int cnt = 0;
        for (int dir2 = 0; dir2 < 8; dir2++) {
          int nny = ny + dy[dir2];
          int nnx = nx + dx[dir2];
          if (board[nny][nnx] == 'M') cnt++;
        }
        if (cnt == 0) {
          board[ny][nx] = 'B';
          q.push({ny, nx});
        } else {
          board[ny][nx] = '0' + cnt;
        }
      }
    }
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      cout << board[i][j];
    }
    cout << endl;
  }
  return 0;
}
