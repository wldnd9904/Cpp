#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int parent[100001];
int board[2002][2002];
int visited[2002][2002] = {0};
int findAncestor(int a) {
  if (parent[a] == a) return a;
  parent[a] = findAncestor(parent[a]);
  return parent[a];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N, K;
  queue<pair<int, int>> q;

  cin >> N >> K;

  for (int i = 1; i <= N; i++) {
    board[i][0] = -1;
    board[i][N + 1] = -1;
    board[0][i] = -1;
    board[N + 1][i] = -1;
  }

  for (int i = 1; i <= K; i++) {
    parent[i] = i;
    int y, x;
    cin >> y >> x;
    q.push({y, x});
    board[y][x] = i;
  }
  K--;  // 유니온 할때마다 k개수 줄임, 0되면 끝날 것
  int qSize = q.size();
  int t = 0;
  while (qSize) {
    t++;
    while (qSize--) {
      int y = q.front().first;
      int x = q.front().second;
      int cur = findAncestor(board[y][x]);
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx] == -1) continue;
        if (board[ny][nx] == 0) {
          board[ny][nx] = cur;
          q.push({ny, nx});
          visited[ny][nx] = t;
          continue;
        }
        if (findAncestor(board[ny][nx]) == cur)
          continue;
        else {
          // 이번 턴에 다른애가 점령했으면 다음턴에 동맹하기
          if (visited[ny][nx] == t) {
            q.push({y, x});
            continue;
          }
          // cout << board[ny][nx] << "->" << cur << endl;
          parent[findAncestor(board[ny][nx])] = cur;
          K--;
          if (K == 0) {
            cout << t - 1;
            return 0;
          }
        }
      }
    }
    qSize = q.size();
  }
  return 0;
}
