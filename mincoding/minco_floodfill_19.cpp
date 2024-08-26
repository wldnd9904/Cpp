#include <iostream>
#include <list>
#include <queue>
using namespace std;
struct node {
  int y;
  int x;
  int dir;
};

const int dy[] = {-1, 0, 1, 0};  // 상, 좌, 하, 우
const int dx[] = {0, -1, 0, 1};
const int dirMap[] = {0, 3, 1, 2, 0};
int N, M;
int board[102][102];
int visited[4][102][102] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    board[i][0] = 1;
    board[i][M + 1] = 1;
  }
  for (int i = 1; i <= M; i++) {
    board[0][i] = 1;
    board[N + 1][i] = 1;
  }
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];
  int sY, sX, sDir;
  int eY, eX, eDir;
  cin >> sY >> sX >> sDir;
  cin >> eY >> eX >> eDir;
  sDir = dirMap[sDir];
  eDir = dirMap[eDir];

  queue<node> q;
  q.push({sY, sX, sDir});
  visited[sDir][sY][sX] = 1;
  while (!q.empty()) {
    node cur = q.front();
    q.pop();
    int y = cur.y;
    int x = cur.x;
    int dir = cur.dir;
    int curDist = visited[dir][y][x];
    if (y == eY && x == eX && dir == eDir) {
      cout << curDist - 1;
      return 0;
    }
    // 커맨드1: 1칸, 2칸, 3칸 앞으로 이동
    for (int i = 1; i <= 3; i++) {
      int ny = y + dy[dir] * i;
      int nx = x + dx[dir] * i;
      if (board[ny][nx]) break;
      if (visited[dir][ny][nx]) continue;
      visited[dir][ny][nx] = curDist + 1;
      q.push({ny, nx, dir});
    }
    // 커맨드2: 90도 이동
    int ndir1 = (dir + 1) % 4;
    int ndir2 = (dir + 3) % 4;
    if (!visited[ndir1][y][x]) {
      visited[ndir1][y][x] = curDist + 1;
      q.push({y, x, ndir1});
    }
    if (!visited[ndir2][y][x]) {
      visited[ndir2][y][x] = curDist + 1;
      q.push({y, x, ndir2});
    }
  }

  return 0;
}
