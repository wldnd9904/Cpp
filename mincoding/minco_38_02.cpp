#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

int board[6][11] = {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

int maxCnt = 0;
int maxId;
int cnt;
int countBee(int y, int x, int id) {
  board[y][x] = -1;
  cnt++;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (board[ny][nx] == id) {
      countBee(ny, nx, id);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 9; j++) cin >> board[i][j];

  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 9; j++) {
      if (board[i][j] != -1) {
        int id = board[i][j];
        cnt = 0;
        countBee(i, j, id);
        if (cnt > maxCnt) {
          maxCnt = cnt;
          maxId = id;
        }
      }
    }
  cout << maxId * maxCnt;
  return 0;
}
