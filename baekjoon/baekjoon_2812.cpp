#include <deque>
#include <iostream>
using namespace std;

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, K;
    deque<int> dq;
    cin >> N >> K;
    while (N--) {
        char tmp;
        cin >> tmp;
        tmp -= '0';
        while (K && !dq.empty()) {
            if (dq.back() < tmp) {
                dq.pop_back();
                K--;
            } else
                break;
        }
        dq.push_back(tmp);
    }
    while (K && !dq.empty()) {
        dq.pop_back();
        K--;
    }
    for (int i : dq) {
        cout << i;
    }

    return 0;
}