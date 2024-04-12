#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;

// 방향 1234: 위 오 아 왼
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct knight {
    int y, x, h, w, hp, maxHp;
};

// 상하좌우 한칸 이동 가능, 연쇄적으로 밀림, 벽 있으면 못밂

int board[42][42];        // 0은 빈칸, 1은 함정, 2는 벽
int knightBoard[42][42];  // 기사 번호
vector<knight> knights;
int L, N, Q;

int check(int y, int x) {  // -2:벽, 0:빈칸, 1~ 기사 번호, 함정은 검사 안 함
    if (board[y][x] == 2)
        return -2;
    else
        return knightBoard[y][x];
}

// 재귀 돌면서 검사, 참이라면 스택에 있는거 하나씩 뽑으면서 옮기면 됨
bool canPush(int id, int d, stack<int>& s) {
    s.push(id);
    int y = knights[id].y;
    int x = knights[id].x;
    int h = knights[id].h;
    int w = knights[id].w;
    set<int> enemies;
    switch (d) {
        case 0:  // 위
            for (int i = 0; i < w; i++) {
                int tmp = check(y - 1, x + i);
                if (tmp == -2) return false;
                enemies.insert(tmp);
            }
            break;
        case 1:  // 오
            for (int i = 0; i < h; i++) {
                int tmp = check(y + i, x + w);
                if (tmp == -2) return false;
                enemies.insert(tmp);
            }
            break;
        case 2:  // 아
            for (int i = 0; i < w; i++) {
                int tmp = check(y + h, x + i);
                if (tmp == -2) return false;
                enemies.insert(tmp);
            }
            break;
        case 3:  // 왼
            for (int i = 0; i < h; i++) {
                int tmp = check(y + i, x - 1);
                if (tmp == -2) return false;
                enemies.insert(tmp);
            }
            break;
    }
    enemies.erase(0);

    for (int i : enemies) {
        if (!canPush(i, d, s)) return false;
    }
    return true;
}

void setScore(int id) {
    int score = 0;
    int y = knights[id].y;
    int x = knights[id].x;
    int h = knights[id].h;
    int w = knights[id].w;
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            if (board[i][j] == 1) score++;
        }
    }
    knights[id].hp -= score;
    if (knights[id].hp <= 0) {
        for (int i = y; i < y + h; i++) {
            for (int j = x; j < x + w; j++) {
                knightBoard[i][j] = 0;
            }
        }
    }
}

void push(int id, int d) {  // i기사가 d방향으로 밀기
    if (knights[id].hp <= 0) return;
    stack<int> s;
    if (!canPush(id, d, s)) return;
    stack<int> s2 = stack<int>(s);
    while (!s2.empty()) {
        s2.pop();
    }
    while (!s.empty()) {
        int curId = s.top();
        s.pop();
        int y = knights[curId].y;
        int x = knights[curId].x;
        int h = knights[curId].h;
        int w = knights[curId].w;
        switch (d) {
            case 0:  // 위
                for (int i = 0; i < w; i++) {
                    knightBoard[y - 1][x + i] = curId;
                    knightBoard[y + h - 1][x + i] = 0;
                }
                knights[curId].y--;
                break;
            case 1:  // 오
                for (int i = 0; i < h; i++) {
                    knightBoard[y + i][x + w] = curId;
                    knightBoard[y + i][x] = 0;
                }
                knights[curId].x++;
                break;
            case 2:  // 아
                for (int i = 0; i < w; i++) {
                    knightBoard[y][x + i] = 0;
                    knightBoard[y + h][x + i] = curId;
                }
                knights[curId].y++;
                break;
            case 3:  // 왼
                for (int i = 0; i < h; i++) {
                    knightBoard[y + i][x + w - 1] = 0;
                    knightBoard[y + i][x - 1] = curId;
                }
                knights[curId].x--;
                break;
        }
        if (curId != id) {
            setScore(curId);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    cin >> L >> N >> Q;
    // 게임판 설정 (체스판 밖도 벽임)
    for (int i = 0; i <= L + 1; i++) {
        board[i][0] = 2;
        board[0][i] = 2;
        board[L + 1][i] = 2;
        board[i][L + 1] = 2;
    }
    for (int y = 1; y <= L; y++)
        for (int x = 1; x <= L; x++) {
            cin >> board[y][x];
            knightBoard[y][x] = 0;
        }

    // 기사 정보
    knights = vector<knight>(N + 1);
    for (int id = 1; id <= N; id++) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        knights[id] = {r, c, h, w, k, k};
        for (int i = r; i < r + h; i++) {
            for (int j = c; j < c + w; j++) {
                knightBoard[i][j] = id;
            }
        }
    }
    // 명령
    while (Q--) {
        int i, d;
        cin >> i >> d;
        push(i, d);
    }
    int totalScore = 0;
    for (int i = 1; i <= N; i++) {
        if (knights[i].hp > 0) totalScore += knights[i].maxHp - knights[i].hp;
    }

    cout << totalScore << endl;
    return 0;
}