#include <stdlib.h>

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
struct node {
  int y, x;
  bool buffed;
  int dist;
};
struct cmp {
  bool operator()(node& a, node& b) { return a.dist > b.dist; }
};
int board[1002][1002] = {0};
int visited[2][1002][1002] = {0};  // 0:기본, 1:버프
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];

  priority_queue<node, vector<node>, cmp> q;
  q.push({1, 1, false, 1});
  visited[0][1][1] = 1;
  while (!q.empty()) {
    node cur = q.top();
    int curDist = visited[cur.buffed][cur.y][cur.x];
    if (cur.y == N && cur.x == M) {
      cout << curDist - 1;
      return 0;
    }
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = cur.y + dy[dir];
      int nx = cur.x + dx[dir];
      int nDist = curDist + 1;
      bool nBuffed = cur.buffed;
      if (board[ny][nx] == 0) continue;
      if (board[ny][nx] == 3 && !nBuffed) continue;
      if (board[ny][nx] == 2) nBuffed = true;
      while (board[ny][nx] == 4) {
        nBuffed = false;
        int next = board[ny + dy[dir]][nx + dx[dir]];
        if (next == 3 || next == 0) break;
        ny += dy[dir];
        nx += dx[dir];
        nDist++;
      }
      if (visited[nBuffed][ny][nx] != 0 && visited[nBuffed][ny][nx] <= nDist)
        continue;
      visited[nBuffed][ny][nx] = nDist;
      q.push({ny, nx, nBuffed, nDist});
    }
  }
  cout << -1;
  return 0;
}
