#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int V;
vector<vector<pair<int, int>>> graph;  // 목적지, 가중치
vector<bool> visited;
int maxLength = -1;
int maxLengthDest = -1;
void dfs(int cur, int curLength) {
    visited[cur] = true;
    if (graph[cur].size() == 1 && curLength > maxLength) {
        maxLength = curLength;
        maxLengthDest = cur;
    }
    for (auto [dest, length] : graph[cur]) {
        if (visited[dest]) continue;
        dfs(dest, curLength + length);
    }
}
void dfs2(int cur, int curLength) {
    visited[cur] = true;
    if (graph[cur].size() == 1 && curLength > maxLength) {
        maxLength = curLength;
    }
    for (auto [dest, length] : graph[cur]) {
        if (visited[dest]) continue;
        dfs2(dest, curLength + length);
    }
}
int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> V;
    graph = vector<vector<pair<int, int>>>(V + 1, vector<pair<int, int>>());
    visited = vector<bool>(V + 1, false);
    for (int i = 0; i < V; i++) {
        int from;
        cin >> from;
        while (true) {
            int to, length;
            cin >> to;
            if (to == -1) break;
            cin >> length;
            graph[from].push_back({to, length});
            // graph[to].push_back({from, length}); -- 입력에서 양방향
            // 주는거였음;;
        }
    }
    dfs(1, 0);
    visited = vector<bool>(V + 1, false);
    dfs2(maxLengthDest, 0);
    cout << maxLength << '\n';

    return 0;
}