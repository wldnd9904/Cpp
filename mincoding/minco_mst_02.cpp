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

priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
               greater<pair<int, pair<int, int>>>>
    edges;
pair<int, int> fields[2001];
int parent[2001];
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
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> fields[i].first >> fields[i].second;
    parent[i] = i;
  }
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      int dy = fields[i].first - fields[j].first;
      int dx = fields[i].second - fields[j].second;
      int cost = dy * dy + dx * dx;
      if (cost >= K) edges.push({cost, {i, j}});
    }
  }
  int sum = 0;
  while (!edges.empty()) {
    auto edge = edges.top();
    edges.pop();
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
  int unionId = findAncestor(0);
  for (int i = 1; i < N; i++) {
    if (findAncestor(i) != unionId) {
      cout << -1;
      return 0;
    }
  }
  cout << sum;
  return 0;
}
