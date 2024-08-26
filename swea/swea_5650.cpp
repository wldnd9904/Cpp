#include <iostream>
#include <vector>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int N;

int maxCnt;
int curCnt;
int idCnt = 0;
int visited[102][102] = {0};
int board[102][102];

vector<vector<pair<int, int>>> wormhole;

int dirFromTo[4][6] = {
    {0, 1, 3, 2, 1, 1},  // 위
    {1, 3, 0, 0, 2, 0},  // 아래
    {2, 0, 1, 3, 3, 3},  // 왼쪽
    {3, 2, 2, 1, 0, 2},  // 오른쪽
};

void fillAndCnt(int y, int x, int dir, int id, bool start = false) {
  if (!start && visited[y][x] == id) return;
  if (board[y][x] == -1) return;
  if (board[y][x] > 5) {
    pair<int, int> dest1 = wormhole[board[y][x]][0];
    pair<int, int> dest2 = wormhole[board[y][x]][1];
    if (dest2.first == y && dest2.second == x) {
      fillAndCnt(dest1.first + dy[dir], dest1.second + dx[dir], dir, id);
    } else if (dest1.first == y && dest1.second == x) {
      fillAndCnt(dest2.first + dy[dir], dest2.second + dx[dir], dir, id);
    }
    return;
  }
  int ndir = dir;
  if (board[y][x] > 0) {
    ndir = dirFromTo[dir][board[y][x]];
    if (dir + ndir == 1 || dir + ndir == 5) {
      curCnt *= 2;
      curCnt++;
      return;
    }
    curCnt++;
  }
  int ny = y + dy[ndir];
  int nx = x + dx[ndir];
  fillAndCnt(ny, nx, ndir, id);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N;
    wormhole = vector<vector<pair<int, int>>>(11, vector<pair<int, int>>());
    for (int i = 1; i <= N; i++) {
      board[i][0] = 5;
      board[0][i] = 5;
      board[i][N + 1] = 5;
      board[N + 1][i] = 5;
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        cin >> board[i][j];
        if (board[i][j] > 5) {
          wormhole[board[i][j]].push_back({i, j});
        }
      }
    }
    maxCnt = 0;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (board[i][j] != 0) continue;
        for (int dir = 0; dir < 4; dir++) {
          curCnt = 0;
          idCnt++;
          visited[i][j] = idCnt;
          fillAndCnt(i, j, dir, idCnt, true);
          if (curCnt > maxCnt) maxCnt = curCnt;
        }
      }
    }

    cout << "#" << test_case << " " << maxCnt << "\n";
  }
  return 0;
}