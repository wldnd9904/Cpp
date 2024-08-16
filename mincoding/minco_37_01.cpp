#include <iostream>
#include <queue>
using namespace std;
int N;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int board[102][102] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 1; i <= N; i++) {
    board[i][0] = -1;
    board[0][i] = -1;
    board[N + 1][i] = -1;
    board[i][N + 1] = -1;
  }
  queue<pair<int, int>> q;
  int ax, ay, bx, by;
  cin >> ay >> ax >> by >> bx;
  int power = 1;
  int qSize = 2;
  q.push({ay + 1, ax + 1});
  q.push({by + 1, bx + 1});
  board[ay + 1][ax + 1] = power;
  board[by + 1][bx + 1] = power;
  while (qSize) {
    ++power;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx]) continue;
        board[ny][nx] = power;
        q.push({ny, nx});
      }
    }
    qSize = q.size();
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cout << board[i][j];
    }
    cout << "\n";
  }

  return 0;
}
