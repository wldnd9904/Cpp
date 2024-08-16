#include <iostream>
#include <queue>
using namespace std;
// 0: 제자리, 1~4: 주변 한칸, 5~12: 주변 두칸
const int dy[] = {0, -1, 1, 0, 0, -1, -1, 1, 1, -2, 2, 0, 0};
const int dx[] = {0, 0, 0, -1, 1, -1, 1, -1, 1, 0, 0, -2, 2};

int board[12][12];
int visited[12][12] = {0};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int Y, X;
  cin >> Y >> X;
  for (int i = 1; i <= Y; i++) {
    board[i][0] = -1;
    board[i][X + 1] = -1;
  }
  for (int i = 1; i <= X; i++) {
    board[0][i] = -1;
    board[Y + 1][i] = -1;
  }
  for (int i = 1; i <= Y; i++) {
    for (int j = 1; j <= X; j++) {
      char c;
      cin >> c;
      switch (c) {
        case '#':
          board[i][j] = -1;
          break;
        default:
          board[i][j] = c - '0';
          break;
      }
    }
  }
  queue<pair<int, int>> q;
  q.push({1, 1});
  visited[1][1] = 1;
  int qSize = 1;
  int time = 0;
  int phase = 1;
  while (phase <= 4) {
    time++;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      if (board[y][x] == phase) {
        q = queue<pair<int, int>>();
        q.push({y, x});
        phase += 1;
        time--;
        visited[y][x] = phase;
        break;
      }

      for (int dir = 1; dir <= 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx] == -1) continue;
        if (visited[ny][nx] == phase) continue;
        visited[ny][nx] = phase;
        q.push({ny, nx});
      }
    }
    qSize = q.size();
  }
  cout << time << "회";
  return 0;
}
