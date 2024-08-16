#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
int T, N, W, H;
int board[15][12];
int cnt[12];

int ret;

void crush(int board[][12], int cnt[], int y, int x) {
  int power = board[y][x];
  if (power == 0) return;
  board[y][x] = 0;
  cnt[x]--;
  if (power == 1) return;
  for (int i = 1; i < power; i++) {
    if (x + i < W) crush(board, cnt, y, x + i);
    if (x - i >= 0) crush(board, cnt, y, x - i);
    if (y + i < H) crush(board, cnt, y + i, x);
    if (y - i >= 0) crush(board, cnt, y - i, x);
  }
}

void dfs(int board[][12], int cnt[], int bead) {
  if (ret == 0) return;
  int left = 0;
  for (int i = 0; i < W; i++) left += cnt[i];
  if (left < ret) ret = left;
  if (ret == 0) return;
  if (bead == 0) {
    return;
  }
  // 부수기
  for (int pos = 0; pos < W; pos++) {
    if (cnt[pos] == 0) continue;
    // 보드, 카운트 복사
    int board2[15][12] = {0};
    int cnt2[12];
    for (int i = 0; i < W; i++) {
      cnt2[i] = cnt[i];
      for (int j = 0; j < cnt[i]; j++) {
        board2[H - 1 - j][i] = board[H - 1 - j][i];
      }
    }
    // pos 위치 폭파
    crush(board2, cnt2, H - cnt[pos], pos);
    // 폭파 후 블럭 중력적용
    for (int x = 0; x < W; x++) {
      int bottom = 0, top = 0;
      while (bottom < cnt2[x]) {
        if (board2[H - 1 - top][x]) {
          board2[H - 1 - bottom][x] = board2[H - 1 - top][x];
          top++;
          bottom++;
        } else {
          top++;
        }
        if (top >= cnt[x]) break;  // 아마 필요없을거임
      }
    }
    // 다음경우로
    dfs(board2, cnt2, bead - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("input.txt", "r", stdin);
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N >> W >> H;
    ret = 2147483647;
    for (int i = 0; i < W; i++) cnt[i] = 0;
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) {
        cin >> board[i][j];
        if (board[i][j] > 0) cnt[j]++;
      }
    dfs(board, cnt, N);
    cout << "#" << test_case << " " << ret << "\n";
  }
  return 0;
}
