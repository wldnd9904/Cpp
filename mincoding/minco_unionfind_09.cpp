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

int dy[] = {0, 0, -1, 1};
int dx[] = {-1, 1, 0, 0};

struct area {
  area* parent = nullptr;
  int size = 0;
};

area* findAncestor(area* a) {
  if (a->parent == nullptr) return nullptr;
  if (a->parent != a) a->parent = findAncestor(a->parent);
  return a->parent;
}

area world[102][102];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int cntSum = 0, sizeSum = 0;

  int N;
  cin >> N;
  int cnt = 0, maxSize = 0;
  for (int i = 0; i < N; i++) {
    int y, x;
    cin >> y >> x;
    y++;
    x++;
    world[y][x].parent = &world[y][x];
    world[y][x].size = 1;
    cnt++;

    for (int dir = 0; dir < 4; dir++) {
      int ny = y + dy[dir], nx = x + dx[dir];
      area* nArea = findAncestor(&world[ny][nx]);
      if (nArea == nullptr) continue;
      if (nArea == &world[y][x]) continue;
      world[y][x].size += nArea->size;
      nArea->parent = &world[y][x];
      cnt--;
    }
    maxSize = max(maxSize, world[y][x].size);
    cntSum += cnt;
    sizeSum += maxSize;
  }
  cout << cntSum << "\n" << sizeSum;
  return 0;
}
