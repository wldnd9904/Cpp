#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct man {
  int id;
  int timeVisited;
  int timeEating;
};

struct cmpTime {
  bool operator()(const man& a, const man& b) const {
    return a.timeVisited > b.timeVisited;
  }
};
struct cmpId {
  bool operator()(const man& a, const man& b) const { return a.id > b.id; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<man, vector<man>, cmpTime> pqTime;
  priority_queue<man, vector<man>, cmpId> pqId;
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int a, t;
    cin >> a >> t;
    pqTime.push({i, a, t});
  }

  int t = 0;
  int maxTimeWaited = 0;

  while (!pqTime.empty() || !pqId.empty()) {
    if (pqId.empty() && pqTime.top().timeVisited > t)
      t = pqTime.top().timeVisited;

    while (!pqTime.empty() && pqTime.top().timeVisited <= t) {
      pqId.push(pqTime.top());
      pqTime.pop();
    }
    man cur = pqId.top();
    pqId.pop();
    maxTimeWaited = max(maxTimeWaited, t - cur.timeVisited);
    // cout << t << " " << cur.id << " " << cur.timeVisited << " "
    //      << cur.timeEating << endl;
    t += cur.timeEating;
  }
  cout << maxTimeWaited;
  return 0;
}