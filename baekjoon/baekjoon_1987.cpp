#include <iostream>
#include <string>
#include <vector>
using namespace std;

int dy[] = {0, -1, 1, 0};
int dx[] = {-1, 0, 0, 1};
int R, C;
vector<vector<char>> map;
vector<bool> visited(100, false);

int mx = 0;
int curCnt = 1;
void solve(int y, int x) {
    mx = max(curCnt, mx);
    for (int dir = 0; dir < 4; dir++) {
        int nextX = x + dx[dir], nextY = y + dy[dir];
        if (nextY >= 0 && nextY < R)
            if (nextX >= 0 && nextX < C) {
                if (!visited[map[nextY][nextX]]) {
                    visited[map[nextY][nextX]] = true;
                    curCnt++;
                    solve(nextY, nextX);
                    visited[map[nextY][nextX]] = false;
                    curCnt--;
                }
            }
    }
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> R >> C;
    for (int y = 0; y < R; y++) {
        vector<char> row;
        for (int x = 0; x < C; x++) {
            char tmp;
            cin >> tmp;
            row.push_back(tmp);
        }
        map.push_back(row);
    }
    visited[map[0][0]] = true;
    solve(0, 0);
    cout << mx;
    return 0;
}