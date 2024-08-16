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

int parent[10001];
pair<int, pair<int, int>> edges[100001];

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
  int V, E;
  cin >> V >> E;
  for (int i = 1; i <= V; i++) {
    parent[i] = i;
  }
  for (int i = 0; i < E; i++) {
    int A, B, C;
    cin >> A >> B >> C;
    edges[i] = {C, {A, B}};
  }
  int sum = 0;
  sort(edges, edges + E);
  for (int i = 0; i < E; i++) {
    int from = edges[i].second.first;
    int to = edges[i].second.second;
    int cost = edges[i].first;
    int aF = findAncestor(from);
    int aT = findAncestor(to);
    if (aF != aT) {
      parent[aF] = aT;
      sum += cost;
    }
  }
  cout << sum;
  return 0;
}
