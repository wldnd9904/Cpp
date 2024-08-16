#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};
int height, width;

bool board[100][100] = {0};
bool check(int y, int x) { return y >= 0 && y < height && x >= 0 && x < width; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> width >> height;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char c;
      cin >> c;
      board[i][j] = c - '0';
    }
  }

  queue<pair<int, int>> q;
  int y, x;
  cin >> x >> y;
  q.push({y - 1, x - 1});
  board[y - 1][x - 1] = false;

  int qSize = 1;
  int time = 0;
  while (qSize) {
    time++;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (!check(ny, nx)) continue;
        if (!board[ny][nx]) continue;
        board[ny][nx] = false;
        q.push({ny, nx});
      }
    }
    qSize = q.size();
  }
  cout << time + 2 << "\n";

  int cnt = 0;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cnt += board[i][j];
    }
  }
  cout << cnt;
  return 0;
}