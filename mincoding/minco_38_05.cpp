#include <iostream>
#include <queue>
using namespace std;
// 0: 제자리, 1~4: 주변 한칸, 5~12: 주변 두칸
struct node {
  int aY, aX, bY, bX, time;
};
const int dy[] = {0, -1, 1, 0, 0, -1, -1, 1, 1, -2, 2, 0, 0};
const int dx[] = {0, 0, 0, -1, 1, -1, 1, -1, 1, 0, 0, -2, 2};
int N;
bool canGo[7][7] = {false};
bool visited[7][7][7][7] = {false};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) {
      char c;
      cin >> c;
      if (c == '_') canGo[i][j] = true;
    }

  queue<node> q;
  int aY, aX, bY, bX;
  cin >> aY >> aX >> bY >> bX;
  aY += 1;
  aX += 1;
  bY += 1;
  bX += 1;
  q.push({aY, aX, bY, bX, 0});

  while (!q.empty()) {
    int aY = q.front().aY;  // c++ 17부턴 구조분해할당
    int aX = q.front().aX;
    int bY = q.front().bY;
    int bX = q.front().bX;
    int time = q.front().time;
    q.pop();
    int dirEnd = 8;
    if (abs(aY - bY) <= 2 && abs(aX - bX) <= 2) dirEnd = 4;

    for (int dir1 = 1; dir1 <= dirEnd; dir1++) {
      for (int dir2 = 0; dir2 <= 4; dir2++) {
        int naY = aY + dy[dir1];
        int naX = aX + dx[dir1];
        int nbY = bY + dy[dir2];
        int nbX = bX + dx[dir2];
        if (!canGo[naY][naX] || !canGo[nbY][nbX]) continue;
        if (naY == nbY && naX == nbX) {
          cout << time + 1 << " sec";
          return 0;
        }
        if (visited[naY][naX][nbY][nbX]) continue;
        visited[naY][naX][nbY][nbX] = true;
        q.push({naY, naX, nbY, nbX, time + 1});
      }
    }
  }

  return 0;
}
