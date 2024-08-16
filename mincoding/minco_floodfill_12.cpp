#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int N, M;
int board[202][202];
queue<pair<int, int>> q;
bool visited[202][202] = {0};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;

  // 프레임씌우기
  for (int i = 1; i <= N; i++) {
    board[i][0] = -1;
    board[i][M + 1] = -1;
  }
  for (int i = 1; i <= M; i++) {
    board[0][i] = -1;
    board[N + 1][i] = -1;
  }
  int id = 0;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      cin >> board[i][j];
      if (id == 0 && board[i][j]) id = board[i][j];
      if (id != 0 && id == board[i][j]) {
        q.push({i, j});
        visited[i][j] = true;
      }
    }
  int qSize = q.size();
  int dist = 0;
  while (qSize) {
    dist++;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx] == -1) continue;
        if (visited[ny][nx]) continue;
        visited[ny][nx] = true;
        if (board[ny][nx] != 0 && board[ny][nx] != id) {
          cout << dist - 1;
          return 0;
        }
        q.push({ny, nx});
      }
    }
    qSize = q.size();
  }
  return 0;
}
