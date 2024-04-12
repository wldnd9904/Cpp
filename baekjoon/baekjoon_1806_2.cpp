#include <iostream>
#include <queue>
using namespace std;

int N, S;

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> S;
    queue<int> q;
    int sum = 0;
    size_t mi = N;
    int cnt = N;
    while (cnt--) {
        int tmp;
        cin >> tmp;
        q.push(tmp);
        sum += tmp;
        if (sum >= S) {
            while (sum - q.front() >= S) {
                sum -= q.front();
                q.pop();
            }
            mi = min(mi, q.size());
        }
    }
    if (mi == N && sum < S) mi = 0;

    cout << mi << "\n";
    return 0;
}