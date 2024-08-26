#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
struct node {
  int y, x, id;
};
int cnt;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
unordered_set<int> dp[402][402];
unordered_set<int> reserve[402][402];
bool available[402][402];
queue<node> q;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; ++test_case) {
    int N, M;
    cin >> N >> M;
    cnt = 0;
    // q = queue<node>();
    // 집들 입력받기
    for (int i = 1; i <= N; i++) {
      available[i][0] = false;
      available[0][i] = false;
      available[i][N + 1] = false;
      available[N + 1][i] = false;
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        available[i][j] = true;
        dp[i][j].clear();
        reserve[i][j].clear();
        bool house;
        cin >> house;
        if (house) {
          q.push({i, j, cnt});
          reserve[i][j].insert(cnt);
          cnt++;
        }
      }
    }

    // 서비스 영역이 K 일 때
    // 운영비용 = 면적 = K*K + (K-1)*(K-1)
    // 최대 거리 = (K-1)*2 -> 0, 2, 4, 6, ... -> 2로 나눈 거리 저장
    // N=20이면 최대거리가 38
    // 지불비용 = 집 수 * M;
    int ret;
    int K = 1;
    int cost = 1;
    int qSize = q.size();
    while (qSize) {
      size_t maxGroup = 0;
      while (qSize--) {
        int id = q.front().id;
        int y = q.front().y;
        int x = q.front().x;
        dp[y][x].insert(id);
        // cout << y << " " << x << " " << dp[y][x].size() << endl;
        maxGroup = max(maxGroup, dp[y][x].size());
        q.pop();
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (!available[ny][nx]) continue;
          if (reserve[ny][nx].insert(id).second)
            q.push({ny, nx, id});
          else
            continue;
        }
      }
      if (maxGroup * M >= cost) ret = maxGroup;
      // cout << K << " " << maxGroup << endl;
      K++;
      cost = K * K + (K - 1) * (K - 1);
      qSize = q.size();
    }
    cout << "#" << test_case << " " << ret << "\n";
  }

  return 0;
}