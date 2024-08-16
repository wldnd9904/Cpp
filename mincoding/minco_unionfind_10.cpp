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

int parent[100001];
int isGurnsey[100001];

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
  // 입력받기
  for (int i = 1; i <= N; i++) {
    parent[i] = i;
    char GH;
    cin >> GH;
    isGurnsey[i] = GH == 'G';
  }
  // 간선 연결하기
  for (int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    if (isGurnsey[a] != isGurnsey[b]) continue;
    if (a > b) swap(a, b);  // 작은게 부모
    int aA = findAncestor(a), aB = findAncestor(b);
    parent[aB] = aA;
  }
  // from~to 검사
  for (int i = 0; i < M; i++) {
    int from, to;
    char GH;
    cin >> from >> to >> GH;
    bool isG = GH == 'G';
    int aF = findAncestor(from);
    int aT = findAncestor(to);
    if (aF != aT) {
      cout << true;
    } else {
      cout << (isGurnsey[aF] == isG);
    }
  }
  return 0;
}
