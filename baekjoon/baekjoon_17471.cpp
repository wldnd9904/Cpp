#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int N;
int people[10];
int isSector1[10] = {false};
int mindif = 2147483647;
vector<vector<int>> v;

void check(set<int>& s, int cur) {
  s.erase(cur);
  for (int next : v[cur]) {
    if (s.find(next) == s.end()) continue;
    if (isSector1[cur] != isSector1[next]) continue;
    check(s, next);
  }
}

bool canCalc() {
  set<int> set1, set2;
  for (int i = 0; i < N; i++) {
    if (isSector1[i])
      set1.insert(i);
    else
      set2.insert(i);
  }
  if (set1.empty() || set2.empty()) return false;
  check(set1, *set1.begin());
  check(set2, *set2.begin());
  return (set1.empty() && set2.empty());
}

void calc() {
  int sum1 = 0, sum2 = 0;
  for (int i = 0; i < N; i++)
    if (isSector1[i]) {
      sum1 += people[i];
    } else {
      sum2 += people[i];
    }
  mindif = min(mindif, abs(sum1 - sum2));
}

// 0번은 무조건 섹터1
void dfs(int cnt) {
  if (cnt == N) {
    if (!canCalc()) return;
    calc();
    return;
  } else {
    dfs(cnt + 1);
    isSector1[cnt] = true;
    dfs(cnt + 1);
    isSector1[cnt] = false;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> people[i];
  }
  v = vector<vector<int>>(N);
  for (int i = 0; i < N; i++) {
    int cnt;
    cin >> cnt;
    v[i] = vector<int>(cnt);
    for (int j = 0; j < cnt; j++) {
      int tmp;
      cin >> tmp;
      v[i][j] = tmp - 1;
    }
  }
  isSector1[0] = true;
  dfs(1);

  cout << (mindif == 2147483647 ? -1 : mindif) << "\n";
  return 0;
}