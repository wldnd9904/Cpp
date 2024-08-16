#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<long long> pq;
  int Q;
  cin >> Q;
  long long numbers[1501];
  int cnt = 0;
  pq.push(-1);
  long long lastone = 0;
  while (cnt <= 1500) {
    long long cur = pq.top();
    pq.pop();
    if (cur == lastone) continue;
    lastone = cur;
    // cout << lastone << endl;

    pq.push(cur * 2);
    pq.push(cur * 3);
    pq.push(cur * 5);
    numbers[cnt] = -cur;
    cnt++;
  }
  for (int i = 0; i < Q; i++) {
    int query;
    cin >> query;
    cout << numbers[query - 1] << " ";
  }
  return 0;
}