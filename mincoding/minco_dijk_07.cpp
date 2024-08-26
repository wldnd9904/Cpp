#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int visited[32][32] = {0};
int board[32][32] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, A, B;
  cin >> N >> A >> B;
  for (int i = 1; i <= N; i++) {
    board[i][0] = -1;
    board[i][N + 1] = -1;
    board[0][i] = -1;
    board[N + 1][i] = -1;
  }
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) {
      char c;
      cin >> c;
      board[i][j] = (c == '(' ? 0 : 1);
    }

  int maxCost = 0;
  int curIt = 0;
  for (int startY = 1; startY <= N; startY++) {
    for (int startX = 1; startX <= N; startX++) {
      curIt++;
      priority_queue<pair<int, pair<int, int>>> pq;  // 사용한 연료, {y,x}
      pq.push({0, {startY, startX}});

      while (!pq.empty()) {
        int curCost = -pq.top().first;
        int y = pq.top().second.first;
        int x = pq.top().second.second;
        pq.pop();
        if (visited[y][x] == curIt) continue;
        visited[y][x] = curIt;
        maxCost = max(curCost, maxCost);
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (board[ny][nx] == -1) continue;
          if (visited[ny][nx] == curIt) continue;
          int cost = board[y][x] == board[ny][nx] ? A : B;
          pq.push({-(curCost + cost), {ny, nx}});
        }
      }
    }
  }
  cout << maxCost;
  return 0;
}
