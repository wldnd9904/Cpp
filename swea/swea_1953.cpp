#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
using namespace std;
int T, N, M, R, C, L;
const int dy[] = {-1, 1, 0, 0};  // 상, 하, 좌, 우
const int dx[] = {0, 0, -1, 1};
const int rev[] = {1, 0, 3, 2};
const bool canGo[][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 0, 0},
                         {0, 0, 1, 1}, {1, 0, 0, 1}, {0, 1, 0, 1},
                         {0, 1, 1, 0}, {1, 0, 1, 0}};

int board[52][52];
int visited[52][52] = {0};
int bfsCnt = 0;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("input.txt", "r", stdin);
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    bfsCnt++;
    cin >> N >> M >> R >> C >> L;

    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= M; j++) cin >> board[i][j];

    for (int i = 0; i < N + 1; i++) {
      visited[i][0] = bfsCnt;
      visited[i][M + 1] = bfsCnt;
    }
    for (int i = 0; i < M + 1; i++) {
      visited[0][i] = bfsCnt;
      visited[N + 1][i] = bfsCnt;
    }
    int cnt = 0;
    queue<pair<int, int>> q;
    q.push({R + 1, C + 1});
    visited[R + 1][C + 1] = bfsCnt;
    int qSize = q.size();
    while (L--) {
      while (qSize--) {
        int y = q.front().first;
        int x = q.front().second;
        int cur = board[y][x];
        // cout << y << ", " << x << endl;
        cnt++;
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
          if (!canGo[cur][dir]) continue;
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (visited[ny][nx] == bfsCnt) continue;
          if (!canGo[board[ny][nx]][rev[dir]]) continue;
          visited[ny][nx] = bfsCnt;
          q.push({ny, nx});
        }
      }
      qSize = q.size();
    }

    cout << "#" << test_case << " " << cnt << "\n";
  }
  return 0;
}
