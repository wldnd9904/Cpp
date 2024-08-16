#include <iostream>
using namespace std;
int board[11][11];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    int N;
    int acY, acX;
    int cnt = 0;
    cin >> N;
    for (int i = 0; i <= N; i++)
      for (int j = 0; j <= N; j++) {
        cin >> board[i][j];
        if (board[i][j] == 1) cnt++;
        if (board[i][j] == 2) {
          acY = i;
          acX = j;
        }
      }
    int ret = 1;
    int tmpCnt;
    for (; ret < 100; ret++) {
      tmpCnt = cnt;
      for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
          if (board[i][j] == 1) {
            if ((acY - i) * (acY - i) + (acX - j) * (acX - j) <= (ret * ret))
              tmpCnt--;
          }
        }
      }
      if (tmpCnt == 0) break;
    }
    cout << "#" << test_case << " " << ret << "\n";
  }
}