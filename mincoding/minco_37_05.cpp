#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

int board[6][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 1},
    {
        1,
        1,
        1,
        1,
        1,
        1,
    },
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;

  int sY, sX, eY, eX;
  cin >> sY >> sX >> eY >> eX;
  sY++;
  sX++;
  eY++;
  eX++;
  q.push({sY, sX});
  board[sY][sX] = 1;
  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    int cur = board[y][x];
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (ny == eY && nx == eX) {
        cout << cur << "회";
        return 0;
      }
      if (board[ny][nx]) continue;
      board[ny][nx] = cur + 1;
      q.push({ny, nx});
    }
  }
  return 0;
}
