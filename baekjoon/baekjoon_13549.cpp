#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int N, K;
int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;
    vector<bool> visited(200000, false);
    q.push({0, N});
    visited[N] = true;
    while (!q.empty()) {
        pair<int, int> cur = q.top();
        q.pop();
        int curX = cur.second;
        if (curX == K) {
            cout << cur.first << '\n';
            return 0;
        }
        if (curX != 0) {
            while (curX <= K) {
                curX *= 2;
                if (!visited[curX]) q.push({cur.first, curX});
                visited[curX] = true;
            }
        }
        if (cur.second != 0 && !visited[cur.second - 1]) {
            q.push({cur.first + 1, cur.second - 1});
            visited[cur.second - 1] = true;
        }
        if (!visited[cur.second + 1]) {
            q.push({cur.first + 1, cur.second + 1});
            visited[cur.second + 1] = true;
        }
    }
    return 0;
}