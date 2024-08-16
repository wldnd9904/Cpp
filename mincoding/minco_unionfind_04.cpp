#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
int N, T;
int parent[26];
int people[26];
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
  for (int i = 0; i < N; i++) {
    parent[i] = i;
    cin >> people[i];
  }
  cin >> T;
  for (int i = 0; i < T; i++) {
    string situation;
    char a, b;
    cin >> situation;
    cin >> a >> b;
    int aA = findAncestor(a - 65);
    int aB = findAncestor(b - 65);
    if (situation == "alliance") {
      if (aA == aB) continue;
      parent[aA] = aB;
      people[aB] += people[aA];

    } else {
      if (people[aA] > people[aB])
        people[aB] = 0;
      else if (people[aA] < people[aB])
        people[aA] = 0;
      else
        people[aA] = people[aB] = 0;
    }
  }
  int cnt = 0;
  for (int i = 0; i < N; i++)
    if (people[findAncestor(i)]) cnt++;

  cout << cnt;
  return 0;
}
