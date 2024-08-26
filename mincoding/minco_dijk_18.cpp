#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  // cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int test_case;
  cin >> test_case;
  while (test_case--) {
    int N, M, T;  // 지점 수, 도로 수, 목적지 후보 수
    cin >> N >> M >> T;
    int S, G, H;  // 출발지, 지나가는 점 두개
    cin >> S >> G >> H;

    vector<vector<pair<int, int>>> v(N + 1);
    vector<int> dist1(N + 1, 2147483647);
    vector<int> usedGH(N + 1, -1);
    for (int i = 0; i < M; i++) {
      int A, B, D;
      cin >> A >> B >> D;
      v[A].push_back({B, D});
      v[B].push_back({A, D});
    }

    // 그냥 다익스트라 돌리기
    priority_queue<pair<int, int>> pq;
    pq.push({0, S});
    dist1[S] = 0;
    usedGH[S] = 0;
    while (!pq.empty()) {
      int cur = pq.top().second;
      int curDist = -pq.top().first;
      // cout << "[" << usedGH[cur] << "]";
      pq.pop();
      if (curDist > dist1[cur]) continue;
      for (auto& next : v[cur]) {
        int n = next.first;
        int ndist = curDist + next.second;
        if (ndist <= dist1[n]) {
          dist1[n] = ndist;
          // cout << cur << " " << n << " " << ndist << " " << usedGH[n] <<
          // endl;
          usedGH[n] = usedGH[cur];
          if (cur == G && n == H || cur == H && n == G) usedGH[n] = 1;
          pq.push({-ndist, n});
        }
      }
    }

    vector<int> cand;

    for (int i = 0; i < T; i++) {
      int a;
      cin >> a;
      // cout << a << ": " << usedGH[a] << " ";
      if (usedGH[a]) cand.push_back(a);
    }
    sort(cand.begin(), cand.end());
    for (int a : cand) cout << a << " ";
    cout << "\n";
  }
  return 0;
}
