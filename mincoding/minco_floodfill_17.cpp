#include <iostream>
#include <list>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};
int N, M;
int board[2][75][75];
int visited[75][75] = {0};
int fill(int y, int x, int time) {
  int ret = 1;
  visited[y][x] = time;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (visited[ny][nx] == time) continue;
    if (board[time & 1][ny][nx] == 0) continue;
    ret += fill(ny, nx, time);
  }
  return ret;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  list<pair<int, int>> l[2];
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) {
      cin >> board[0][i][j];
      if (board[0][i][j]) l[0].push_back({i, j});
    }
  int time = 0;
  while (true) {
    bool day = time & 1;

    time++;
    l[!day].clear();
    list<pair<int, int>> collapseList;
    for (pair<int, int>& pos : l[day]) {
      int y = pos.first;
      int x = pos.second;
      int n = board[day][y][x];
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[day][ny][nx] == 0) n--;
      }
      if (n <= 0) {
        board[!day][y][x] = 0;
        collapseList.push_back(pos);
      } else {
        board[!day][y][x] = n;
        l[!day].push_back(pos);
      }
    }
    for (auto& pos : collapseList) {
      board[day][pos.first][pos.second] = 0;
    }

    if (l[!day].size() == 0) {
      cout << 0;
      return 0;
    }
    auto firstOne = *(l[!day].begin());

    int cnt = fill(firstOne.first, firstOne.second, time);

    if (cnt != l[!day].size()) {
      cout << time;
      return 0;
    }
  }

  return 0;
}
