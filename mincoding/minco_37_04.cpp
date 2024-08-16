#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

bool board[6][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 3, 3, 3, 3, 0},
    {0, 3, 3, 3, 3, 0},
    {0, 3, 3, 3, 3, 0},
    {0, 3, 3, 3, 3, 0},
    {
        0,
        0,
        0,
        0,
        0,
        0,
    },
};
int cnt = 0;

void dfs(int y, int x) {
  board[y][x] = false;
  cnt++;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (!board[ny][nx]) continue;
    dfs(ny, nx);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;

  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 4; j++) {
      cin >> board[i][j];
    }
  dfs(1, 1);
  cout << cnt;
  return 0;
}
