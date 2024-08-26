#include <iostream>
using namespace std;
int N;
bool board[500][500];

void fillToCeil(int y, int x, int stackCnt) {
  for (int i = y; i >= 0; i--) {
    if (stackCnt) {
      board[i][x] = true;
      stackCnt--;
    } else {
      board[i][x] = false;
    }
  }
}

int countStack(int y, int x) {
  int ret = 0;
  for (int i = y; i < N; i++) {
    if (!board[i][x]) return ret;
    ret++;
  }
  return ret;
}

void hagang(int y, int x, double power, int stackCnt) {
  if (y == N - 1) {
    fillToCeil(y, x, stackCnt);
    return;
  }
  if (board[y + 1][x]) {
    int resist = countStack(y + 1, x);
    if (power > resist) {
      hagang(y + resist, x, (power + resist), stackCnt + resist);
    } else {
      fillToCeil(y, x, stackCnt);
      return;
    }
  } else {
    hagang(y + 1, x, power * 1.9, stackCnt);
  }
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
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) cin >> board[i][j];

    for (int i = 0; i < N; i++)
      if (board[0][i]) hagang(0, i, 1, 1);

    bool tmp[500][500];

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) tmp[j][i] = board[i][j];

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) board[i][j] = tmp[i][j];

    for (int i = 0; i < N; i++)
      if (board[0][i]) hagang(0, i, 1, 1);

    int ret1 = 0;
    int ret2 = 0;
    for (int i = 0; i < N; i++) {
      if (board[i][N - 1]) ret1++;
      if (board[N - 1][i]) ret2++;
    }

    cout << "#" << test_case << " " << ret1 << " " << ret2 << "\n";
  }
  return 0;
}
