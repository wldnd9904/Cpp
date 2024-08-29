#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int yunbis[50000];
  int N, Q;
  cin >> N >> Q;
  for (int i = 0; i < N; i++) cin >> yunbis[i];
  sort(yunbis, yunbis + N);
  map<int, int> yunbiToCnt;
  int curYunbi = -1;
  for (int i = 0; i < N; i++) {
    yunbiToCnt[yunbis[i]] = i * (N - 1 - i);
  }
  for (int i = 0; i < Q; i++) {
    int query;
    cin >> query;
    if (yunbiToCnt.count(query) == 0)
      cout << 0 << "\n";
    else
      cout << yunbiToCnt[query] << "\n";
  }
  return 0;
}