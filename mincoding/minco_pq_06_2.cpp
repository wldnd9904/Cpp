#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MAX 303

using namespace std;

int N, M;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int ans = 0;

struct Square {
  int x, y;
  bool operator<(Square i) const { return map[y][x] > map[i.y][i.x]; }
};

priority_queue<Square> pq;

void BFS(int x, int y, int h) {
  queue<pair<int, int>> q;
  q.push({x, y});
  visited[y][x] = true;

  while (!q.empty()) {
    int CurX = q.front().first;
    int CurY = q.front().second;
    q.pop();

    for (int i = 0; i < 4; ++i) {
      int nx = CurX + dx[i];
      int ny = CurY + dy[i];

      if (!visited[ny][nx]) {
        visited[ny][nx] = true;

        if (map[ny][nx] > h)
          pq.push({nx, ny});
        else {
          ans += h - map[ny][nx];
          q.push({nx, ny});
        }
      }
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> M >> N;

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      cin >> map[i][j];
    }
  }

  for (int i = 1; i <= N; ++i) {
    visited[i][0] = true;
    visited[i][M + 1] = true;
    visited[i][1] = true;
    visited[i][M] = true;
    pq.push({i, 1});
    pq.push({i, M});
  }
  for (int i = 1; i <= M; ++i) {
    visited[0][i] = true;
    visited[N + 1][i] = true;
    visited[1][i] = true;
    visited[N][i] = true;
    pq.push({1, i});
    pq.push({N, i});
  }

  while (!pq.empty()) {
    Square s = pq.top();
    pq.pop();
    BFS(s.x, s.y, map[s.y][s.x]);
  }
  cout << ans;

  return 0;
}