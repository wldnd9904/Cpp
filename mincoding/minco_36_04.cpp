#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int C, P, K, A, B;
  cin >> C >> P >> K >> A >> B;
  int dist[100001];                   // K에서 다른곳으로
  int dist2[100001];                  // A에서 다른곳으로
  priority_queue<pair<int, int>> pq;  // -거리, 정점
  vector<vector<pair<int, int>>> v(
      P + 1, vector<pair<int, int>>());  // v[출발지][n] = 목적지, 거리
  for (int i = 0; i < C; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
    v[to].push_back({from, cost});
  }

  for (int j = 1; j <= P; j++) {
    dist[j] = 2147483647;
    dist2[j] = 2147483647;
  }
  pq.push({-0, K});
  dist[K] = 0;
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
  pq.push({-0, A});
  dist2[A] = 0;
  while (!pq.empty()) {
    int curDist = -pq.top().first;
    int curNode = pq.top().second;
    pq.pop();
    for (auto next : v[curNode]) {
      if (curDist + next.second < dist2[next.first]) {
        dist2[next.first] = curDist + next.second;
        pq.push({-(curDist + next.second), next.first});
      }
    }
  }

  int ret = min(dist[A], dist[B]) + dist2[B];
  cout << ret << "\n";
  return 0;
}
