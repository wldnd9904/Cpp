#include <iostream>
using namespace std;

// 0:빈칸, 1:벽, 2부터는 방문지점
int board[6][6] = {
    {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1},
};

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int dfs(int y, int x, int cur, int last) {
  if (cur == last) return 1;
  if (board[y][x] == cur + 1) {
    board[y][x] = 1;
    int ret = dfs(y, x, cur + 1, last);
    board[y][x] = cur + 1;
    return ret;
  }
  board[y][x] = 1;
  int ret = 0;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (board[ny][nx] == 1) continue;
    if (board[ny][nx] > 0 && board[ny][nx] != cur + 1) continue;
    ret += dfs(ny, nx, cur, last);
  }
  board[y][x] = 0;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) cin >> board[i][j];

  int sx, sy;
  cin >> sy >> sx;
  board[sy][sx] = 2;
  for (int i = 3; i < M + 2; i++) {
    int x, y;
    cin >> y >> x;
    board[y][x] = i;
  }


  cout << dfs(sy, sx, 2, M + 1);
  return 0;
}