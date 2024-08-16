#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>
using namespace std;
int N, width;
int parent[1000001] = {0};
int groupSize[1000001] = {0};
int maxSize = 0;
int cnt = 0;
set<int> s;
bool stone[1000001] = {false};
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
  cin >> width >> N;
  for (int i = 0; i < N; i++) {
    int pos;
    cin >> pos;
    stone[pos] = true;
    if (stone[pos - 1] && stone[pos + 1]) {
      int aPosP1 = findAncestor(pos + 1);
      int aPosM1 = findAncestor(pos - 1);
      parent[pos] = aPosM1;
      parent[aPosP1] = aPosM1;
      parent[pos + 1] = aPosM1;
      groupSize[aPosM1] += groupSize[aPosP1] + 1;
      maxSize = max(maxSize, groupSize[aPosM1]);
      cnt--;
    } else if (stone[pos - 1]) {
      int aPosM1 = findAncestor(pos - 1);
      parent[pos] = aPosM1;
      groupSize[aPosM1]++;
      maxSize = max(maxSize, groupSize[aPosM1]);
    } else if (stone[pos + 1]) {
      int aPosP1 = findAncestor(pos + 1);
      parent[pos] = aPosP1;
      groupSize[aPosP1]++;
      maxSize = max(maxSize, groupSize[aPosP1]);
    } else {
      parent[pos] = pos;
      groupSize[pos] = 1;
      maxSize = max(maxSize, groupSize[pos]);
      cnt++;
    }
    cout << cnt << " " << maxSize << "\n";
  }
  return 0;
}
