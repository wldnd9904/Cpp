#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

int board[6][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1},
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;
  int cnt = 0;
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 6; j++) cin >> board[i][j];
  q.push({1, 1});
  board[1][1] = 1;
  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] == 1) continue;
      if (board[ny][nx] == 2) cnt++;
      board[ny][nx] = 1;
      q.push({ny, nx});
    }
  }
  cout << cnt;
  return 0;
}
