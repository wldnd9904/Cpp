#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0, 0, 0};
const int dx[] = {0, 0, -1, 1, 0, 0};
const int dz[] = {0, 0, 0, 0, -1, 1};

int N;
int board[102][102][102];
queue<pair<int, pair<int, int>>> q;  // {z, {y,x}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 0; i <= N + 1; i++)
    for (int j = 0; j <= N + 1; j++)
      for (int k = 0; k <= N + 1; k++) board[i][j][k] = 1;

  int xs, ys, zs;
  int xe, ye, ze;
  cin >> xs >> ys >> zs;
  cin >> xe >> ye >> ze;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
      for (int k = 1; k <= N; k++) {
        char c;
        cin >> c;
        board[i][j][k] = c - '0';
      }
  q.push({zs, {ys, xs}});

  while (!board[ze][xe][ye] && !q.empty()) {
    int y = q.front().second.first;
    int x = q.front().second.second;
    int z = q.front().first;
    int cur = board[z][x][y];
    q.pop();
    for (int dir = 0; dir < 6; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      int nz = z + dz[dir];
      if (board[nz][nx][ny]) continue;
      board[nz][nx][ny] = cur + 1;
      q.push({nz, {ny, nx}});
    }
  }
  if (board[ze][xe][ye])
    cout << board[ze][xe][ye];
  else
    cout << -1;

  return 0;
}
