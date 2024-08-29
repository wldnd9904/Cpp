#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  int myScore[100000];
  int sorted[100000];
  int total[100000];
  for (int i = 0; i < N; i++) {
    cin >> myScore[i];
    sorted[i] = myScore[i];
    total[i] = myScore[i];
  }
  sort(sorted, sorted + N, greater<int>());
  for (int i = 0; i < N; i++) {
    cout << lower_bound(sorted, sorted + N, myScore[i], greater<int>()) -
                sorted + 1
         << " ";
  }
  cout << "\n";

  for (int i = 0; i < N; i++) {
    cin >> myScore[i];
    sorted[i] = myScore[i];
    total[i] += myScore[i];
  }
  sort(sorted, sorted + N, greater<int>());
  for (int i = 0; i < N; i++) {
    cout << lower_bound(sorted, sorted + N, myScore[i], greater<int>()) -
                sorted + 1
         << " ";
  }
  cout << "\n";
  for (int i = 0; i < N; i++) {
    cin >> myScore[i];
    sorted[i] = myScore[i];
    total[i] += myScore[i];
  }
  sort(sorted, sorted + N, greater<int>());
  for (int i = 0; i < N; i++) {
    cout << lower_bound(sorted, sorted + N, myScore[i], greater<int>()) -
                sorted + 1
         << " ";
  }
  cout << "\n";
  for (int i = 0; i < N; i++) {
    sorted[i] = total[i];
  }
  sort(sorted, sorted + N, greater<int>());
  for (int i = 0; i < N; i++) {
    cout << lower_bound(sorted, sorted + N, total[i], greater<int>()) - sorted +
                1
         << " ";
  }
  cout << "\n";

  return 0;
}