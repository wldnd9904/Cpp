#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, K;
vector<pair<int, int>> colorDots[21];
bool used[21] = {false};
int ret = 2147483647;

int pivotX;
int pivotY;
bool cmp(pair<int, int>& a, pair<int, int>& b) {
  return (abs(a.first - pivotY) + abs(a.second - pivotX)) <
         (abs(b.first - pivotY) + abs(b.second - pivotX));
}

void dfs(int cur, int minY, int minX, int maxY, int maxX) {
  int size = (maxY - minY) * (maxX - minX);
  if (size >= ret) return;
  if (cur > K) {
    ret = min(ret, size);
    return;
  }
  pivotX = (minX + maxX) / 2;
  pivotY = (minY + maxY) / 2;
  sort(colorDots[cur].begin(), colorDots[cur].end(), cmp);
  for (auto [y, x] : colorDots[cur]) {
    dfs(cur + 1, min(minY, y), min(minX, x), max(maxY, y), max(maxX, x));
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    int x, y, k;
    cin >> x >> y >> k;
    colorDots[k].push_back({y, x});
  }
  dfs(1, 1001, 1001, -1001, -1001);
  cout << ret;
  return 0;
}