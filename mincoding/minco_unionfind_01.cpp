#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
int N, Q;
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
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    parent[i] = i;
  }
  for (int i = 0; i < Q; i++) {
    int K, A, B;
    cin >> K >> A >> B;
    if (K) {
      parent[findAncestor(B)] = findAncestor(A);
    } else {
      cout << (findAncestor(A) == findAncestor(B) ? "YES" : "NO") << "\n";
    }
  }
  return 0;
}
