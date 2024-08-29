#include <iostream>
#include <queue>
#include <string>
using namespace std;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
int N, M;

int main(int argc, char** argv) {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  vector<vector<int>> board(N + 2, vector<int>(M + 2, 2147483647));
  vector<pair<int, int>> ghosts;
  int sY, sX, eY, eX;
  for (int y = 1; y <= N; y++) {  // input
    for (int x = 1; x <= M; x++) {
      char c;
      cin >> c;
      switch (c) {
        case 'D':
          board[y][x] = 0;
          eY = y;
          eX = x;
          break;
        case '.':
          board[y][x] = 0;
          break;
        case 'G':
          board[y][x] = 0;
          ghosts.push_back({y, x});
          break;
        case 'N':
          board[y][x] = 0;
          sY = y;
          sX = x;
          break;
        case '#':
          board[y][x] = 2147483646;
          break;
      }
    }
  }  // endof input

  bool answer = false;
  queue<pair<int, int>> q;  // y, x
  q.push({sY, sX});
  int timeLimit = 2147483647;
  for (auto [y, x] : ghosts) {
    int dist = abs(eY - y) + abs(eX - x);
    timeLimit = min(timeLimit, dist);
  }
  board[sY][sX] = 1;

  while (!q.empty()) {
    auto [y, x] = q.front();
    int cur = board[y][x];
    if (cur >= timeLimit) break;
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx]) continue;
      board[ny][nx] = cur + 1;
      if (ny == eY && nx == eX) {
        cout << "Yes";
        return 0;
      }
      q.push({ny, nx});
    }
  }
  cout << "No";
  return 0;
}