#include <algorithm>
#include <iostream>
using namespace std;

string v[15];
bool used[15] = {false};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }
  int ret = 0;
  for (int i = 0; i < N; i++) {
    if (used[i]) continue;
    ret++;
    string base = v[i];
    used[i] = true;
    for (int j = i + 1; j < N; j++) {
      if (used[j]) continue;
      bool canFill = true;
      for (int k = 0; k < M; k++) {
        if (base[k] == '.') continue;
        if (v[j][k] == '.') continue;
        if (base[k] == v[j][k]) continue;
        canFill = false;
        break;
      }
      if (!canFill) continue;
      used[j] = true;
      for (int k = 0; k < M; k++) {
        if (base[k] == '.') base[k] = v[j][k];
      }
    }
  }
  cout << ret;
  return 0;
}