#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    queue<int>* q[21];
    for (int i = 2; i < 21; i++) {
        q[i] = new queue<int>();
    }
    int N, K;
    long ret = 0;
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        int n = s.size();
        while (!q[n]->empty() && q[n]->front() < i - K) q[n]->pop();
        ret += q[n]->size();
        q[n]->push(i);
    }
    cout << ret << "\n";
}