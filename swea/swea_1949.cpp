#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
int board[10][10];
int T, N, K;
int peakHeight;
int ret;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
bool visited[10][10] = {false};

void dfs(int y, int x, int cur, bool digged) {
  visited[y][x] = true;
  ret = max(cur, ret);
  const int curHeight = board[y][x];
  for (int dir = 0; dir < 4; dir++) {
    const int ny = y + dy[dir];
    const int nx = x + dx[dir];
    if (visited[ny][nx]) continue;
    if (board[ny][nx] >= curHeight) {
      if (digged) continue;
      int dif = board[ny][nx] - curHeight + 1;
      if (dif > K) continue;
      board[ny][nx] -= dif;
      dfs(ny, nx, cur + 1, true);
      board[ny][nx] += dif;
    } else {
      dfs(ny, nx, cur + 1, digged);
    }
  }
  visited[y][x] = false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N >> K;
    peakHeight = -1;
    // 테두리
    for (int i = 0; i <= N + 1; i++) {
      visited[i][0] = true;
      visited[0][i] = true;
      visited[N + 1][i] = true;
      visited[i][N + 1] = true;
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        int tmp;
        cin >> tmp;
        board[i][j] = tmp;
        visited[i][j] = false;
        peakHeight = max(peakHeight, tmp);
      }
    }
    ret = 0;
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (board[i][j] == peakHeight) {
          dfs(i, j, 1, false);
        }
      }
    }

    cout << "#" << test_case << " " << ret << "\n";
  }
  return 0;
}
