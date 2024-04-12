#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N;
bool solved = false;
int solve(int cur, int bags) {
    if (solved) return 0;
    if (cur > N) return 0;
    if (cur == N) {
        solved = true;
        return bags;
    }
    return solve(cur + 5, bags + 1) + solve(cur + 3, bags + 1);
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    long ret = solve(0, 0);
    cout << (solved ? ret : -1) << "\n";
    cout << (ret) << "\n";
    return 0;
}