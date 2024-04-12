#include <chrono>
#include <iostream>
#include <queue>
using namespace std;
typedef struct {
    int N;
    vector<vector<int>> matrix;
} test_item;

typedef struct {
    int now, cost;
    vector<bool> visited;
} cycle_item;

int solve(int N, vector<vector<int>> matrix) {
    // 비용 우선순위큐, 사이클 아이템 큐
    priority_queue<int, vector<int>, greater<int>> pq;
    queue<cycle_item> q;
    // 큐 초기화
    for (int i = 0; i < N; i++) {
        cycle_item item;
        item.cost = 0;
        item.now = i;
        item.visited = vector<bool>(N, false);
        item.visited[i] = true;
        q.push(item);
    }
    pq.push(9999999);
    // 큐가 빌 때까지 돌리기
    while (!q.empty()) {
        cycle_item item = q.front();
        q.pop();
        if (item.cost >= pq.top()) continue;
        for (int i = 0; i < N; i++) {
            if (matrix[item.now][i] > 0) {
                if (item.visited[i]) {  // 사이클 형성되면 우선순위큐 삽입 (-ㅇ
                                        // 모양이어도 상관없음)
                    pq.push(item.cost + matrix[item.now][i]);
                } else {  // 아니면 사이클 아이템 큐에 삽입
                    cycle_item tmp = cycle_item(item);
                    tmp.cost += matrix[item.now][i];
                    tmp.visited[i] = true;
                    tmp.now = i;
                    q.push(tmp);
                }
            }
        }
    }
    if (pq.size() == 1)
        return -1;
    else
        return pq.top();
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;  // 테스트 수
    test_item tc[T];
    for (int i = 0; i < T; i++) {
        int N, M;  // 학생수, 마니또관계수  (2 ≤ N ≤ 400, 2 ≤ M ≤ N * (N - 1))
        std::cin >> N >> M;
        vector<vector<int>> matrix(N, vector<int>(N, 0));
        for (int j = 0; j < M; j++) {
            int a, b, c;
            std::cin >> a >> b >> c;
            matrix[a - 1][b - 1] = c;
        }
        tc[i] = {N, matrix};
    }
    for (int i = 0; i < T; i++) {
        cout << "#" << i + 1 << " " << solve(tc[i].N, tc[i].matrix) << "\n";
    }
    return 0;
}
