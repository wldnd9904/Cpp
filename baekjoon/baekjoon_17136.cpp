#include <iostream>
using namespace std;

bool board[10][10];
int paper[6] = {0, 5, 5, 5, 5, 5};
int ret = 2147483647;
void solve(int left, int y, int x) {
  if (left == 0) {
    int sum = 0;
    for (int i = 1; i <= 5; i++) {
      sum += 5 - paper[i];
    }
    ret = ret < sum ? ret : sum;
    return;
  }
  if (y >= 10) return;
  if (x >= 10) {
    solve(left, y + 1, 0);
    return;
  }
  if (board[y][x] == false) {
    solve(left, y, x + 1);
    return;
  }
  for (int i = 5; i > 0; i--) {
    if (paper[i] == 0) continue;
    bool canFill = true;
    for (int dy = 0; dy < i; dy++) {
      for (int dx = 0; dx < i; dx++) {
        if (y + dy >= 10 || x + dx >= 10 || board[y + dy][x + dx] == false) {
          canFill = false;
          break;
        }
      }
      if (!canFill) break;
    }
    if (!canFill) continue;
    for (int dy = 0; dy < i; dy++)
      for (int dx = 0; dx < i; dx++) board[y + dy][x + dx] = false;
    paper[i]--;
    solve(left - i * i, y, x + 1);
    paper[i]++;
    for (int dy = 0; dy < i; dy++)
      for (int dx = 0; dx < i; dx++) board[y + dy][x + dx] = true;
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int cnt = 0;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) {
      cin >> board[i][j];
      if (board[i][j]) cnt++;
    }
  solve(cnt, 0, 0);
  cout << (ret == 2147483647 ? -1 : ret) << "\n";
  return 0;
}