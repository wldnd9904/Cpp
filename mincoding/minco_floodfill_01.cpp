#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int board[5][5] = {0};
bool check(int y, int x) { return y >= 0 && y < 5 && x >= 0 && x < 5; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int y, x;
  cin >> y >> x;
  queue<pair<int, int>> q;
  q.push({y, x});
  board[y][x] = 1;
  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    int cur = board[y][x];
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (!check(ny, nx)) continue;
      if (board[ny][nx]) continue;
      board[ny][nx] = cur + 1;
      q.push({ny, nx});
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}