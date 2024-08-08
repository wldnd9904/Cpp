#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

int schedule[12];
int minPrice;
int day, month, three;

void solve(int curMonth, int curPrice) {
  if (curMonth >= 12) {
    minPrice = min(minPrice, curPrice);
    return;
  }
  if (curPrice > minPrice) return;
  solve(curMonth + 1, curPrice + min(schedule[curMonth] * day, month));
  solve(curMonth + 3, curPrice + three);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; ++test_case) {
    cin >> day >> month >> three >> minPrice;
    for (int i = 0; i < 12; i++) cin >> schedule[i];
    solve(0, 0);
    cout << "#" << test_case << " " << minPrice << "\n";
  }

  return 0;
}
