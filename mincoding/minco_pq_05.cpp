#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct print {
  int id;
  int timeArrived;
  int timeEating;
};

struct cmpTime {
  bool operator()(const print& a, const print& b) const {
    return a.timeArrived > b.timeArrived;
  }
};
struct cmpId {
  bool operator()(const print& a, const print& b) const { return a.id > b.id; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<print, vector<print>, cmpTime> pqTime;
  priority_queue<print, vector<print>, cmpId> pqId;
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
    if (pqId.empty() && pqTime.top().timeArrived > t)
      t = pqTime.top().timeArrived;

    while (!pqTime.empty() && pqTime.top().timeArrived <= t) {
      pqId.push(pqTime.top());
      pqTime.pop();
    }
    print cur = pqId.top();
    pqId.pop();
    maxTimeWaited = max(maxTimeWaited, t - cur.timeArrived);
    t += cur.timeEating;
  }
  cout << maxTimeWaited;
  return 0;
}