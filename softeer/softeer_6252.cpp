#include <math.h>

#include <iostream>
using namespace std;
long long v[100000];
int N;
long long B;

bool canEnhanceTo(int perf) {
  long long total = 0;
  for (int i = 0; i < N; i++) {
    if (v[i] >= perf) continue;
    total += (perf - v[i]) * (perf - v[i]);
    if (total > B) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> B;
  for (int i = 0; i < N; i++) cin >> v[i];

  int left = 0, right = 2000000000;
  while (left != right) {
    int mid = right - (right - left) / 2;
    if (canEnhanceTo(mid))
      left = mid;
    else
      right = mid - 1;
  }

  cout << left;
  return 0;
}