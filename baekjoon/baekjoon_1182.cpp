#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M;
    cin >> N >> M;
    // 점이 두개이하면 애초에 안됨
    if (N <= 2) {
        cout << -1 << '\n';
        return 0;
    }
    vector<vector<pair<int, int>>> graph = vector<vector<pair<int, int>>>(
        N + 1, vector<pair<int, int>>());  // 목적지, 간선id

    vector<bool> vertexVisited(N + 1, false);
    vector<int> tree1;
    vector<int> tree1Edges;
    int vertexLeft = N - 1;

    for (int i = 1; i <= M; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back({v2, i});
        graph[v2].push_back({v1, i});
    }
    // spanning tree1
    queue<int> q;
    q.push(1);
    vertexVisited[1] = true;
    int cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        tree1.push_back(cur);
        for (auto [next, id] : graph[cur]) {
            if (vertexVisited[next]) continue;
            vertexVisited[next] = true;
            vertexLeft--;
            tree1Edges.push_back(id);
            q.push(next);
        }
    }
    // 모든 점 다 찾았으면 하나만 빼고 트리라고 우기기 (cur 이 마지막으로
    // 본 노드이자 트리2)
    if (vertexLeft == 0) {
        cout << N - 1 << ' ' << 1 << '\n';
        for (int i = 1; i <= N; i++)
            if (i != cur) cout << i << ' ';
        cout << '\n';
        for (int i = 0; i < tree1Edges.size() - 1; i++) {
            cout << tree1Edges[i] << ' ';
        }
        cout << '\n';
        cout << cur << "\n\n";
        return 0;
    }
    // 점이 남았다면 트리 한개 더 만들어보기
    vector<int> tree2;
    vector<int> tree2Edges;
    // 남은것들 돌면서 방문안한거 찾음
    int tree2Start;
    for (int i = 1; i <= N; i++) {
        if (!vertexVisited[i]) {
            tree2Start = i;
            break;
        }
    }
    // spanning tree2
    vertexVisited[tree2Start] = true;
    vertexLeft--;
    q.push(tree2Start);
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        tree2.push_back(cur);
        for (auto [next, id] : graph[cur]) {
            if (vertexVisited[next]) continue;
            vertexVisited[next] = true;
            vertexLeft--;
            tree2Edges.push_back(id);
            q.push(next);
        }
    }

    // 이래도 남았거나 크기 같으면 안됨
    if (vertexLeft || tree1.size() == tree2.size()) {
        cout << -1 << '\n';
        return 0;
    }
    cout << tree1.size() << ' ' << tree2.size() << '\n';
    for (int i : tree1) cout << i << ' ';
    cout << '\n';
    for (int i : tree1Edges) cout << i << ' ';
    cout << '\n';
    for (int i : tree2) cout << i << ' ';
    cout << '\n';
    for (int i : tree2Edges) cout << i << ' ';
    cout << '\n';
    return 0;
}
