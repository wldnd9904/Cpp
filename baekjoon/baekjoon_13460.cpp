#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct node {
  int cnt, ry, rx, by, bx;
};
struct cmp {
  const bool operator()(const node a, const node b) const {
    return a.cnt > b.cnt;
  }
};
int dy[4] = {0, 0, -1, 1};
int dx[4] = {-1, 1, 0, 0};

int N, M;
int ry, rx, by, bx, oy, ox;             // 빨강 파랑 출구
int visited[10][10][10][10] = {false};  // 빨강y,x,파랑y,x
bool isWall[10][10] = {false};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      char tmp;
      cin >> tmp;
      switch (tmp) {
        case '#':
          isWall[i][j] = true;
          break;
        case '.':
          break;
        case 'O':
          oy = i;
          ox = j;
          break;
        case 'R':
          ry = i;
          rx = j;
          break;
        case 'B':
          by = i;
          bx = j;
          break;
      }
    }
  }
  priority_queue<node, vector<node>, cmp> pq;
  pq.push({0, ry, rx, by, bx});
  while (!pq.empty()) {
    node curNode = pq.top();
    const int ccnt = curNode.cnt;
    const int cry = curNode.ry;
    const int crx = curNode.rx;
    const int cby = curNode.by;
    const int cbx = curNode.bx;
    pq.pop();
    if (ccnt == 10) {
      break;
    }
    if (visited[cry][crx][cby][cbx]) continue;
    visited[cry][crx][cby][cbx] = true;
    // 각 방향마다
    for (int i = 0; i < 4; i++) {
      int nry = cry;
      int nrx = crx;
      int nby = cby;
      int nbx = cbx;
      bool redGoal = false, blueGoal = false;
      while (!redGoal && !isWall[nry + dy[i]][nrx + dx[i]] &&
             (blueGoal || ((nry + dy[i]) != nby || (nrx + dx[i]) != nbx))) {
        nry += dy[i];
        nrx += dx[i];
        if (nry == oy && nrx == ox) {
          redGoal = true;
        }
      }

      while (!blueGoal && !isWall[nby + dy[i]][nbx + dx[i]] &&
             (redGoal || ((nby + dy[i]) != nry || (nbx + dx[i]) != nrx))) {
        nby += dy[i];
        nbx += dx[i];
        if (nby == oy && nbx == ox) {
          blueGoal = true;
        }
      }
      while (!redGoal && !isWall[nry + dy[i]][nrx + dx[i]] &&
             (blueGoal || ((nry + dy[i]) != nby || (nrx + dx[i]) != nbx))) {
        nry += dy[i];
        nrx += dx[i];
        if (nry == oy && nrx == ox) {
          redGoal = true;
        }
      }

      while (!blueGoal && !isWall[nby + dy[i]][nbx + dx[i]] &&
             (redGoal || ((nby + dy[i]) != nry || (nbx + dx[i]) != nrx))) {
        nby += dy[i];
        nbx += dx[i];
        if (nby == oy && nbx == ox) {
          blueGoal = true;
        }
      }

      if (blueGoal) continue;
      if (redGoal) {
        cout << ccnt + 1;
        return 0;
      }

      pq.push({ccnt + 1, nry, nrx, nby, nbx});
    }
  }
  std::cout << -1;

  return 0;
}





