#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
int N, wormHead = -1;
vector<bool> visited;
vector<vector<pair<int, int>>> graph;      // 목적지 ,거리
vector<vector<pair<int, int>>> candidate;  // 어디서왔는지, 얼마나왔는지
vector<int> dp;
queue<int> cross;

// 모든 리프노드에서 갈림길 나올때까지 따라올라감
void solve1(int cur, int prev, int curLength, bool started = false) {
    if (started && graph[cur].size() != 1) return;
    if (!started && graph[cur].size() == 1) {  // 리프노드 찾았으면 지렁이모양
        wormHead = cur;
        return;
    }
    if (graph[cur].size() <= 2) {
        for (auto [dest, length] : graph[cur]) {
            if (dest == prev) continue;
            solve1(dest, cur, curLength + length);
        }
        return;
    }
    // 3개 이상의 갈림길이면 후보로 등록해놓고 나중에 보기위해 큐에넣음
    cross.push(cur);
    candidate[cur].push_back({prev, curLength});
}

// 지렁이모양이면 한쪽에서 반대쪽으로 가면서 dp 채우기
void solve2(int cur, int prev, int curLength, bool started = false) {
    if (!started && graph[cur].size() == 1) {  // 꼬리 찾았으면 갱신
        wormHead = cur;
        return;
    }
    dp[cur] = max(dp[cur], curLength);
    for (auto [dest, length] : graph[cur]) {
        if (dest == prev) continue;
        solve2(dest, cur, curLength + length);
    }
    return;
}

// 루트에서 내려가면서 dp 채우기
void solve3(int cur, int prev, int curLength, bool started = false) {
    dp[cur] = curLength;
    if (graph[cur].size() == 1) return;
    int maxLength = curLength, secondLength = 0, maxDest = prev;
    // 루트로부터 내려온 길 + 찾아놓은 후보지들중 젤 긴거 고름
    for (auto [from, length] : candidate[cur]) {
        if (length > maxLength) {
            secondLength = maxLength;
            maxLength = length;
            maxDest = from;
        } else if (length == maxLength) {
            secondLength = length;
        } else {
            secondLength = max(secondLength, length);
        }
    }
    // 다시 따라내려가기
    for (auto [dest, length] : graph[cur]) {
        if (dest == prev) continue;
        if (dest == maxDest)  // 지가 온 길이 제일 길면 2등길에서 왔다고함
            solve3(dest, cur, secondLength + length);
        else  // 그게아니면 제일 긴 곳에서 왔다고함
            solve3(dest, cur, maxLength + length);
    }
    dp[cur] = maxLength;
    return;
}

int main(void) {
    ios_base ::sync_with_stdio(false);
   // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    graph = vector<vector<pair<int, int>>>(N + 1, vector<pair<int, int>>());
    candidate = vector<vector<pair<int, int>>>(N + 1, vector<pair<int, int>>());
    visited = vector<bool>(N + 1, false);
    dp = vector<int>(N + 1, 0);
    int root = -1;
    for (int i = 0; i < N - 1; i++) {
        int from, to, length;
        cin >> from >> to >> length;
        graph[from].push_back({to, length});
        graph[to].push_back({from, length});
    }
    // 모든 리프노드에서 갈림길 나올때까지 따라올라감
    for (int i = 1; i <= N; i++) {
        solve1(i, 0, 0, true);
        if (wormHead != -1)
            break;  // 루트(리프노드) 찾았다면 지렁이모양인것, 바로탈출
    }

    // 갈림길 다시 올라가면서 그다음 갈림길 찾음
    while (!cross.empty()) {
        int cur = cross.front();
        cross.pop();
        if (visited[cur]) continue;
        // 전부 온곳이라면 탐색끝난거, 루트로 삼기
        if (candidate[cur].size() == graph[cur].size()) {
            root = cur;
            break;
        }
        // 길 하나만 안간곳이어야됨
        if (candidate[cur].size() != graph[cur].size() - 1) {
            cross.push(cur);
            continue;
        }
        visited[cur] = true;

        int lengthMax = 0;
        map<int, bool> candidates;
        for (auto [from, length] : candidate[cur]) {
            lengthMax = max(lengthMax, length);
            candidates[from] = true;
        }
        for (auto [dest, length] : graph[cur]) {
            if (candidates.count(dest)) continue;
            solve1(dest, cur, lengthMax + length);
        }
    }

    // 지렁이모양이면 끝에서 끝으로 샥 갔다오면서 최고값 갱신
    if (wormHead != -1) {
        solve2(wormHead, -1, 0, true);  // 출발
        solve2(wormHead, -1, 0, true);  // 갔다오기
    }
    // 루트가 있으면 거기서부터 내려가면서 dp 채우기
    if (root != -1) {
        solve3(root, -1, 0, true);
    }
    for (int i = 1; i <= N; i++) {
        cout << dp[i] << '\n';
    }
    return 0;
}