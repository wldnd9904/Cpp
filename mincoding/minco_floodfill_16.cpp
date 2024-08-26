#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int N, M;
int board[502][502] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];

  int y, x;
  cin >> y >> x;
  int day = 0, cnt = 0;
  int maxDay, maxCnt = 0;
  queue<pair<int, int>> q;
  priority_queue<int, vector<int>, greater<int>> pq;
  q.push({y + 1, x + 1});
  pq.push(1 + board[y + 1][x + 1]);
  board[y + 1][x + 1] = 0;
  while (!pq.empty()) {
    day++;
    while (!pq.empty() && pq.top() <= day) pq.pop();
    if (pq.size() > maxCnt) {
      maxCnt = pq.size();
      maxDay = day;
    }
    int qSize = q.size();
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx] == 0) continue;
        q.push({ny, nx});
        pq.push(day + 1 + board[ny][nx]);
        board[ny][nx] = 0;
      }
    }
    if (q.size() == 0) {
      day = pq.top() - 1;
    }
  }
  cout << maxDay << "일\n";
  cout << maxCnt << "개";

  return 0;
}
