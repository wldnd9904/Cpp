#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
struct node {
  int y, x, dir;
};
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int dp[402][402];
int available[402][402];
queue<node> q;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; ++test_case) {
    q = queue<node>();
    int N, M;
    cin >> N >> M;
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
        bool house;
        cin >> house;
        dp[i][j] = house;
        if (house) {  // 퍼져나가면서 하나씩 올릴 예정
          q.push({i - 1, j, 0});
          q.push({i + 1, j, 1});
          q.push({i, j - 1, 2});
          q.push({i, j + 1, 3});
        }
      }
    }
    // 서비스 영역이 K 일 때
    // 운영비용 = 면적 = K*K + (K-1)*(K-1)
    // 최대 거리 = (K-1)*2 -> 0, 2, 4, 6, ... -> 2로 나눈 거리 저장
    // N=20이면 최대거리가 38
    // 지불비용 = 집 수 * M;
    int ret = 1;
    int K = 2;
    int cost = 5;
    int qSize = q.size();
    while (qSize) {
      int maxGroup = 0;
      while (qSize--) {
        int y = q.front().y;
        int x = q.front().x;
        int dir = q.front().dir;
        q.pop();
        if (!available[y][x]) continue;
        dp[y][x]++;
        maxGroup = max(maxGroup, dp[y][x]);

        int ny = y + dy[dir];
        int nx = x + dx[dir];
        q.push({ny, nx, dir});
        if (dir >= 2) continue;  // 좌우면 한칸 전진하고 끝
        q.push({y, x - 1, 2});   // 상하면 좌우로 새끼낳기
        q.push({y, x + 1, 3});
      }
      if (maxGroup * M >= cost) {
        ret = maxGroup;
      }
      K++;
      cost = K * K + (K - 1) * (K - 1);
      qSize = q.size();
      if (K == N + 2) {
        break;
      }
    }
    cout << "#" << test_case << " " << ret << "\n";
  }

  return 0;
}