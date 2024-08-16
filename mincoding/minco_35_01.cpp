#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<char> pq;
  string s;
  cin >> s;
  for (char c : s) pq.push(c);
  while (!pq.empty()) {
    cout << pq.top();
    pq.pop();
  }

  return 0;
}