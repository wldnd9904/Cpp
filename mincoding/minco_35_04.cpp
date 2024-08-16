#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<int> pq;
  int N;
  cin >> N;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      int cost;
      cin >> cost;
      if (j <= i) continue;
      if (cost > 0) pq.push(-cost);
    }
  for (int i = 0; i < 9; i++) {
    int cur = pq.top();
    pq.pop();
    pq.push(cur * 2);
  }
  cout << -pq.top() * 2 << "만원";

  return 0;
}