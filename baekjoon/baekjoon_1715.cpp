#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  int sum = 0;
  priority_queue<int> pq;
  for (int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    pq.push(-tmp);
  }
  while (true) {
    int a = -pq.top();
    pq.pop();
    if (pq.empty()) break;
    int b = -pq.top();
    pq.pop();
    sum -= a + b;
    pq.push(-(a + b));
  }
  cout << -sum;
  return 0;
}