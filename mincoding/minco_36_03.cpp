#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M, P;
  cin >> N >> M >> P;
  long long dist[1001];               // 마을에서 다른곳으로
  long long dist2[1001];              // 다른곳에서 마을로
  priority_queue<pair<int, int>> pq;  // -거리, 정점
  vector<vector<pair<int, int>>> v(
      N + 1, vector<pair<int, int>>());  // v[출발지][n] = 목적지, 거리
  vector<vector<pair<int, int>>> v2(
      N + 1, vector<pair<int, int>>());  // v[목적지][n] = 출발지, 거리
  for (int i = 0; i < M; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
    v2[to].push_back({from, cost});
  }

  for (int j = 1; j <= N; j++) {
    dist[j] = 99999999999;
    dist2[j] = 99999999999;
  }
  pq.push({-0, P});
  dist[P] = 0;
  while (!pq.empty()) {
    int curDist = -pq.top().first;
    int curNode = pq.top().second;
    pq.pop();
    for (auto next : v[curNode]) {
      if (curDist + next.second < dist[next.first]) {
        dist[next.first] = curDist + next.second;
        pq.push({-(curDist + next.second), next.first});
      }
    }
  }
  pq = priority_queue<pair<int, int>>();
  pq.push({-0, P});
  dist2[P] = 0;
  while (!pq.empty()) {
    int curDist = -pq.top().first;
    int curNode = pq.top().second;
    pq.pop();
    for (auto next : v2[curNode]) {
      if (curDist + next.second < dist2[next.first]) {
        dist2[next.first] = curDist + next.second;
        pq.push({-(curDist + next.second), next.first});
      }
    }
  }
  int ret = 0;
  for (int i = 1; i <= N; i++) {
    if (i == P) continue;
    if (dist[i] + dist2[i] > ret) ret = dist[i] + dist2[i];
  }
  cout << ret << "\n";
  return 0;
}
