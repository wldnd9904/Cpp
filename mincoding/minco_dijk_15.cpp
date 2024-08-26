#include <stdlib.h>

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int N;
int heartCnt;
int board[302][302];
int visited[302][302];
int bfsCnt = 0;
int firstHeartY, firstHeartX;

bool canCollectAllHeart(
    int power) {  // power이하의 몬스터가 있는 곳만 지나갈 수 있음
  int heartLeft = heartCnt - 1;
  bfsCnt++;
  queue<pair<int, int>> q;
  q.push({firstHeartY, firstHeartX});
  visited[firstHeartY][firstHeartX] = bfsCnt;
  while (heartLeft && !q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (visited[ny][nx] == bfsCnt) continue;
      if (board[ny][nx] == -1) continue;
      if (board[ny][nx] > power) continue;
      visited[ny][nx] = bfsCnt;
      if (board[ny][nx] == 0) heartLeft--;
      if (heartLeft == 0) break;
      q.push({ny, nx});
    }
  }
  return heartLeft == 0;
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
    bool foundFirstHeart = false;
    heartCnt = 0;
    for (int i = 1; i <= N; i++) {
      board[i][0] = -1;
      board[i][N + 1] = -1;
      board[N + 1][i] = -1;
      board[0][i] = -1;
      for (int j = 1; j <= N; j++) {
        cin >> board[i][j];
        if (board[i][j] == 0) heartCnt++;
        if (!foundFirstHeart && board[i][j] == 0) {
          firstHeartY = i;
          firstHeartX = j;
          foundFirstHeart = true;
        }
      }
    }
    int left = 1, right = 101;  // [left, right)
    while (left != right) {
      int mid = right - (right - left) / 2;
      if (canCollectAllHeart(mid))
        right = mid - 1;
      else
        left = mid;
    }
    cout << "#" << test_case << " " << left + 1 << "\n";
  }
  return 0;
}
