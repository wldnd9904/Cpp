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
  cin >> height >> width;
  queue<pair<int, int>> q;
  int y, x;
  cin >> y >> x;
  q.push({y, x});
  board[y][x] = 1;

  cin >> y >> x;
  q.push({y, x});
  board[y][x] = 1;

  int qSize = 2;
  int time = 0;
  while (qSize) {
    time++;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      int cur = board[y][x];
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (!check(ny, nx)) continue;
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