#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  long long plus[100000];
  long long minus[100000];
  int plusCnt = 0, minusCnt = 0, zeroCnt = 0;

  for (int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    if (tmp > 0) {
      plus[plusCnt++] = tmp;
    } else if (tmp < 0) {
      minus[minusCnt++] = tmp;
    } else {
      zeroCnt++;
    }
  }

  sort(plus, plus + plusCnt, greater<int>());
  sort(minus, minus + minusCnt, less<int>());

  long long score = 0;

  // 짝 없는애 미리 제거
  if (plusCnt & 1) score += plus[--plusCnt];
  // 절댓값 큰애들 짝지어줌
  for (int i = 0; i < plusCnt; i += 2) {
    long long mul = plus[i] * plus[i + 1];
    long long sum = plus[i] + plus[i + 1];
    score += max(mul, sum);
  }
  // 0이 있으면 혼자노는 음수 죽이기
  // 없으면 마이너스점수
  if (minusCnt & 1) {
    --minusCnt;
    if (!zeroCnt) score += minus[minusCnt];
  }
  // 절댓값 큰애들 짝지어줌
  for (int i = 0; i < minusCnt; i += 2) {
    score += minus[i] * minus[i + 1];
  }
  cout << score;
  return 0;
}