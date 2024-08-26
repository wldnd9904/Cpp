#include <stdlib.h>

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  int prev[1001] = {0};
  int minCost[1001] = {0};
  bool visited[1001] = {0};

  vector<vector<pair<int, int>>> v(N + 1);  // 다음코스, 비용
  for (int i = 2; i <= N; i++) {
    minCost[i] = 2147483647;
  }
  for (int i = 0; i < M; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    v[from].push_back({to, cost});
  }
  queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int cur = q.front();
    int curCost = minCost[q.front()];
    q.pop();
    for (auto n : v[cur]) {
      int cost = n.second;
      int next = n.first;
      if (curCost + cost < minCost[next]) {
        minCost[next] = (curCost + cost);
        prev[next] = cur;
      }
      if (visited[next]) continue;
      visited[next] = true;
      q.push(next);
    }
  }
  stack<int> s;
  int cur = N;
  int maxMaxCost = 0;
  while (cur) {
    s.push(cur);
    maxMaxCost = max(maxMaxCost, minCost[cur] - minCost[prev[cur]]);
    cur = prev[cur];
  }
  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << "\n" << maxMaxCost;
  return 0;
}
