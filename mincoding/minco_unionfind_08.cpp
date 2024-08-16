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
int T, N;

int parent[3001];
int x[3001];
int y[3001];
int r[3001];
int cnt;

int findAncestor(int a) {
  if (parent[a] == 0) return 0;
  if (parent[a] != a) parent[a] = findAncestor(parent[a]);
  return parent[a];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T;
  for (int test_case = 0; test_case < T; test_case++) {
    cin >> N;
    cnt = N;
    for (int i = 0; i < N; i++) {
      parent[i] = i;
      cin >> x[i] >> y[i] >> r[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j) continue;
        int ai = findAncestor(i);
        int aj = findAncestor(j);
        if (ai == aj)
          continue;
        else {
          int dx = x[i] - x[j];
          int dy = y[i] - y[j];
          int dr = r[i] + r[j];
          if (dr * dr >= dx * dx + dy * dy) {
            parent[ai] = aj;
            cnt--;
          }
        }
      }
    }
    cout << cnt << "\n";
  }
  return 0;
}
