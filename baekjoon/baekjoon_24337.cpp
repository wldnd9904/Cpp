#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, a, b;
    cin >> N >> a >> b;
    if (a + b > N + 1) {
        cout << -1;
        return 0;
    }
    vector<int> v(N, 1);
    for (int i = 1; i < b; i++) v[N - i] = i;
    int highest = max(a, b);
    if (a == 1) {
        v[0] = highest;
    } else {
        v[N - b] = highest;
        int j = 1;
        for (int i = N - b - a + 1; i < N - b; i++) {
            v[i] = j++;
        }
    }
    for (int i = 0; i < N; i++) {
        cout << v[i] << ' ';
    }

    return 0;
}
