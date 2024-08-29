#include <iostream>
#include <queue>
using namespace std;

int ret[200000];
int rightLine[4] = {3, 0, 1, 2};
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
    pq[4];  // A,B,C,D
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int t;
    char w;
    cin >> t >> w;
    pq[w - 'A'].push({t, i});
    ret[i] = -1;
  }
  int time = -1;
  while (true) {
    // 현재시간 결정 - time보다 늦게 온 애들만 있으면 그중 최솟값
    time++;
    int minTime = 2147483647;
    for (int i = 0; i < 4; i++) {
      if (pq[i].empty()) continue;
      minTime = min(minTime, pq[i].top().first);
    }
    if (minTime == 2147483647) break;
    time = max(time, minTime);
    // 4개 도로 중 출발 가능한 도로 탐색
    bool canGo[4] = {false};
    for (int i = 0; i < 4; i++) {
      if (pq[i].empty() || pq[i].top().first > time) continue;
      if (pq[rightLine[i]].empty() || pq[rightLine[i]].top().first > time)
        canGo[i] = true;
    }
    if (canGo[0] + canGo[1] + canGo[2] + canGo[3] == 0) break;
    for (int i = 0; i < 4; i++) {
      if (!canGo[i]) continue;
      ret[pq[i].top().second] = time;
      pq[i].pop();
    }
  }
  for (int i = 0; i < N; i++) {
    cout << ret[i] << "\n";
  }
  return 0;
}
