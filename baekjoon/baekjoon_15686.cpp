#include <iostream>
using namespace std;

int myabs(int a) { return a < 0 ? -a : a; }

struct chicken {
    int y, x,
}

int N,
    M;
int board[51][51];
int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    cin >> N >> M;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> board[y][x];
        }
    }
}