#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // freopen("input.txt", "r", stdin);
  int N, L;
  cin >> N >> L;
  vector<pair<int, int>> v(N);

  for (int i = 0; i < N; i++) {
    int from, to;
    cin >> from >> to;
    v[i] = {from, to};
  }
  sort(v.begin(), v.end());
  int curEnd = 0, cnt = 0;  // [0,curEnd)
  for (auto pond : v) {
    if (curEnd >= pond.second) continue;
    curEnd = max(pond.first, curEnd);
    int required = (pond.second - curEnd + L - 1) / L;
    curEnd += L * required;
    cnt += required;
  }
  cout << cnt << "\n";
  return 0;
}