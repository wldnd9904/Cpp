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
int parent[100002] = {0};  // 0이면 한번도 안 쓴 노드, 자기자신이면 한번 쓴
                           // 노드, 둘다 아니면 부모가 있는거
int findAncestor(int a) {
  if (parent[a] == 0) return 0;
  if (parent[a] != a) parent[a] = findAncestor(parent[a]);
  return parent[a];
}

void fill(int car) {
  parent[car] = car;
  // 오른쪽칸이 차있으면 합치기
  int ancP1 = parent[car + 1];
  if (ancP1) parent[ancP1] = car;

  // 왼쪽칸이 차있으면 그것도 합치기
  int ancM1 = findAncestor(car - 1);
  if (ancM1) parent[car] = ancM1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T >> N;
  for (int i = 1; i <= N; i++) {
    int car;
    cin >> car;
    int anc = findAncestor(car);
    // 비어있던 칸이라면
    if (anc == 0) {
      fill(car);
      // 이미 차있었다면
    } else {
      int nextCar = anc - 1;
      if (nextCar > 0)
        fill(nextCar);
      else {
        cout << i - 1;
        return 0;
      }
    }
  }
  cout << N;
  return 0;
}
