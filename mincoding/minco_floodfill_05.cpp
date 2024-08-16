#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-2, -3, -3, -2, 2, 3, 3, 2};
const int dx[] = {-3, -2, 2, 3, 3, 2, -2, -3};
int height, width;
int visited[101][101] = {0};
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
  visited[y][x] = 1;
  int targetY, targetX;
  cin >> targetY >> targetX;

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int y, x;
    cin >> y >> x;
    visited[y][x] = 1;
  }

  while (!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    int cur = visited[y][x];
    q.pop();
    for (int dir = 0; dir < 8; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (!check(ny, nx)) continue;
      if (visited[ny][nx]) continue;
      if (ny == targetY && nx == targetX) {
        cout << cur;
        return 0;
      }
      visited[ny][nx] = cur + 1;
      q.push({ny, nx});
    }
  }
  cout << -1;
  return 0;
}