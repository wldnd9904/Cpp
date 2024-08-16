#include <iostream>
#include <queue>
#include <string>
using namespace std;
int board[10][10];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<pair<int, pair<int, int>>> pq;
  int N;
  cin >> N;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      int cost;
      cin >> cost;
      pq.push({cost, {i, j}});
    }
  for (int i = 0; i < 3; i++) {
    cout << char('A' + pq.top().second.first) << "-"
         << char('A' + pq.top().second.second) << " " << pq.top().first << "\n";
    pq.pop();
  }

  return 0;
}