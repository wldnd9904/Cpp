#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct edge {
  int from, to, dist;
};

bool compareEdge(edge& a, edge& b) { return a.dist < b.dist; }

int N, M;
int dist[8][8];
int parent[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int board[12][12];
const int dy[4] = {0, 0, -1, 1};
const int dx[4] = {-1, 1, 0, 0};
int islandIdx = 2;  // 2번부터 7번까지

int findAncestor(int i) {
  while (parent[i] != i) {
    i = parent[i];
  }
  return i;
}

void fillIdx(int y, int x, int idx) {
  board[y][x] = idx;
  for (int i = 0; i < 4; i++) {
    int ny = y + dy[i], nx = x + dx[i];
    if (board[ny][nx] == 1) fillIdx(ny, nx, idx);
  }
}
// 섬에 ID부여
void grantId() {
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      if (board[i][j] == 1) fillIdx(i, j, islandIdx++);
    }
}

void findEdge() {
  // 간선 초기화
  for (int i = 2; i < islandIdx; i++) {
    for (int j = 2; j < islandIdx; j++) {
      dist[i][j] = dist[j][i] = 100;
    }
  }
  // 가로 연결점 탐색
  for (int i = 1; i <= N; i++) {
    int curIsland = 0;  // 현재 섬 저장
    int harbor = -1;    // 그 섬의 끝좌표
    for (int j = 1; j <= M; j++) {
      // 섬일때
      if (board[i][j]) {
        // 이전 섬이랑 다른 섬이라면 연결해주기
        if (curIsland != 0 && curIsland != board[i][j] && j - harbor > 2) {
          dist[curIsland][board[i][j]] =
              min(dist[curIsland][board[i][j]], j - harbor - 1);
          dist[board[i][j]][curIsland] = dist[curIsland][board[i][j]];
        }
        // 끝지점 갱신
        curIsland = board[i][j];
        harbor = j;
      }
    }
  }

  // 세로 연결점 탐색
  for (int j = 1; j <= M; j++) {
    int curIsland = 0;  // 현재 섬 저장
    int harbor = -1;    // 그 섬의 끝좌표
    for (int i = 1; i <= N; i++) {
      // 섬일때
      if (board[i][j]) {
        // 이전 섬이랑 다른 섬이라면 연결해주기
        if (curIsland != 0 && curIsland != board[i][j] && i - harbor > 2) {
          dist[curIsland][board[i][j]] =
              min(dist[curIsland][board[i][j]], i - harbor - 1);
          dist[board[i][j]][curIsland] = dist[curIsland][board[i][j]];
        }
        // 끝지점 갱신
        curIsland = board[i][j];
        harbor = i;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M;

  // 테두리 채우기
  for (int i = 0; i <= N + 1; i++) {
    board[i][0] = -1;
    board[i][M + 1] = -1;
  }
  for (int i = 0; i <= M + 1; i++) {
    board[0][i] = -1;
    board[M + 1][i] = -1;
  }
  // 입력받기
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> board[i][j];

  grantId();
  findEdge();

  vector<edge> v;

  // 간선 정렬용 배열에 넣기
  for (int i = 3; i < islandIdx; i++)
    for (int j = 2; j < i; j++)
      if (dist[i][j] < 100) v.push_back({i, j, dist[i][j]});

  // 크루스칼
  // 간선 오름차순으로 정렬
  bool visited[8] = {false};
  sort(v.begin(), v.end(), compareEdge);
  int sum = 0;
  for (edge e : v) {
    int afrom = findAncestor(e.from);
    int ato = findAncestor(e.to);
    cout << afrom << ", " << ato << endl;
    if (afrom != ato) {
      sum += e.dist;
      parent[ato] = afrom;
      visited[e.from] = visited[e.to] = true;
    }
  }
  for (int i = 2; i < islandIdx; i++) {
    if (!visited[i]) {
      cout << -1;
      return 0;
    }
  }
  int ancestor = findAncestor(2);
  for (int i = 3; i < islandIdx; i++) {
    if (findAncestor(i) != ancestor) {
      cout << -1;
      return 0;
    }
  }
  cout << sum << "\n";
  return 0;
}