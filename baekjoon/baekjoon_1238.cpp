#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M, X;

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> X;
    vector<vector<pair<int, int>>> edges(N + 1, vector<pair<int, int>>());
    vector<vector<pair<int, int>>> reverseEdges(N + 1,
                                                vector<pair<int, int>>());
    for (int i = 0; i < M; i++) {
        int start, end, dist;
        cin >> start >> end >> dist;
        edges[start].push_back({end, dist});
        reverseEdges[end].push_back({start, dist});
    }

    vector<int> dijk1(N + 1, 2147483647);  // 정방향
    vector<int> dijk2(N + 1, 2147483647);  // 역방향
    priority_queue<pair<int, int>> pq;
    pq.push({0, X});
    while (!pq.empty()) {
        int curDist = -pq.top().first;
        int curPlace = pq.top().second;
        pq.pop();
        if (dijk1[curPlace] < curDist) continue;
        dijk1[curPlace] = curDist;
        for (auto edge : edges[curPlace])
            if (curDist + edge.second < dijk1[edge.first])
                pq.push({-(curDist + edge.second), edge.first});
    }
    pq.push({0, X});
    while (!pq.empty()) {
        int curDist = -pq.top().first;
        int curPlace = pq.top().second;
        pq.pop();
        if (dijk2[curPlace] < curDist) continue;
        dijk2[curPlace] = curDist;
        for (auto edge : reverseEdges[curPlace])
            if (curDist + edge.second < dijk2[edge.first])
                pq.push({-(curDist + edge.second), edge.first});
    }
    int mx = -1;
    for (int i = 1; i <= N; i++) mx = max(mx, dijk1[i] + dijk2[i]);
    cout << mx;

    return 0;
}