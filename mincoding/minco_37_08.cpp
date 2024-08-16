#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};

int board[102][102] = {0};

int islandId = 2;

int markIsland(int y, int x) {
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (board[ny][nx] == 1) {
      board[ny][nx] = islandId;
      markIsland(ny, nx);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      if (board[i][j] == 1) {
        markIsland(i, j);
        islandId++;
      }
    }
  cout << islandId - 2;
  return 0;
}
