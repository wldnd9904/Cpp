#include <algorithm>
#include <iostream>
using namespace std;
int N, M, K;
int A[101][101];
int Ks[6][3];
bool visited[6] = {false};

int ret = 2147483647;

void calc() {
  for (int i = 0; i < N; i++) {
    int sum1 = 0;
    for (int j = 0; j < M; j++) {
      sum1 += A[i][j];
    }
    ret = min(ret, sum1);
  }
}

void rotate(int y, int x, int r) {
  y--;
  x--;
  for (int rad = 1; rad <= r; rad++) {
    int tmp = A[y - rad][x - rad];
    for (int i = y - rad; i < y + rad; i++) A[i][x - rad] = A[i + 1][x - rad];

    for (int i = x - rad; i < x + rad; i++) A[y + rad][i] = A[y + rad][i + 1];

    for (int i = y + rad; i > y - rad; i--) A[i][x + rad] = A[i - 1][x + rad];

    for (int i = x + rad; i > x - rad; i--) A[y - rad][i] = A[y - rad][i - 1];

    A[y - rad][x - rad + 1] = tmp;
  }
}

void rotateR(int y, int x, int r) {
  y--;
  x--;
  for (int rad = 1; rad <= r; rad++) {
    int tmp = A[y - rad][x - rad];
    for (int i = x - rad; i < x + rad; i++) A[y - rad][i] = A[y - rad][i + 1];

    for (int i = y - rad; i < y + rad; i++) A[i][x + rad] = A[i + 1][x + rad];

    for (int i = x + rad; i > x - rad; i--) A[y + rad][i] = A[y + rad][i - 1];

    for (int i = y + rad; i > y - rad; i--) A[i][x - rad] = A[i - 1][x - rad];

    A[y - rad + 1][x - rad] = tmp;
  }
}

void dfs(int cnt) {
  if (cnt == K) {
    calc();
    return;
  } else {
    for (int i = 0; i < K; i++) {
      if (visited[i]) continue;
      visited[i] = true;
      rotate(Ks[i][0], Ks[i][1], Ks[i][2]);
      dfs(cnt + 1);
      rotateR(Ks[i][0], Ks[i][1], Ks[i][2]);
      visited[i] = false;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> N >> M >> K;
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < M; x++) {
      cin >> A[y][x];
    }
  }
  for (int k = 0; k < K; k++) {
    for (int i = 0; i < 3; i++) {
      cin >> Ks[k][i];
    }
  }

  dfs(0);

  cout << ret << "\n";
  return 0;
}