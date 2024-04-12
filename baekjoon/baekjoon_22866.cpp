#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N), vLeft(N), vRight(N), vCnt(N);
    stack<pair<int, int>> s;
    for (int i = 0; i < N; i++) {
        int height;
        cin >> height;
        v[i] = height;
    }
    // 오른쪽으로 가면서 채우기
    for (int i = 0; i < N; i++) {
        while (!s.empty() && s.top().second <= v[i]) s.pop();
        vCnt[i] = s.size();
        vLeft[i] = s.empty() ? -1 : s.top().first;
        if (s.empty() || s.top().second > v[i]) s.push({i, v[i]});
    }
    s = stack<pair<int, int>>();
    // 반대로
    for (int i = N - 1; i >= 0; i--) {
        while (!s.empty() && s.top().second <= v[i]) s.pop();
        vCnt[i] += s.size();
        vRight[i] = s.empty() ? -1 : s.top().first;
        if (s.empty() || s.top().second > v[i]) s.push({i, v[i]});
    }
    // 출력
    for (int i = 0; i < N; i++) {
        cout << vCnt[i] << ' ';
        if (vCnt[i]) {
            if (vLeft[i] == -1)
                cout << vRight[i] + 1;
            else if (vRight[i] == -1)
                cout << vLeft[i] + 1;
            else
                cout << ((i - vLeft[i] <= vRight[i] - i) ? vLeft[i] + 1
                                                         : vRight[i] + 1);
        }
        cout << '\n';
    }

    return 0;
}
