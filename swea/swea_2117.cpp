#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int cnt;
int y[400];
int x[400];
int neighborCnt[400][41];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; ++test_case) {
    int N, M;
    cin >> N >> M;
    cnt = 0;
    // 집들 입력받기
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        bool house;
        cin >> house;
        if (house) {
          y[cnt] = i;
          x[cnt] = j;
          cnt++;
        }
      }
    }
    // 이웃 수 초기화
    for (int i = 0; i < cnt; i++) {
      neighborCnt[i][0] = 1;
      for (int j = 1; j < 2 * N; j++) {
        neighborCnt[i][j] = 0;
      }
    }
    // 거리별 이웃 수 계산
    for (int i = 0; i < cnt; i++) {
      for (int j = i + 1; j < cnt; j++) {
        int dy = y[i] - y[j];
        int dx = x[i] - x[j];
        // 이러면 0:0, 1: 1,2, 2: 3,4 이런식으로 들어감
        int distance = (abs(dy) + abs(dx) + 1) / 2;
        neighborCnt[i][distance]++;
        neighborCnt[j][distance]++;
      }
    }
    // 서비스 영역이 K 일 때
    // 운영비용 = 면적 = K*K + (K-1)*(K-1)
    // 최대 거리 = (K-1)*2 -> 0, 2, 4, 6, ... -> 2로 나눈 거리 저장
    // N=20이면 최대거리가 38
    // 지불비용 = 집 수 * M;
    int ret;
    for (int k = 1; k <= N + 2; k++) {
      cout << "K: " << k << endl;
      int cost = k * k + (k - 1) * (k - 1);
      cout << "cost: " << cost << endl;
      int maxGroup = 0;  // 최고 인싸의 집단 머릿수
      for (int i = 0; i < cnt; i++) {
        neighborCnt[i][k] += neighborCnt[i][k - 1];
        cout << neighborCnt[i][k - 1] << " ";
        maxGroup = max(maxGroup, neighborCnt[i][k - 1]);
      }
      cout << endl;
      cout << "maxGroup: " << maxGroup << endl;
      if (cost <= maxGroup * M) ret = maxGroup;
    }
    cout << "#" << test_case << " " << ret << "\n";
  }

  return 0;
}