#include <stdlib.h>

#include <iostream>
#include <queue>
#include <stack>
using namespace std;
struct node {
  int cur;
  int cost;
  int power;
};
struct cmp {
  bool operator()(node &a, node &b) {
    if (a.cost == 0) return true;
    if (b.cost == 0) return false;
    return (double)a.power / a.cost < (double)b.power / b.cost;
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  bool visited[1001] = {0};

  vector<vector<pair<int, pair<int, int>>>> v(N + 1);  // 다음코스, {비용, 수압}

  for (int i = 0; i < M; i++) {
    int from, to, cost, power;
    cin >> from >> to >> cost >> power;
    v[from].push_back({to, {cost, power}});
    v[to].push_back({from, {cost, power}});
  }
  priority_queue<node, vector<node>, cmp> pq;
  pq.push({1, 0, 1000});
  while (!pq.empty()) {
    int cur = pq.top().cur;
    int curCost = pq.top().cost;
    int curPower = pq.top().power;
    pq.pop();
    if (visited[cur]) continue;
    visited[cur] = true;
    if (cur == N) {
      cout << int(double(curPower) / curCost * 1000000);
    }
    for (auto n : v[cur]) {
      int next = n.first;
      if (visited[next]) continue;
      int cost = n.second.first + curCost;
      int power = min(n.second.second, curPower);
      pq.push({next, cost, power});
    }
  }
  return 0;
}