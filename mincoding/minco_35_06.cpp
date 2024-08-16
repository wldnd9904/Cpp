#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  int center = 500;
  // 중앙보다 큰애들
  priority_queue<int, vector<int>, greater<int>> bigger;
  // 중앙보다 작은애들
  priority_queue<int, vector<int>, less<int>> smaller;

  bigger.push(1000000000);
  smaller.push(0);

  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);  // b가 더 큰것
    if (a <= center && center <= b) {
      smaller.push(a);
      bigger.push(b);
    }
    // center < a < b 이면 center를 작은쪽에 넣고
    // 오른쪽 탑 포함 셋 중 작은거 하나만 빼고 넣기
    else if (center < a) {
      smaller.push(center);
      center = bigger.top();
      bigger.pop();
      if (center > a) swap(center, a);
      if (center > b) swap(center, b);
      bigger.push(a);
      bigger.push(b);
    } else if (b < center) {
      bigger.push(center);
      center = smaller.top();
      smaller.pop();
      if (center < b) swap(center, b);
      if (center < a) swap(center, a);
      smaller.push(a);
      smaller.push(b);
    }
    cout << center << "\n";
  }

  return 0;
}