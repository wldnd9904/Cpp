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
  for (int i = 1; i <= N; i++) {
    board[i][0] = -1;
    board[i][M + 1] = -1;
  }
  for (int i = 1; i <= M; i++) {
    board[0][i] = -1;
    board[N + 1][i] = -1;
  }
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      cin >> board[i][j];
      visited[i][j] = 2147483647;
    }
  priority_queue<pair<int, pair<int, int>>> pq;  // 피로도, {y,x}
  pq.push({-board[1][1], {1, 1}});

  while (!pq.empty()) {
    int curDist = -pq.top().first;
    int y = pq.top().second.first;
    int x = pq.top().second.second;
    pq.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] == -1) continue;
      if (visited[ny][nx] <= curDist + board[ny][nx]) continue;
      visited[ny][nx] = curDist + board[ny][nx];
      pq.push({-visited[ny][nx], {ny, nx}});
    }
  }
  cout << visited[N][M];
  return 0;
}
