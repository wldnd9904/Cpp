#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
using namespace std;
int T, N;

int syn[16][16];
bool selected[16] = {
    true,
};

int v1[8], v2[8];
int dif() {
  int v1Cnt = 0, v2Cnt = 0;
  for (int i = 0; i < N; i++) {
    if (selected[i])
      v1[v1Cnt++] = i;
    else
      v2[v2Cnt++] = i;
  }
  int sum1 = 0, sum2 = 0;
  for (int i = 0; i < N / 2; i++) {
    for (int j = i + 1; j < N / 2; j++) {
      sum1 += syn[v1[i]][v1[j]];
      sum2 += syn[v2[i]][v2[j]];
    }
  }
  return abs(sum2 - sum1);
}
int ret;

void dfs(int cur, int trueLeft) {
  if (cur == N) return;
  dfs(cur + 1, trueLeft);

  selected[cur] = true;
  if (trueLeft == 1) {
    ret = min(ret, dif());
    selected[cur] = false;
    return;
  }
  dfs(cur + 1, trueLeft - 1);
  selected[cur] = false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (j >= i)
          cin >> syn[i][j];
        else {
          int tmp;
          cin >> tmp;
          syn[j][i] += tmp;
        }
      }
    }
    ret = 2147483647;
    dfs(1, N / 2 - 1);
    cout << "#" << test_case << " " << ret << "\n";
  }
  return 0;
}
