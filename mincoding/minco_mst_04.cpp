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

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

struct node {
  int y, x, dist, id;
};
struct cmp {
  bool operator()(const node& a, const node& b) { return a.dist > b.dist; }
};

char board[50][50];
int visited[50][50];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 0; test_case < T; test_case++) {
    int X, Y;
    cin >> X >> Y;
    int sX, sY;
    for (int i = 0; i < Y; i++)
      for (int j = 0; j < X; j++) {
        cin >> board[i][j];
        if (board[i][j] == 'S') {
          visited[i][j] = 2147483647;
          sX = j;
          sY = i;
        } else {
          visited[i][j] = 0;
        }
      }
    int sum = 0;
    int id = 1;
    priority_queue<node, vector<node>, cmp> pq;
    pq.push({sY, sX, 0, id++});
    while (!pq.empty()) {
      node cur = pq.top();
      int y = cur.y;
      int x = cur.x;
      // cout << y << ", " << x << ", " << cur.dist << ", " << cur.id << endl;
      pq.pop();
      if (visited[y][x] != 2147483647 && board[y][x] == 'A') {
        visited[y][x] = 2147483647;
        // cout << y << ", " << x << ", " << cur.dist << endl;
        sum += cur.dist;
        pq.push({y, x, 0, id++});
        continue;
      }
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (visited[ny][nx] >= cur.id) continue;
        if (board[ny][nx] == '#') continue;
        visited[ny][nx] = cur.id;
        pq.push({ny, nx, cur.dist + 1, cur.id});
      }
    }
    cout << sum << "\n";
  }

  return 0;
}
