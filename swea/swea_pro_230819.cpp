#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
struct Result {
  int row;
  int col;
};
struct Bacteria {
  int id;
  int size;
  int time;
};
void init(int N);
Result putBacteria(int mTime, int mRow, int mCol, Bacteria mBac);
int killBacteria(int mTime, int mRow, int mCol);
int checkCell(int mTime, int mRow, int mCol);
/////////////////////////////////////////////////////////////////////////
#define INIT 10000
#define PUT 20000
#define KILL 30000
#define CHECK 40000
static bool run() {
  int cmd, N, time, row, col, ans, ret;
  Result ret_bac;
  Bacteria bac;
  int Q = 0;
  bool okay = false;
  scanf("%d", &Q);
  for (int q = 0; q < Q; ++q) {
    scanf("%d", &cmd);
    switch (cmd) {
      case INIT:
        scanf("%d", &N);
        init(N);
        okay = true;
        break;
      case PUT:
        scanf("%d %d %d %d %d %d", &time, &row, &col, &bac.id, &bac.size,
              &bac.time);
        ret_bac = putBacteria(time, row, col, bac);
        scanf("%d %d", &row, &col);
        if (ret_bac.row != row || ret_bac.col != col) {
          okay = false;
        }
        // printf("PUT: %d, %d -- %d, %d\n", ret_bac.row, ret_bac.col, row,
        // col);
        break;
      case KILL:
        scanf("%d %d %d %d", &time, &row, &col, &ans);
        ret = killBacteria(time, row, col);
        if (ret != ans) {
          okay = false;
        }
        // printf("KILL: %d\n", okay);
        break;
      case CHECK:
        scanf("%d %d %d %d", &time, &row, &col, &ans);
        ret = checkCell(time, row, col);
        if (ret != ans) {
          okay = false;
        }
        // printf("CHECK:%d, %d\n", ret, ans);
        break;
      default:
        okay = false;
    }
  }
  return okay;
}
int main() {
  setbuf(stdout, NULL);
  freopen("input.txt", "r", stdin);
  int T, MARK;
  scanf("%d %d", &T, &MARK);
  for (int tc = 1; tc <= T; tc++) {
    int score = run() ? MARK : 0;
    printf("#%d %d\n", tc, score);
  }
  return 0;
}
// user.cpp
#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;
struct Bac {
  int id;
  int deadAfter;
};
int n;
Bac bac_pool[6001];
Bac* reserve;
Bac* board[202][202];

int pivotY, pivotX;

int distance(int y, int x) { return abs(y - pivotY) + abs(x - pivotX); }

struct cmp {
  bool operator()(pair<int, int>& a, pair<int, int>& b) {
    int dirA = distance(a.first, a.second);
    int dirB = distance(b.first, b.second);
    if (dirA == dirB) return a > b;
    return dirA > dirB;
  }
};

int dy[] = {-1, 0, 0, 1};
int dx[] = {0, -1, 1, 0};
void print() {
  for (int i = 0; i <= n + 1; i++) {
    for (int j = 0; j <= n + 1; j++) {
      if (board[i][j] == nullptr)
        cout << 0 << " ";
      else
        cout << board[i][j]->id << " ";
    }
    cout << endl;
  }
  cout << endl;
}
void init(int N) {
  n = N;
  // 0번 박테리아로 테두리 만듦
  bac_pool[0].id = 0;
  bac_pool[0].deadAfter = 1020001;
  Bac* wall = &bac_pool[0];
  for (int i = 1; i <= N; i++) {
    board[0 + i][0] = wall;
    board[i][N + 1] = wall;
    board[0][0 + i] = wall;
    board[N + 1][i] = wall;
  }
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) board[i][j] = nullptr;
  return;
}
Result putBacteria(int mTime, int mRow, int mCol, Bacteria mBac) {
  pivotY = mRow;
  pivotX = mCol;
  reserve = &bac_pool[mBac.id + 3000];
  reserve->id = 0;
  reserve->deadAfter = mTime + 1;
  bac_pool[mBac.id].id = mBac.id;
  bac_pool[mBac.id].deadAfter = mTime + 1;
  Bac* bac = &bac_pool[mBac.id];
  if (board[mRow][mCol] != nullptr && board[mRow][mCol]->deadAfter > mTime)
    return {0, 0};
  priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q;
  priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q2;
  Result ret;
  int sizeLeft = mBac.size;
  q.push({mRow, mCol});
  int maxDist = 0;
  while (sizeLeft && !q.empty()) {
    int y = q.top().first;
    int x = q.top().second;
    maxDist = max(maxDist, distance(y, x));
    board[y][x] = bac;
    sizeLeft--;
    if (sizeLeft == 0) {
      ret = {y, x};
      break;
    }
    q.pop();
    // 주변지역 예약해놓기
    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir];
      int nx = x + dx[dir];
      if (board[ny][nx] != nullptr && board[ny][nx]->deadAfter > mTime)
        continue;
      board[ny][nx] = reserve;
      if (distance(ny, nx) <= maxDist)
        q.push({ny, nx});
      else
        q2.push({ny, nx});
    }
    if (q.empty()) swap(q, q2);
  }
  if (sizeLeft) return {0, 0};
  // print();
  bac->deadAfter = mTime + mBac.time;
  return ret;
}
int killBacteria(int mTime, int mRow, int mCol) {
  if (board[mRow][mCol] == nullptr || board[mRow][mCol]->deadAfter <= mTime)
    return 0;
  board[mRow][mCol]->deadAfter = mTime;
  return board[mRow][mCol]->id;
}
int checkCell(int mTime, int mRow, int mCol) {
  if (board[mRow][mCol] == nullptr || board[mRow][mCol]->deadAfter <= mTime)
    return 0;
  return board[mRow][mCol]->id;
}