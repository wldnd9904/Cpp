#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);

    int T = 1;
    while (true) {
        int N;
        cin >> N;
        if (N == 0) return 0;
        vector<int> map;
        for (int y = 0; y < N * N; y++) {
            int input;
            cin >> input;
            map.push_back(input);
        }

        vector<int> dijk(N * N, 2147483647);
        priority_queue<pair<int, int>> pq;  // 현재 거리, 정점넘버
        pq.push({-map[0], 0});
        while (!pq.empty()) {
            int curNode = pq.top().second;
            int curDist = -pq.top().first;
            pq.pop();
            if (dijk[curNode] <= curDist) continue;
            dijk[curNode] = curDist;
            if (curNode % N != 0)
                pq.push({-(curDist + map[curNode - 1]), curNode - 1});
            if (curNode % N != N - 1)
                pq.push({-(curDist + map[curNode + 1]), curNode + 1});
            if (curNode + N < N * N)
                pq.push({-(curDist + map[curNode + N]), curNode + N});
            if (curNode >= N)
                pq.push({-(curDist + map[curNode - N]), curNode - N});
        }

        cout << "Problem " << T++ << ": " << dijk[N * N - 1] << endl;
    }
}