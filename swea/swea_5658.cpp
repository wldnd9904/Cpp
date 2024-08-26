#include <iostream>
using namespace std;

struct trie {
  trie* next[16] = {0};
};

int cnt;
int ret;
void dfs(trie* cur, int curSum, int curDepth) {
  if (cnt == 0) return;
  if (curDepth == 0) {
    cnt--;
    if (cnt == 0) {
      ret = curSum;
    }
    return;
  }
  for (int i = 15; i >= 0; i--) {
    if (cur->next[i] != nullptr)
      dfs(cur->next[i], curSum * 16 + i, curDepth - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    int N, K;
    cin >> N >> K;
    trie head;
    int s[28];
    for (int i = 0; i < N; i++) {
      char c;
      cin >> c;
      if (c <= '9')
        s[i] = c - '0';
      else
        s[i] = 10 + c - 'A';
    }
    for (int i = 0; i < N; i++) {
      trie* cur = &head;
      for (int j = 0; j <= N / 4; j++) {
        int next = s[(i + j) % N];
        if (cur->next[next] == nullptr) {
          cur->next[next] = new trie;
        }
        cur = cur->next[next];
      }
    }
    cnt = K;
    dfs(&head, 0, N / 4);

    cout << "#" << test_case << " " << ret << "\n";
  }
  return 0;
}