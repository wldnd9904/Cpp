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

int parent[200001];  // 유니온 파인드용
int edge[200001];    // 간선 연결될 부모
bool cut[200001];    // true면 그 간선이 잘린것
int query[400001][3];
bool answer[200001];

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
  int N, Q;
  cin >> N >> Q;
  // 부모 입력
  for (int i = 1; i < N; i++) {
    parent[i] = i;
    cin >> edge[i + 1];
  }
  parent[N] = N;
  // 쿼리 저장 및 끊을 선 싹다 끊기
  for (int i = 0; i < N + Q; i++) {
    cin >> query[i][0];
    if (query[i][0] == 0) {
      cin >> query[i][1];
      cut[query[i][1]] = true;
    }

    if (query[i][0] == 1) {
      cin >> query[i][1] >> query[i][2];
    }
  }
  // 쿼리 역으로 돌기
  int answerCnt = 0;
  for (int i = N + Q - 1; i >= 0; i--) {
    if (query[i][0] == 0) {
      int aA = findAncestor(query[i][1]);
      int aB = findAncestor(edge[query[i][1]]);
      parent[aA] = aB;
    } else {
      int aA = findAncestor(query[i][1]);
      int aB = findAncestor(query[i][2]);
      answer[answerCnt++] = aA == aB;
    }
  }
  // 답변 목록 역으로 출력
  while (answerCnt) {
    cout << (answer[--answerCnt] ? "YES" : "NO") << "\n";
  }

  return 0;
}
