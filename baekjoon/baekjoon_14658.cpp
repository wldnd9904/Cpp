#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int X, Y, L, K;
vector<pair<int, int>> v;  // x 기준 정렬됨
int mx = 0;
void solve(int y) {  // y가 정해져있을때 x기준으로 검사
    queue<int> q;
    for (auto star : v) {
        if (star.second < y || star.second >= y + L) continue;
        q.push(star.first);
        while (!q.empty() && star.first - q.front() + 1 > L) q.pop();
        mx = max(mx, (int)q.size());
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> X >> Y >> L >> K;
    L += 2;
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < K; i++) solve(v[i].second);

    cout << K - mx;
    return 0;
}