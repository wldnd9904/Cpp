#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

int N, M;
string v[15];
unordered_map<string, string> m;  // 서열두개 더한것, true/false
bool used[15] = {false};
int ret = 2147483647;

bool merge(string a, string b, string& result) {
  auto it = m.find(a + b);
  if (it != m.end()) {
    result = it->second;
    return result.size();
  };
  result = a;
  for (int k = 0; k < M; k++) {
    if (a[k] == '.')
      result[k] = b[k];
    else if (b[k] == '.')
      continue;
    else if (a[k] != b[k]) {
      m[a + b] = "";
      return false;
    } else
      continue;
  }
  m[a + b] = result;
  return true;
}

void dfs(int cur, string curString, int curGroup, int curGroupSize) {
  if (curGroup >= ret) return;
  // cout << cur << " " << curString << " " << curGroup << endl;

  if (cur != N) {
    int mergeTried = 0;
    for (int i = cur; i < N; i++) {
      if (used[i]) continue;
      string result;
      result.reserve(M);
      bool canMerge = merge(curString, v[i], result);
      if (canMerge) {
        mergeTried++;
        used[i] = true;
        dfs(i + 1, result, curGroup, curGroupSize + 1);
        used[i] = false;
      }
    }
    // 적어도 결합하기는 해야됨
    // 근데 애초에 결합자체를 못하는거면 밑으로
    if (curGroupSize == 1 && mergeTried) return;
  }
  // 안 쓴게 있으면 그거로 그룹만들기 시도
  for (int i = 0; i < N; i++) {
    if (!used[i]) {
      used[i] = true;
      dfs(i + 1, v[i], curGroup + 1, 1);
      used[i] = false;
      return;
    }
  }
  // 모두 다 쓰였으면 현재 그룹 수+1이 만든 그룹 수인 것
  ret = min(ret, curGroup + 1);
}

// a가 b를 완전히 흡수하는지
bool coversPerfectly(string a, string b) {
  for (int k = 0; k < M; k++) {
    if (a[k] == b[k]) continue;
    if (b[k] == '.') continue;
    return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }
  int orphan = 0;

  for (int i = 0; i < N; i++) {
    if (used[i]) continue;
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      if (used[j]) continue;
      if (coversPerfectly(v[i], v[j])) {
        used[j] = true;
      }
    }
  }

  for (int i = 0; i < N; i++) {
    if (used[i]) continue;
    int mergeableCnt = 0;
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      if (used[j]) continue;
      string result;
      mergeableCnt += merge(v[i], v[j], result);
    }
    if (mergeableCnt == 0) {
      used[i] = true;
      orphan++;
    }
  }
  if (orphan != N) {
    for (int i = 0; i < N; i++) {
      if (!used[i]) {
        used[i] = true;
        dfs(i, v[i], 0, 1);
        cout << ret + orphan;
        return 0;
      }
    }
  }
  cout << orphan;
  return 0;
}