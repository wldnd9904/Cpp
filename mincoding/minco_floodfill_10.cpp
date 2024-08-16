#include <iostream>
#include <queue>
using namespace std;
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int T, N, M, HP;
int board[12][12];    // 0:빈공간, 1:벽, 2:막대기, 3:칼리버, 4:마왕
int visited[12][12];  // 0:빈공간, 1:벽, 2:막대기, 3:칼리버, 4:마왕
queue<pair<int, int>> q;
queue<pair<int, int>> q1;
queue<pair<int, int>> q2;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    cin >> N >> M;
    // 프레임씌우기
    for (int i = 1; i <= N; i++) {
      board[i][0] = 1;
      board[i][M + 1] = 1;
    }
    for (int i = 1; i <= M; i++) {
      board[0][i] = 1;
      board[N + 1][i] = 1;
    }
    // 큐초기화 및 방문배열 초기화
    int q1Time = -1, q1Y, q1X;
    int q2Time = -1, q2Y, q2X;
    q = queue<pair<int, int>>();
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= M; j++) visited[i][j] = 0;

    // 입력받기
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        char c;
        cin >> c;
        switch (c) {
          case 'Y':
            q.push({i, j});
            visited[i][j] = 1;
          case '_':
            board[i][j] = 0;
            continue;
          case 'x':
            board[i][j] = 1;
            continue;
          case 'M':
            board[i][j] = 4;
            continue;
          case 'S':
            board[i][j] = 3;
            continue;
          case 'T':
            board[i][j] = 2;
            continue;
        }
      }
    }
    cin >> HP;

    // 무기 찾기
    while (!q.empty()) {
      int y = q.front().first;
      int x = q.front().second;
      q.pop();
      int cur = visited[y][x];
      if (board[y][x] == 2) {
        q1Time = cur;
        q1Y = y;
        q1X = x;
        if (q2Time != -1) break;
      }
      if (board[y][x] == 3) {
        q2Time = cur;
        q2Y = y;
        q2X = x;
        if (q1Time != -1) break;
      }
      for (int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx] == 1) continue;
        if (visited[ny][nx]) continue;
        visited[ny][nx] = cur + 1;
        q.push({ny, nx});
      }
    }
    int minTime = 2147483647;

    // 마왕찾기: 99강화 막대기편
    if (q1Time != -1) {
      // 큐초기화 및 방문배열 초기화
      q = queue<pair<int, int>>();
      for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) visited[i][j] = 0;
      q.push({q1Y, q1X});
      visited[q1Y][q1X] = q1Time;

      while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        int cur = visited[y][x];
        if (board[y][x] == 4) {
          minTime = min(minTime, cur + (HP + 1) / 2);
          break;
        }
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (board[ny][nx] == 1) continue;
          if (visited[ny][nx]) continue;
          visited[ny][nx] = cur + 1;
          q.push({ny, nx});
        }
      }
    }

    // 마왕찾기: 칼편
    if (q2Time != -1) {
      // 큐초기화 및 방문배열 초기화
      q = queue<pair<int, int>>();
      for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) visited[i][j] = 0;
      q.push({q2Y, q2X});
      visited[q2Y][q2X] = q2Time;

      while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        int cur = visited[y][x];
        if (board[y][x] == 4) {
          minTime = min(minTime, cur + (HP + 4) / 5);
          break;
        }
        for (int dir = 0; dir < 4; dir++) {
          int ny = y + dy[dir];
          int nx = x + dx[dir];
          if (board[ny][nx] == 1) continue;
          if (visited[ny][nx]) continue;
          visited[ny][nx] = cur + 1;
          q.push({ny, nx});
        }
      }
    }

    cout << "#" << test_case << " ";
    if (minTime == 2147483647)
      cout << "the world is doomed\n";
    else
      cout << minTime - 1 << "\n";
  }

  return 0;
}
