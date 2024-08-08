#include <iostream>
using namespace std;
int arr[12];
int N;
int minValue, maxValue;

void solve(int cur, int idx, int plus, int minus, int mul, int div) {
  if (idx == N) {
    if (cur < minValue) minValue = cur;
    if (cur > maxValue) maxValue = cur;
    return;
  }
  if (plus) solve(cur + arr[idx], idx + 1, plus - 1, minus, mul, div);
  if (minus) solve(cur - arr[idx], idx + 1, plus, minus - 1, mul, div);
  if (mul) solve(cur * arr[idx], idx + 1, plus, minus, mul - 1, div);
  if (div) solve(cur / arr[idx], idx + 1, plus, minus, mul, div - 1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N;
    int plus, minus, mul, div;
    cin >> plus >> minus >> mul >> div;
    for (int i = 0; i < N; i++) cin >> arr[i];
    minValue = 2147483647;
    maxValue = -2147483648;
    solve(arr[0], 1, plus, minus, mul, div);
    cout << "#" << test_case << " " << maxValue - minValue << "\n";
  }
  return 0;
}