#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int visited[1002][1002] = {0};
int board[1002][1002] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      cin >> board[i][j];
      visited[i][j] = 2147483647;
    }
  priority_queue<pair<int, pair<int, int>>> pq;  // 소모비용, {y,x}
  pq.push({-board[1][1] - 1, {1, 1}});
  if (board[1][1] == -1) {
    cout << -1;
    return 0;
  }
  while (!pq.empty()) {
    int curCost = -pq.top().first;
    int y = pq.top().second.first;
    int x = pq.top().second.second;
    if (y == N && x == M) {
      cout << curCost - 1;
      return 0;
    }
    pq.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] == -1) continue;
      if (visited[ny][nx] <= curCost + board[ny][nx]) continue;
      visited[ny][nx] = curCost + board[ny][nx];
      pq.push({-visited[ny][nx], {ny, nx}});
    }
  }
  cout << -1;
  return 0;
}
