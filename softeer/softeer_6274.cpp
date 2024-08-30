#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
int N, T;
int board[4][102][102] = {0};
int visited[4][102][102] = {0};  // [dir][y][x]
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};  // 상, 하, 좌, 우

bool signalDirAvailable[13][4] = {
    {0, 0, 0, 0},  // 무시
    {1, 1, 0, 1},  // 1:  상 하 ㅁ 우
    {1, 0, 1, 1},  // 2:  상 ㅁ 좌 우
    {1, 1, 1, 0},  // 3:  상 하 좌 ㅁ
    {0, 1, 1, 1},  // 4:  ㅁ 하 좌 우
    {1, 0, 0, 1},  // 5:  상 ㅁ ㅁ 우
    {1, 0, 1, 0},  // 6:  상 ㅁ 좌 ㅁ
    {0, 1, 1, 0},  // 7:  ㅁ 하 좌 ㅁ
    {0, 1, 0, 1},  // 8:  ㅁ 하 ㅁ 우
    {0, 1, 0, 1},  // 9:  ㅁ 하 ㅁ 우
    {1, 0, 0, 1},  // 10: 상 ㅁ ㅁ 우
    {1, 0, 1, 0},  // 11: 상 ㅁ 좌 ㅁ
    {0, 1, 1, 0},  // 12: ㅁ 하 좌 ㅁ
};
// signalDir[a]: 신호 a는 어느 방향 바라보는 차들만 출발할 수 있는지
int signalDir[13] = {4, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 1};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> T;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int k = 0; k < 4; k++) {
        cin >> board[k][i][j];
      }
    }
  }
  queue<pair<pair<int, int>, int>> q;  //{{y,x}, dir}
  q.push({{1, 1}, 0});
  visited[0][1][1] = true;
  int qSize = 1;
  int time = 0;
  while (qSize) {
    while (qSize--) {
      auto [pos, curDir] = q.front();
      auto [y, x] = pos;
      int sig = board[time % 4][y][x];
      q.pop();
      if (signalDir[sig] != curDir) continue;
      for (int dir = 0; dir < 4; dir++) {
        if (!signalDirAvailable[sig][dir]) continue;
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[0][ny][nx] == 0) continue;
        q.push({{ny, nx}, dir});
        visited[dir][ny][nx] = true;
        continue;
      }
    }
    time++;
    qSize = q.size();
    if (time == T) break;
  }
  int ret = 0;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      bool out = 0;
      for (int k = 0; k < 4; k++) {
        if (visited[k][i][j]) {
          ret++;
          break;
        }
      }
    }
  }
  cout << ret;
  return 0;
}