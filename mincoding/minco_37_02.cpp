#include <iostream>
#include <queue>
using namespace std;
int N, M;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

bool board[1002][1002] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    board[i][0] = 1;
    board[i][M + 1] = 1;
  }
  for (int i = 1; i <= M; i++) {
    board[0][i] = 1;
    board[N + 1][i] = 1;
  }

  queue<pair<int, int>> q;

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];

  int y, x;
  cin >> y >> x;
  y++;
  x++;
  q.push({y, x});
  board[y][x] = 1;

  int time = -1;
  int qSize = 1;
  while (qSize) {
    ++time;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
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
