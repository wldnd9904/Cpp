#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

bool board[6][7] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  for (int i = 0; i <= 5; i++) {
    board[i][0] = 1;
    board[i][6] = 1;
  }
  for (int i = 0; i <= 6; i++) {
    board[0][i] = 1;
    board[5][i] = 1;
  }

  queue<pair<int, int>> q;

  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 5; j++) {
      cin >> board[i][j];
      if (board[i][j]) q.push({i, j});
    }
  int time = -1;
  int qSize = q.size();
  while (qSize) {
    ++time;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      for (int dir = 0; dir < 8; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx]) continue;
        board[ny][nx] = 1;
        q.push({ny, nx});
      }
    }
    qSize = q.size();
  }
  cout << time;
  return 0;
}
