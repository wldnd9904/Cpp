#include <iostream>
#include <list>
using namespace std;
struct microbiome {
  int y, x, cnt;
  int direction;
  int maxCnt;
};
int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, -1, 1, 0, 0};
microbiome bio_pool[1000];
int bioCnt;
microbiome* board[2][100][100];
bool toxic[100][100];
list<microbiome*> biomeList;
int N, M, K;
int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N >> M >> K;
    bioCnt = 0;
    biomeList.clear();

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) {
        board[0][i][j] = nullptr;
        board[1][i][j] = nullptr;
        toxic[i][j] = false;
      }
    for (int i = 0; i < N; i++) {
      toxic[i][0] = true;
      toxic[0][i] = true;
      toxic[N - 1][i] = true;
      toxic[i][N - 1] = true;
    }

    for (int i = 0; i < K; i++) {
      int y, x, cnt, dir;
      cin >> y >> x >> cnt >> dir;
      bio_pool[bioCnt] = {y, x, cnt, dir, cnt};
      board[0][y][x] = &bio_pool[bioCnt];
      biomeList.push_back(&bio_pool[bioCnt]);
      bioCnt++;
    }

    for (int turn = 0; turn < M; turn++) {
      int curBit = turn & 1;

      for (auto it = biomeList.begin(); it != biomeList.end();) {
        microbiome* bio = *it;
        int ny = bio->y + dy[bio->direction];
        int nx = bio->x + dx[bio->direction];
        board[curBit][bio->y][bio->x] = nullptr;
        if (toxic[ny][nx]) {
          bio->cnt /= 2;
          if (bio->cnt == 0) {
            it = biomeList.erase(it);
          } else {
            bio->y = ny;
            bio->x = nx;
            board[!curBit][ny][nx] = bio;
            bio->direction += (bio->direction & 1 ? 1 : -1);
            it++;
          }
          continue;
        }
        if (board[!curBit][ny][nx] != nullptr) {
          microbiome* enemy = board[!curBit][ny][nx];
          enemy->cnt += bio->cnt;
          if (enemy->maxCnt < bio->cnt) {
            enemy->maxCnt = bio->cnt;
            enemy->direction = bio->direction;
          }
          it = biomeList.erase(it);
        } else {
          board[!curBit][ny][nx] = bio;
          bio->maxCnt = bio->cnt;
          bio->y = ny;
          bio->x = nx;
          it++;
        }
      }
    }
    int sum = 0;
    for (auto bio : biomeList) sum += bio->cnt;
    cout << "#" << test_case << " " << sum << "\n";
  }
  return 0;
}