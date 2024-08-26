#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

struct BC {
  int power, usedTurn;
  int y, x, c;
};

bool compareBC(const BC& a, const BC& b) { return a.power > b.power; }

int dx[5] = {0, -1, 0, 1, 0};
int dy[5] = {0, 0, 1, 0, -1};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;

  int M, A;
  int dirA[101] = {0};
  int dirB[101] = {0};
  list<BC*> board[20][20];
  BC bc_pool[8];
  for (int test_case = 1; test_case <= T; ++test_case) {
    for (int i = 1; i <= 20; i++)
      for (int j = 1; j <= 20; j++) board[i][j].clear();

    cin >> M >> A;
    for (int i = 1; i <= M; i++) cin >> dirA[i];
    for (int i = 1; i <= M; i++) cin >> dirB[i];

    for (int i = 0; i < A; i++) {
      int y, x, c, p;
      cin >> y >> x >> c >> p;
      bc_pool[i] = {p, -1, y, x, c};
    }

    sort(bc_pool, bc_pool + A, compareBC);

    for (int i = 0; i < A; i++) {
      BC* bc = &bc_pool[i];
      for (int ddy = -bc->c; ddy <= bc->c; ddy++) {
        for (int ddx = -bc->c + abs(ddy); ddx <= bc->c - abs(ddy); ddx++) {
          int ny = bc->y + ddy;
          int nx = bc->x + ddx;
          if (nx < 0 || ny < 0 || nx > 10 || ny > 10) continue;
          board[ny][nx].push_back(bc);
        }
      }
    }

    int Ay = 1, Ax = 1, By = 10, Bx = 10;

    int ret = 0;
    for (int turn = 0; turn <= M; turn++) {
      Ay += dy[dirA[turn]];
      Ax += dx[dirA[turn]];
      By += dy[dirB[turn]];
      Bx += dx[dirB[turn]];
      auto Ai = board[Ay][Ax].begin();
      auto Bi = board[By][Bx].begin();
      if (Ai != board[Ay][Ax].end() && Bi != board[By][Bx].end()) {
        if ((*Ai) == (*Bi)) {
          ret += ((*Ai)->power);
          Ai++;
          Bi++;
          if (Ai == board[Ay][Ax].end() && Bi == board[By][Bx].end())
            continue;
          else if (Ai == board[Ay][Ax].end())
            ret += (*Bi)->power;
          else if (Bi == board[By][Bx].end())
            ret += (*Ai)->power;
          else
            ret += max((*Ai)->power, (*Bi)->power);
        } else {
          ret += (*Ai)->power;
          ret += (*Bi)->power;
        }
      } else if (Ai != board[Ay][Ax].end()) {
        ret += (*Ai)->power;
      } else if (Bi != board[By][Bx].end()) {
        ret += (*Bi)->power;
      }
    }
    cout << "#" << test_case << " " << ret << "\n";
  }

  return 0;
}
