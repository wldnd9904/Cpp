#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int L, RANGE, DMG, AMMO;
  cin >> L >> RANGE >> DMG >> AMMO;
  int MAXDMG = RANGE * DMG;
  queue<int> pq;
  int accDmg = 0;
  for (int i = 0; i < L; i++) {
    int zombie;
    cin >> zombie;
    accDmg += DMG;
    if (accDmg > MAXDMG) accDmg = MAXDMG;
    while (!pq.empty() && pq.front() > RANGE - i) pq.pop();
    int totalDmg = accDmg - pq.size() * DMG;
    if (zombie > totalDmg) {
      if (AMMO == 0) {
        cout << "NO";
        return 0;
      }
      AMMO--;
      pq.push(-i);
    }
  }
  cout << "YES";
  return 0;
}