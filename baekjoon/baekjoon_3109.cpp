#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
bool board[10002][501];
int R, C;
int ret = 0;

bool dfs(int y, int x) {
  if (board[y][x]) return false;
  board[y][x] = true;
  if (x == C) return true;
  return (dfs(y - 1, x + 1) || dfs(y, x + 1) || dfs(y + 1, x + 1));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> R >> C;
  for (int i = 0; i < C; i++) {
    board[0][i] = true;
    board[R + 1][i] = true;
  }

  for (int i = 1; i <= R; i++) {
    for (int j = 0; j < C; j++) {
      char c;
      cin >> c;
      board[i][j] = c == 'x';
    }
  }
  for (int y = 1; y <= R; y++)
    if (dfs(y, 0)) ret++;

  cout << ret;
  return 0;
}
