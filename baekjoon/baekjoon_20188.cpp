#include <iostream>
#include <vector>
using namespace std;
int N;
vector<vector<int>> graph;

struct node {
    long long cnt, depthSum, diversity;
};

node dfs(int parent, int cur) {
    vector<node> v;
    long long depthSum = 0, cnt = 0, diversity = 0;
    for (int next : graph[cur]) {
        if (next != parent) {
            node thisOne = dfs(cur, next);
            depthSum +=
                thisOne.cnt + thisOne.depthSum;  // 깊이합에  개수만큼 1씩더해줌
            cnt += thisOne.cnt;
            diversity +=
                thisOne.cnt + thisOne.depthSum;  // 자식 깊이합 + 자식수만큼
            diversity +=
                thisOne.diversity + (thisOne.cnt * (thisOne.cnt - 1) /
                                     2);  // 자식 다양성 + 자식 조합 수만큼
            v.push_back(thisOne);
        }
    }
    // for (int i = 0; i < v.size(); i++) {
    //     for (int j = i + 1; j < v.size(); j++) {
    //         diversity += v[i].cnt * (v[j].depthSum + v[j].cnt);
    //         diversity += v[j].cnt * (v[i].depthSum + v[i].cnt);
    //     }
    // }
    // 아래로 축약
    for (auto [icnt, idepthSum, idiversity] : v)
        diversity += (depthSum - idepthSum - icnt) * icnt;
    cnt++;
    return {cnt, depthSum, diversity};
}

int main(void) {
    ios_base ::sync_with_stdio(false);
   // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    graph = vector<vector<int>>(N + 1, vector<int>());
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    node result = dfs(0, 1);
    cout << result.diversity;
    return 0;
}