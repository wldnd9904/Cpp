#include <iostream>

using namespace std;

int N;
int from[1000], to[1000];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> from[i];
  for (int i = 0; i < N; i++) cin >> to[i];
  int ret = 0;
  int jump = 0;
  while (true) {
    int i = jump;
    while (i < N && to[i] - from[i] == 0) i++;
    if (i == N) break;
    bool flag = (to[i] - from[i]) > 0;
    int fromIdx = i;
    i++;
    if (flag) {
      while (i < N && to[i] - from[i] > 0) i++;
      for (int j = fromIdx; j < i; j++) from[j]++;
    } else {
      while (i < N && to[i] - from[i] < 0) i++;
      for (int j = fromIdx; j < i; j++) from[j]--;
    }
    if (to[fromIdx] - from[fromIdx] == 0) jump = fromIdx;
    ret++;
  }
  cout << ret;
  return 0;
}
