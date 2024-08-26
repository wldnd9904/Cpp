#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M, K;
  cin >> N >> M >> K;
  int A, B;  // 출발지, 목적지
  cin >> A >> B;
  long long dist[1001];
  priority_queue<pair<int, int>> pq;  // -거리, 정점
  vector<vector<pair<int, int>>> v(
      N + 1, vector<pair<int, int>>());  // v[출발지][n] = 목적지, 거리
  for (int i = 0; i < M; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
    v[to].push_back({from, cost});
  }
  int raising = 0;
  for (int i = 0; i <= K; i++) {
    if (i != 0) {
      int a;
      cin >> a;
      raising += a;
    }
    for (int j = 1; j <= N; j++) {
      dist[j] = 99999999999;
    }
    pq = priority_queue<pair<int, int>>();
    pq.push({-0, A});
    dist[A] = 0;
    while (!pq.empty()) {
      int curDist = -pq.top().first;
      int curNode = pq.top().second;
      pq.pop();
      for (auto next : v[curNode]) {
        if (curDist + raising + next.second < dist[next.first]) {
          dist[next.first] = curDist + raising + next.second;
          pq.push({-(curDist + raising + next.second), next.first});
        }
      }
    }
    cout << dist[B] << "\n";
  }
  return 0;
}
