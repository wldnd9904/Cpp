#include <iostream>
#include <queue>
#include <string>
using namespace std;

bool fire[1003][1003] = {false};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      pq;

  int N, M;
  cin >> N >> M;

  for (int i = 0; i < M + N; i++) {
    int B, Y, X;
    cin >> B;
    if (B == 0) {
      bool activated = false;
      while (!pq.empty()) {
        // 가장 작은 번호 폭탄 폭파
        int y = pq.top().second.first;
        int x = pq.top().second.second;
        int id = pq.top().first;
        pq.pop();
        // 고장난 폭탄 스킵
        if (fire[y][x]) continue;
        fire[y][x] = true;
        fire[y - 1][x] = true;
        fire[y + 1][x] = true;
        fire[y][x - 1] = true;
        fire[y][x + 1] = true;
        cout << id << "\n";
        activated = true;
        break;
      }
      if (activated) continue;
      // 터질거 없으면 -1
      cout << -1 << "\n";
      continue;
    }
    cin >> Y >> X;
    Y++;
    X++;
    // 불타는 지역은 스킵
    if (fire[Y][X]) continue;
    // B번 폭탄을 Y,X,에 설치
    pq.push({B, {Y, X}});
  }

  return 0;
}