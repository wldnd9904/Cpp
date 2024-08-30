#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int N;

// depth1: 기본 보드
int board[45][15];
int visited[15][15] = {0};

// depth2: 한 번 동작 후 보드
int board2[15][15];
int visited2[15][15] = {0};

// depth3: 두번 동작 후 보드
int board3[15][15];
int visited3[15][15] = {0};

int used[15] = {0};
int ret = 0;
int visitedCnt = 0;

void dfs3(int score) {
  queue<pair<int, int>> q;
  memset(visited3, 0, sizeof(visited3));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (visited3[i][j]) continue;
      int score3 = 0;
      int color = board3[i][j];
      // dfs돌면서 방문체크 및 점수 구하기
      visitedCnt++;
      int minX = 15, maxX = 0, minY = 15, maxY = 0;
      q.push({i, j});
      visited3[i][j] = visitedCnt;
      while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        minX = min(minX, x);
        minY = min(minY, y);
        maxX = max(maxX, x);
        maxY = max(maxY, y);
        q.pop();
        score3++;
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (ny < 0 || nx < 0 || nx >= N || ny >= N) continue;
          if (visited3[ny][nx]) continue;
          if (board3[ny][nx] != color) continue;
          visited3[ny][nx] = visitedCnt;
          q.push({ny, nx});
        }
      }
      score3 += (maxX - minX + 1) * (maxY - minY + 1);
      ret = max(ret, score + score3);
    }
  }
}

void dfs2(int score) {
  queue<pair<int, int>> q;
  memset(visited2, 0, sizeof(visited2));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (visited2[i][j]) continue;
      int color = board2[i][j];
      // dfs돌면서 방문체크 및 점수 구하기
      int score2 = 0;
      visitedCnt++;
      int minX = 15, maxX = 0, minY = 15, maxY = 0;
      q.push({i, j});
      visited2[i][j] = visitedCnt;
      while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        minX = min(minX, x);
        minY = min(minY, y);
        maxX = max(maxX, x);
        maxY = max(maxY, y);
        q.pop();
        score2++;
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (ny < 0 || nx < 0 || nx >= N || ny >= N) continue;
          if (visited2[ny][nx]) continue;
          if (board2[ny][nx] != color) continue;
          visited2[ny][nx] = visitedCnt;
          q.push({ny, nx});
        }
      }
      score2 += (maxX - minX + 1) * (maxY - minY + 1);
      // board2를 다음 모양으로 채우기
      for (int x = 0; x < N; x++) {
        int ny = 0;
        for (int y = 0; y < N; y++) {
          while (ny < N && visited2[ny][x] == visitedCnt) {
            ny++;
            if (ny == N) ny = used[x];
          }
          if (ny == N) ny = used[x];
          if (ny >= N)
            board3[y][x] = board[ny++][x];
          else
            board3[y][x] = board2[ny++][x];
        }
      }
      dfs3(score + score2);
    }
  }
}

void dfs1() {
  queue<pair<int, int>> q;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (visited[i][j]) continue;
      int color = board[i][j];
      // dfs돌면서 방문체크 및 점수 구하기
      visitedCnt++;
      int minX = 15, maxX = 0, minY = 15, maxY = 0;
      int score = 0;
      q.push({i, j});
      visited[i][j] = visitedCnt;
      while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        minX = min(minX, x);
        minY = min(minY, y);
        maxX = max(maxX, x);
        maxY = max(maxY, y);
        q.pop();
        score++;
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (ny < 0 || nx < 0 || nx >= N || ny >= N) continue;
          if (visited[ny][nx]) continue;
          if (board[ny][nx] != color) continue;
          visited[ny][nx] = visitedCnt;
          q.push({ny, nx});
        }
      }
      score += (maxX - minX + 1) * (maxY - minY + 1);
      // board2를 다음 모양으로 채우기
      for (int x = 0; x < N; x++) {
        int ny = 0;
        for (int y = 0; y < N; y++) {
          while (ny < N && visited[ny][x] == visitedCnt) ny++;
          board2[y][x] = board[ny++][x];
        }
        used[x] = ny;
      }
      // 그 보드가지고 한번 더 해보기
      dfs2(score);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N;
  for (int i = 3 * N - 1; i >= 0; i--)
    for (int j = 0; j < N; j++) cin >> board[i][j];
  dfs1();
  cout << ret;
  return 0;
}