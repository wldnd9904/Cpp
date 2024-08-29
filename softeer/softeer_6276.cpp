#include <iostream>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("input.txt", "r", stdin);
  int v[5000];
  long long bigger[5000];  // v[i] 보다 큰 오른쪽 원소들의 개수
  long long dp[5000];      // 이거의 합이 정답
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> v[i];
    bigger[i] = 0;
    dp[i] = 0;
    for (int j = i - 1; j >= 0; j--) {
      if (v[i] > v[j]) bigger[j]++;
      if (v[i] < v[j]) dp[j] += bigger[j];
    }
  }

  long long ret = 0;
  for (int i = 0; i < N; i++) ret += dp[i];

  cout << ret;
  return 0;
}