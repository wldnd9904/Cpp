#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
int N;
int parent[26];
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
  // freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 0; i < 26; i++) {
    parent[i] = i;
  }
  for (int i = 0; i < N; i++) {
    char a, b;
    cin >> a >> b;
    int aA = findAncestor(a - 65);
    int aB = findAncestor(b - 65);
    if (aA == aB)
      continue;
    else
      parent[aA] = aB;
  }
  bool team[26] = {false};
  for (int i = 0; i < 26; i++) {
    int aI = findAncestor(i);
    if (aI != i) team[aI] = true;
  }
  int indiCnt = 0, teamCnt = 0;
  for (int i = 0; i < 26; i++) {
    if (team[i]) teamCnt++;
    if (parent[i] == i && !team[i]) indiCnt++;
  }
  cout << teamCnt << "\n" << indiCnt;
  return 0;
}
