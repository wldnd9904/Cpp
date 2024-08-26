#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  vector<vector<pair<int, int>>> v(N + 1);
  for (int i = 0; i < M; i++) {
    int A, B, C, D, E;
    cin >> A >> B >> C >> D >> E;
    int cost = C;
    if (E > 10) cost += (E - 10) * D;
    v[A].push_back({B, cost});
  }

  priority_queue<pair<int, pair<int, int>>>
      pq;  // -비용, -방문한 도시 수, 현재도시
  pq.push({0, {-1, 1}});
  bool visited[101] = {false};
  while (!pq.empty()) {
    int curDist = -pq.top().first;
    int curCnt = -pq.top().second.first;
    int cur = pq.top().second.second;
    pq.pop();
    if (visited[cur]) continue;
    visited[cur] = true;
    if (cur == N) {
      cout << curDist << " " << curCnt;
      return 0;
    }
    for (auto next : v[cur]) {
      if (visited[next.first]) continue;
      pq.push({-(curDist + next.second), {-(curCnt + 1), next.first}});
    }
  }
  cout << -1;
  return 0;
}
