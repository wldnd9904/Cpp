#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  pair<long long, bool> cnt[26];  // 가중치, 0이 가능한지
  string s[10];
  for (int i = 0; i < N; i++) cin >> s[i];
  for (int i = 0; i < 26; i++) {
    cnt[i] = {0, true};
  }
  for (int i = 0; i < N; i++) {
    long long factor = 1;
    for (int j = s[i].length() - 1; j >= 0; j--) {
      int idx = s[i][j] - 'A';
      cnt[idx].first += factor;
      if (j == 0) cnt[idx].second = false;  // 맨앞에 나온애는 0못함
      factor *= 10;
    }
  }
  vector<pair<long long, bool>> cnt2;
  for (int i = 0; i < 26; i++) {
    if (cnt[i].first > 0) cnt2.push_back(cnt[i]);
  }
  sort(cnt2.begin(), cnt2.end());

  long long sum = 0;
  int ii = 10 - cnt2.size();
  bool foundZero = ii != 1;
  for (int i = 0; i < cnt2.size(); i++) {
    if (cnt2[i].first == 0) continue;
    if (!foundZero && cnt2[i].second) {
      foundZero = true;
      continue;
    }
    sum += cnt2[i].first * ii++;
  }
  cout << sum;
  return 0;
}