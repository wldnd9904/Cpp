#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <vector>
using namespace std;
bool find(list<int> l, int i) {
    for (int li : l) {
        if (li == i || li == 0) return true;
    }
    return false;
}

struct bfsNode {
    int x, y, dist;
    int crashId;
};
int crashIdCounter = 1;
struct cmp {
    bool operator()(bfsNode* a, bfsNode* b) { return a->crashId > b->crashId; }
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int X, Y;
vector<vector<bool>> maze;
vector<vector<list<int>>> visited;  // crashId로 채워넣음
priority_queue<bfsNode*, vector<bfsNode*>, cmp> pq;
int main(void) {
    ios_base::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> Y >> X;
    for (int i = 0; i < Y; i++) {
        string tmp;
        cin >> tmp;
        vector<bool> row(X);
        for (int j = 0; j < X; j++) row[j] = tmp[j] - '0';
        maze.push_back(row);
    }
    bfsNode* start = new bfsNode();
    start->x = 0;
    start->y = 0;
    visited = vector<vector<list<int>>>(Y, vector<list<int>>(X, list<int>()));
    start->dist = 1;
    start->crashId = 0;
    visited[0][0].push_back(0);
    pq.push(start);

    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        // cout << node->x << node->y << node->crashId << endl;
        if (node->x == X - 1 && node->y == Y - 1) {
            // while (!pq.empty()) {
            //     delete pq.top();
            //     pq.pop();
            // }
            cout << node->dist << endl;
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int newx = node->x + dx[i];
            int newy = node->y + dy[i];
            if (newx < 0 || newx >= X) continue;
            if (newy < 0 || newy >= Y) continue;
            if (find(visited[newy][newx], node->crashId)) continue;
            if (node->crashId && maze[newy][newx]) continue;
            bfsNode* next = new bfsNode();
            next->x = newx;
            next->y = newy;
            next->dist = node->dist + 1;
            if (!node->crashId && maze[newy][newx])
                next->crashId = crashIdCounter;
            else
                next->crashId = node->crashId;
            visited[newy][newx].push_back(next->crashId);
            pq.push(next);
        }
        delete node;
    }
    cout << -1;
    return 0;
}