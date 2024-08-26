#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
bool board[52][52] = {0};
bool visited[52][52] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    visited[i][N + 1] = true;
    visited[i][0] = true;
    visited[0][i] = true;
    visited[N + 1][i] = true;

    for (int j = 1; j <= N; j++) {
      char c;
      cin >> c;
      board[i][j] = (c == '1');
    }
  }
  priority_queue<pair<int, pair<int, int>>> pq;  // -부순 벽, {y,x}
  pq.push({0, {1, 1}});
  while (!pq.empty()) {
    int curCrash = -pq.top().first;
    int y = pq.top().second.first;
    int x = pq.top().second.second;
    pq.pop();
    if (visited[y][x]) continue;
    visited[y][x] = true;
    if (y == N && x == N) {
      cout << curCrash;
      return 0;
    }
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      int nCrash = curCrash;
      if (visited[ny][nx]) continue;
      if (board[ny][nx] == 0) nCrash++;
      pq.push({-nCrash, {ny, nx}});
    }
  }
  cout << -1;
  return 0;
}
