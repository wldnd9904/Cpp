#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
int N;
int parent[1001];
int findAncestor(int a) {
  int cur = parent[a];
  while (parent[cur] != cur) {
    cur = parent[cur];
  }
  parent[a] = cur;
  return cur;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 0; i < N; i++) parent[i] = i;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      bool linked;
      cin >> linked;
      if (i <= j) continue;
      if (linked) {
        int ai = findAncestor(i);
        int aj = findAncestor(j);
        if (ai == aj) {
          cout << "WARNING";
          return 0;
        }
        parent[ai] = aj;
      }
    }
  cout << "STABLE";
  return 0;
}
