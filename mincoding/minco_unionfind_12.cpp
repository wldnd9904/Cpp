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

int parent[100001];  // 유니온 파인드용
long long cnt[100001];
int edge[100001][2];  // 간선
bool cut[100001];     // true면 그 간선이 잘린것
int query[100001];    // 자를 간선 번호

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
  int N, M, Q;
  cin >> N >> M >> Q;
  // 부모 초기화
  for (int i = 1; i <= N; i++) {
    parent[i] = i;
    cnt[i] = 1;
  }
  // 간선 입력받기
  for (int i = 1; i <= M; i++) {
    cin >> edge[i][0] >> edge[i][1];
  }
  // 쿼리 저장 및 끊을 선 싹다 끊기
  for (int i = 0; i < Q; i++) {
    cin >> query[i];
    cut[query[i]] = true;
  }
  // 제거 안 된 간선들 연결하기
  for (int i = 1; i <= M; i++) {
    if (cut[i]) continue;
    int aA = findAncestor(edge[i][0]);
    int aB = findAncestor(edge[i][1]);
    if (aA == aB) continue;
    parent[aA] = aB;
    cnt[aB] += cnt[aA];
  }
  // 쿼리 역으로 돌면서 연결
  long long ret = 0;
  for (int i = Q - 1; i >= 0; i--) {
    int aA = findAncestor(edge[query[i]][0]);
    int aB = findAncestor(edge[query[i]][1]);
    if (aA == aB) continue;
    parent[aA] = aB;
    ret += cnt[aA] * cnt[aB];
    cnt[aB] += cnt[aA];
  }
  cout << ret;
  return 0;
}
