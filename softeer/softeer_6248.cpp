#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> vForward[100001];
vector<int> vReverse[100001];
int visited[100001] = {0};
// 1: 출근길, 2: 출근길 역주행
// 4: 퇴근길, 8: 퇴근길 역주행
int N, M;
int S, T;

void bfs(int start, int isPath, vector<int> v[]) {
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int next : v[cur]) {
      if (visited[next] & isPath) continue;
      visited[next] |= isPath;
      q.push(next);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int from, to;
    cin >> from >> to;
    vForward[from].push_back(to);
    vReverse[to].push_back(from);
  }
  cin >> S >> T;
  visited[S] = 5;
  visited[T] = 5;
  bfs(S, 1, vForward);
  bfs(T, 2, vReverse);
  bfs(T, 4, vForward);
  bfs(S, 8, vReverse);
  int ret = 0;
  for (int i = 1; i <= N; i++) {
    if (visited[i] == 15) {
      ret++;
    }
  }
  cout << ret - 2;
  return 0;
}