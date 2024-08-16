#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int N;
int board[22][22];             // 0:: 빈공간, 1: 벽, 2: 소화기, 3:불
int visited[2][22][22] = {0};  // 0: 맨손, 1: 소화기 들었을 때
queue<pair<bool, pair<int, int>>> q;  // 소화기 있는지여부, 위치;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;

  // 프레임씌우기
  for (int i = 1; i <= N; i++) {
    board[i][0] = 1;
    board[i][N + 1] = 1;
    board[0][i] = 1;
    board[N + 1][i] = 1;
  }

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) {
      char c;
      cin >> c;
      switch (c) {
        case '_':
          board[i][j] = 0;
          continue;
        case '#':
          board[i][j] = 1;
          continue;
        case 'A':
          board[i][j] = 2;
          continue;
        case '$':
          board[i][j] = 3;
          continue;
      }
    }
  int sY, sX;
  cin >> sY >> sX;
  q.push({0, {sY + 1, sX + 1}});
  visited[0][sY + 1][sX + 1] = 1;

  while (!q.empty()) {
    bool hasExtinguisher = q.front().first;
    int y = q.front().second.first;
    int x = q.front().second.second;
    q.pop();

    int cur = visited[hasExtinguisher][y][x];

    if (!hasExtinguisher && board[y][x] == 3) {
      continue;
    }
    if (!hasExtinguisher && board[y][x] == 2) {
      q.push({true, {y, x}});
      visited[true][y][x] = cur;
      continue;
    }
    if (hasExtinguisher && board[y][x] == 3) {
      cout << cur - 1;
      return 0;
    }
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] == 1) continue;
      if (visited[hasExtinguisher][ny][nx]) continue;
      visited[hasExtinguisher][ny][nx] = cur + 1;
      q.push({hasExtinguisher, {ny, nx}});
    }
  }
  return 0;
}
