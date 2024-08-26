#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, T;
  cin >> N >> T;
  long long dist[20000];
  priority_queue<pair<int, int>> pq;  // -거리, 정점
  vector<vector<pair<int, int>>> v(
      N, vector<pair<int, int>>());  // v[출발지][n] = 목적지, 거리
  for (int i = 0; i < N; i++) {
    dist[i] = 99999999999;
  }
  for (int i = 0; i < T; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
  }
  pq.push({-0, 0});
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
  if (dist[N - 1] == 99999999999)
    cout << "impossible";
  else
    cout << dist[N - 1];
  return 0;
}
