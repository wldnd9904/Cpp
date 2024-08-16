#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

pair<int, pair<int, int>> edges[10001];
pair<int, int> fields[1001];
bool isM[1001];
int parent[1001];
int findAncestor(int a) {
  if (parent[a] == a) return a;
  parent[a] = findAncestor(parent[a]);
  return parent[a];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    char c;
    cin >> c;
    isM[i] = c == 'M';
    parent[i] = i;
  }

  int edgeCnt = 0;
  for (int i = 0; i < M; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    if (isM[u] == isM[v]) continue;
    edges[edgeCnt++] = {d, {u, v}};
  }

  sort(edges, edges + edgeCnt);
  int sum = 0;

  for (int i = 0; i < edgeCnt; i++) {
    auto edge = edges[i];
    int from = edge.second.first;
    int to = edge.second.second;
    int cost = edge.first;
    int aF = findAncestor(from);
    int aT = findAncestor(to);
    if (aF != aT) {
      parent[aF] = aT;
      sum += cost;
    }
  }
  int unionId = findAncestor(1);
  for (int i = 2; i <= N; i++) {
    if (findAncestor(i) != unionId) {
      cout << -1;
      return 0;
    }
  }
  cout << sum;
  return 0;
}
