#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};
int H, W;
int board[151][151] = {0};
bool check(int y, int x) { return y >= 0 && y < H && x >= 0 && x < W; }

int cure(int y, int x) {
  board[y][x] = false;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    if (!check(ny, nx)) continue;
    if (!board[ny][nx]) continue;
    cure(ny, nx);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> H >> W;
  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++) cin >> board[i][j];

  int cnt = 0;

  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
      if (board[i][j] == 2) {
        cnt++;
        cure(i, j);
      }
  cout << cnt;
  return 0;
}