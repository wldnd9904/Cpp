#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int N, M;
int board[202][202] = {0};
int idCnt[3] = {0};
int maxCnt = 0;
int maxId;
int cnt;

int countCreature(int y, int x, int id) {
  board[y][x] = 0;
  cnt++;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (board[ny][nx] == id) {
      countCreature(ny, nx, id);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      char c;
      cin >> c;
      if (c == '_') continue;
      board[i][j] = c == 'A' ? 1 : 2;
    }
  }
  queue<pair<int, int>> q;

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      if (board[i][j]) {
        int id = board[i][j];
        idCnt[id]++;
        cnt = 0;
        countCreature(i, j, id);
        if (cnt > maxCnt) {
          maxCnt = cnt;
          maxId = id;
        }
      }
    }
  cout << idCnt[1] << " " << idCnt[2] << "\n";
  cout << maxCnt;
  return 0;
}
