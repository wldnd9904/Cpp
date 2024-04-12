#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N, M;  // 개수, 몇번째인지 알고싶은 문서의 번호
        cin >> N >> M;
        vector<int> v(N);  // priority
        vector<int> priorityCnt(10, 0);
        for (int i = 0; i < N; i++) {
            int priority;
            cin >> priority;
            v[i] = priority;
            priorityCnt[priority]++;
        }
        int cnt = 0, priority = 9, idx = 0;
        while (priority) {
            while (priorityCnt[priority]) {
                if (v[idx] == priority) {
                    priorityCnt[priority]--;
                    cnt++;
                }
                if (idx == M && priority == v[M]) break;
                idx++;
                if (idx == N) idx = 0;
            }
            if (idx == M && priority == v[M]) break;
            priority--;
        }
        cout << cnt << '\n';
    }
    return 0;
}