#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int personY[10];
int personX[10];
int personCnt;

int stairY[2];
int stairX[2];
int stairCnt;

int stairLength[2];
int dist[2][10];

int useStair[10];

int ret;

queue<int> q[2];                    // 사람별 나오는시간
priority_queue<pair<int, int>> pq;  // 계단 탈 수 있는 시간, 계단id

int calc() {
  // 거리 계산
  for (int i = 0; i < personCnt; i++) {
    int dis = dist[useStair[i]][i];
    pq.push({-dis - 1, useStair[i]});
  }

  while (!pq.empty()) {
    int stairId = pq.top().second;
    int curTime = -pq.top().first;
    int finishTime = curTime + stairLength[stairId];
    if (finishTime >= ret) {
      pq = priority_queue<pair<int, int>>();
      q[0] = queue<int>();
      q[1] = queue<int>();
      return ret;
    }
    pq.pop();

    while (!q[stairId].empty() && q[stairId].front() <= curTime)
      q[stairId].pop();

    if (q[stairId].size() == 3) {
      pq.push({-(q[stairId].front()), stairId});
      continue;
    }

    q[stairId].push(finishTime);
  }

  int lastTime = 0;
  for (int i = 0; i < stairCnt; i++) {
    while (!q[i].empty()) {
      lastTime = max(lastTime, q[i].front());
      q[i].pop();
    }
  }
  return lastTime;
}

void dfs(int cur) {
  if (cur == personCnt) {
    ret = min(ret, calc());
    return;
  }
  for (int i = 0; i < stairCnt; i++) {
    useStair[cur] = i;
    dfs(cur + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    int N;
    cin >> N;
    personCnt = 0;
    stairCnt = 0;

    // 입력받기
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int cur;
        cin >> cur;
        switch (cur) {
          case 0:
            break;
          case 1:
            personY[personCnt] = i;
            personX[personCnt] = j;
            ++personCnt;
            break;
          default:
            stairY[stairCnt] = i;
            stairX[stairCnt] = j;
            stairLength[stairCnt] = cur;
            ++stairCnt;
            break;
        }
      }
    }

    // 거리 계산
    for (int i = 0; i < stairCnt; i++) {
      for (int j = 0; j < personCnt; j++) {
        int dy = abs(stairY[i] - personY[j]);
        int dx = abs(stairX[i] - personX[j]);
        dist[i][j] = dy + dx;
      }
    }

    ret = 2147483647;
    dfs(0);

    cout << "#" << test_case << " " << ret << "\n";
  }

  return 0;
}