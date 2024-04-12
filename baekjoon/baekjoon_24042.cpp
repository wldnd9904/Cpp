#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int N, M;
vector<vector<pair<int, int>>> graph;  // 목적지, 신호등 순서

struct Node {
    long long time, modTime, curNode;
    bool operator<(const Node& other) const { return time < other.time; }
};

long long solve() {
    priority_queue<Node> pq;  // 실제 시간, (MOD된 시간,현재 위치)
    vector<bool> visited(N + 1, false);
    pq.push({0, 0, 1});
    while (!pq.empty()) {
        auto [time, modTime, curNode] = pq.top();  // 써보고싶었음
        time *= -1;
        pq.pop();
        if (curNode == N) return time;
        if (visited[curNode]) continue;
        visited[curNode] = true;
        for (int i = 0; i < graph[curNode].size(); i++) {
            auto [nextNode, nextTime] = graph[curNode][i];
            if (visited[nextNode]) continue;
            long long cost = nextTime - modTime;
            if (cost < 0) cost += M;
            cost += 1;
            pq.push({-(time + cost), nextTime + 1, nextNode});
        }
    }
    return -1;
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    graph = vector<vector<pair<int, int>>>(N + 1, vector<pair<int, int>>());
    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back({to, i});
        graph[to].push_back({from, i});
    }

    cout << solve() << '\n';

    return 0;
}