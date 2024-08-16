#include <iostream>
#include <queue>
using namespace std;
// 0: 제자리, 1~4: 주변 한칸, 5~12: 주변 두칸
const int dy[] = {0, -1, 1, 0, 0, -1, -1, 1, 1, -2, 2, 0, 0};
const int dx[] = {0, 0, 0, -1, 1, -1, 1, -1, 1, 0, 0, -2, 2};

int visited1[11][11] = {0};
int visited2[11][11] = {0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  queue<pair<int, int>> q;
  for (int y = 2; y <= 8; y++)
    for (int x = 2; x <= 8; x++) {
      char type;
      cin >> type;
      switch (type) {
        case '0':
          break;
        case '1': {
          int smell = 2;
          for (int dir = 0; dir <= 4; dir++) {
            if (dir == 1) smell--;
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            visited1[ny][nx] += smell;
            if (smell != 2 && visited1[ny][nx] >= 2) {
              cout << "fail";
              return 0;
            }
          }
          break;
        }
        case '2': {
          int smell = 3;
          for (int dir = 0; dir <= 12; dir++) {
            if (dir == 1) smell--;
            if (dir == 5) smell--;
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            visited2[ny][nx] += smell;
            if (smell != 3 && visited2[ny][nx] >= 3) {
              cout << "fail";
              return 0;
            }
          }
          break;
        }
      }
    }
  cout << "pass";

  return 0;
}
