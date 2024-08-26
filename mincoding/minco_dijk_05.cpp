#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;

struct node {
  int dist, cur;
  bool pickedUp;
};

struct cmp {
  bool operator()(node& a, node& b) {
    if (a.dist == b.dist) return a.pickedUp < b.pickedUp;
    return a.dist > b.dist;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int V, E, P;
  cin >> V >> E >> P;
  int dist[5001];
  dist[1] = 0;
  for (int i = 2; i <= V; i++) {
    dist[i] = 2147483647;
  }
  vector<vector<pair<int, int>>> v(V + 1);  // 목적지, 거리

  for (int i = 0; i < E; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
    v[to].push_back({from, cost});
  }

  priority_queue<node, vector<node>, cmp> pq;  // 거리, {위치,민철픽업여부}
  pq.push({0, 1, P == 1});
  while (!pq.empty()) {
    int curDist = pq.top().dist;
    int cur = pq.top().cur;
    bool pickedUp = pq.top().pickedUp;

    if (cur == V) {
      if (pickedUp)
        cout << "OKAY";
      else
        cout << "SORRY";
      return 0;
    }

    pq.pop();
    for (auto next : v[cur]) {
      if (dist[next.first] < curDist + next.second) continue;
      int nPickedUp = pickedUp;
      if (next.first == P) nPickedUp = true;
      dist[next.first] = curDist + next.second;
      pq.push({curDist + next.second, next.first, nPickedUp});
    }
  }
  cout << "SORRY";
  return 0;
}
