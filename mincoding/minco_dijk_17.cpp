#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct edge {
  int from;
  int to;
  int cost;
  int criticalEdgeId;
  bool disabled = false;
};
int criticalEdgeIdCnt = 1;

priority_queue<pair<int, int>> pq;  // -비용, 현위치
int dist[1001] = {0};               // 1에서 출발하는 거리
int dist3[1001] = {0};              // N에서 출발하는 거리
bool critical[1001] = {false};      // 최단거리에 속한 노드들
int criticalEdgeId[1010] = {
    0};  // 이 노드 번호로 들어오는 최단거리 간선의 id (두개 이상일 수 있음)
int maxDist;
vector<vector<edge*>> v;

int N, M;

int dijk() {
  pq = priority_queue<pair<int, int>>();  // -비용, 현위치
  pq.push({0, 1});
  vector<int> dist4(N + 1, 2147483647);
  dist4[1] = 0;
  while (!pq.empty()) {
    // for (int i = 1; i <= N; i++) cout << dist4[i] << " ";
    // cout << endl;
    int cur = pq.top().second;
    int curDist = -pq.top().first;
    pq.pop();
    if (cur == N) return dist4[N];
    if (curDist > dist4[cur]) continue;
    for (auto next : v[cur]) {
      if (next->disabled) {
        // cout << next->from << ", " << next->to << " disabled" << endl;
        continue;
      }
      int n = next->to == cur ? next->from : next->to;
      int ndist = curDist + next->cost;
      if (dist4[n] <= ndist) {
        continue;
      }
      dist4[n] = ndist;
      pq.push({-ndist, n});
    }
  }
  // for (int i = 1; i <= N; i++) cout << dist4[i] << " ";
  // cout << endl;
  // cout << dist4[N] << endl;
  return dist4[N];
}

void process(int cur) {
  vector<int> distList;
  cout << endl;
  cout << cur << ": ";
  for (auto prevNode : v[cur]) {
    auto to = prevNode->to == cur ? prevNode->from : prevNode->to;
    if (critical[to] && criticalEdgeId[cur] == prevNode->criticalEdgeId) {
      cout << "prev(" << to << ") ";
      continue;
    }

    // if (critical[to] && criticalEdgeId[to] == prevNode->criticalEdgeId) {
    //   cout << "next edge(" << to << ") ";
    //   continue;
    // }
    if (critical[to] && dist[to] > dist[cur]) {
      cout << "next(" << to << ") ";
      continue;
    }
    if (critical[to]) continue;
    cout << to << " ";
    int tmpDist = dist[to] + prevNode->cost + dist3[cur];
    if (dist[to] > dist[cur]) tmpDist = dist[to] + dist3[to];
    distList.push_back(tmpDist);
  }
  cout << endl;
  sort(distList.begin(), distList.end());
  if (distList.size() == 0) return;
  cout << distList[0] << endl;
  maxDist = max(maxDist, distList[0]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  v = vector<vector<edge*>>(N + 1);

  for (int i = 1; i <= N; i++) {
    dist[i] = 2147483647;
    dist3[i] = 2147483647;
  }
  for (int i = 0; i < M; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    edge* e = new edge;
    e->from = from;
    e->cost = cost;
    e->to = to;
    e->criticalEdgeId = 0;
    v[from].push_back(e);
    v[to].push_back(e);
  }
  pq.push({0, 1});
  dist[1] = 0;
  while (!pq.empty()) {
    int cur = pq.top().second;
    int curDist = -pq.top().first;
    pq.pop();
    if (curDist > dist[cur]) continue;
    for (auto next : v[cur]) {
      int n = next->to == cur ? next->from : next->to;
      int ndist = curDist + next->cost;
      if (dist[n] < ndist) {
        // 아무것도 안함
      } else if (dist[n] == ndist) {
        next->criticalEdgeId = criticalEdgeId[n];
      } else if (ndist < dist[n]) {
        dist[n] = ndist;
        pq.push({-ndist, n});
        next->criticalEdgeId = criticalEdgeIdCnt;
        criticalEdgeId[n] = criticalEdgeIdCnt;
        criticalEdgeIdCnt++;
      }
    }
  }
  pq = priority_queue<pair<int, int>>();  // -비용, 현위치
  pq.push({0, N});
  dist3[N] = 0;
  while (!pq.empty()) {
    int cur = pq.top().second;
    int curDist = -pq.top().first;
    pq.pop();
    if (curDist > dist3[cur]) continue;
    for (auto next : v[cur]) {
      int n = next->to == cur ? next->from : next->to;
      int ndist = curDist + next->cost;
      if (dist3[n] <= ndist) {
        continue;
      } else {
        dist3[n] = ndist;
        pq.push({-ndist, n});
      }
    }
  }

  // for (int i = 1; i <= N; i++) cout << dist[i] << " ";
  // cout << endl;
  // for (int i = 1; i <= N; i++) cout << dist3[i] << " ";
  // cout << endl;

  int cur = N;
  maxDist = dist[N];
  // cout << "critical:" << endl;
  for (int i = 1; i <= N; i++) {
    // 최단거리에 속하는 모든점들 체크
    if (dist[i] + dist3[i] == dist[N]) critical[i] = true;

    // if (critical[i]) cout << i << "(" << dist[i] + dist3[i] << ")" << " ";
  }
  // cout << endl;

  for (int i = 1; i <= N; i++) {
    // 최단거리에 속하는 모든점들에 대해서
    // 최단거리용 간선이 두 개 이상이면
    // 잘라도 의미 없음
    if (critical[i]) {
      int criticalAdjacentCnt = 0;
      for (auto adjacent : v[i]) {
        if (adjacent->criticalEdgeId == criticalEdgeId[i]) {
          adjacent->disabled = true;
          maxDist = max(maxDist, dijk());
          adjacent->disabled = false;
        }
      }
    }
  }

  cout << maxDist;

  return 0;
}
