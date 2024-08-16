#include <iostream>
#include <queue>
#include <string>
using namespace std;

int cup[302][302] = {0};
int visited[302][302] = {0};
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

bool canFill;
int minWall;
int filled = 0;
int fillId = 0;
void check(int y, int x, int height) {
  if (!canFill) return;
  if (visited[y][x] == fillId) return;
  if (cup[y][x] > height) {
    minWall = min(minWall, cup[y][x]);
    return;
  }
  if (cup[y][x] < height) {
    canFill = false;
    return;
  }
  visited[y][x] = fillId;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    check(ny, nx, height);
  }
}

void fill(int y, int x, int height) {
  if (cup[y][x] >= height) return;
  filled += height - cup[y][x];
  cup[y][x] = height;
  for (int dir = 0; dir < 4; dir++) {
    int ny = y + dy[dir];
    int nx = x + dx[dir];
    fill(ny, nx, height);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<pair<int, pair<int, int>>> pq;  // 높이, 좌표
  int N, M;
  cin >> M >> N;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      cin >> cup[i][j];
      pq.push({-cup[i][j], {i, j}});
    }
  }

  int cnt = 0;

  while (!pq.empty()) {
    // for (int i = 0; i <= N + 1; i++) {
    //   for (int j = 0; j <= M + 1; j++) cout << cup[i][j] << " ";
    //   cout << endl;
    // }
    // cout << endl;

    int height = -pq.top().first;
    int y = pq.top().second.first;
    int x = pq.top().second.second;
    pq.pop();
    // 제일 낮은 곳부터
    // 만약 그 자리가 이미 채워졌다면 스킵
    if (cup[y][x] != height) continue;
    // 아니라면 플루드필
    canFill = true;
    minWall = 2147483647;
    fillId++;
    check(y, x, height);
    // cout << y << ", " << x << ", " << height << " " << canFill << endl;
    if (!canFill) continue;
    // cout << "fill" << y << ", " << x << ", " << minWall << endl;
    fill(y, x, minWall);
    pq.push({minWall, {y, x}});
  }
  cout << filled;
  return 0;
}