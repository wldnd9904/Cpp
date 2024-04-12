#include <iostream>
#include <vector>
using namespace std;

int myabs(int a) { return (a < 0) ? -a : a; }

// 산타: 상우하좌, 루돌프는 대각선까지
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

// 상호작용: 원래 있던 산타는 한칸 밀려남, 연쇄 가능

// 기절: 루돌프랑 충돌하면 한 턴 기절

struct santa {
    int y, x, score, isStunnedTo;
    bool isDead;
};

int N, M, P, C, D, turn = 0;  // 판크기, 총 턴수, 산타 수
int Rx, Ry;
int board[52][52] = {0};  // 게임판, 가장자리 테두리 -1 있음
vector<santa> santas;     // 산타들, 0번은 비움

int dist(int ay, int ax, int by, int bx) {
    return (by - ay) * (by - ay) + (bx - ax) * (bx - ax);
}
int dst(int target) { return dist(Ry, Rx, santas[target].y, santas[target].x); }
int biasedDst(int target, int y, int x) {
    return dist(Ry, Rx, santas[target].y + y, santas[target].x + x);
}

// 최초 호출 시 보드 상 이전위치는 따로 갱신해줘야됨
void processCollision(int curTarget, int y, int x, int dy, int dx) {
    if (curTarget == 0) return;
    int afterX = x + dx, afterY = y + dy;
    santas[curTarget].y = afterY;
    santas[curTarget].x = afterX;
    int nextTarget = board[afterY][afterX];
    if (nextTarget == -1) {
        santas[curTarget].isDead = true;
    } else {
        board[afterY][afterX] = curTarget;
        processCollision(nextTarget, afterY, afterX, dy, dx);
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    // freopen("input.txt", "r", stdin);

    cin >> N >> M >> P >> C >> D;
    santas = vector<santa>(P + 1, {0, 0, 0, 0, false});

    // 보드 초기화 및 테두리 설치
    for (int y = 1; y <= 51; y++)
        for (int x = 1; x <= 51; x++) board[y][x] = 0;
    for (int i = 0; i <= N + 1; i++) {
        board[0][i] = -1;
        board[i][0] = -1;
        board[i][N + 1] = -1;
        board[N + 1][i] = -1;
    }
    // 루돌프 초기화
    cin >> Ry >> Rx;
    // 산타 초기화
    for (int i = 1; i <= P; i++) {
        int no, x, y;
        cin >> no >> y >> x;
        board[y][x] = no;
        santas[no] = {y, x, 0, 0, false};
    }
    while (turn < M) {
        turn++;
        int target = 0, targetDist = 2147483647;
        // 루돌프: 가장 가까운 산타한테 돌진
        for (int i = 1; i <= P; i++) {
            if (santas[i].isDead) continue;
            int d = dst(i);
            if (d < targetDist) {
                target = i;
                targetDist = d;
                continue;
            }
            // y좌표 큰거우선, x좌표 큰거우선
            if (d == targetDist) {
                if (santas[target].y < santas[i].y) {
                    target = i;
                    continue;
                } else if (santas[target].y == santas[i].y) {
                    if (santas[target].x < santas[i].x) {
                        target = i;
                        continue;
                    }
                }
            }
        }
        // 산타 다뒤졌으면 종료
        if (target == 0) break;
        int targetX = santas[target].x;
        int targetY = santas[target].y;
        int Rdx = targetX - Rx == 0 ? 0 : (targetX - Rx) / myabs(targetX - Rx);
        int Rdy = targetY - Ry == 0 ? 0 : (targetY - Ry) / myabs(targetY - Ry);
        Rx += Rdx;
        Ry += Rdy;
        // 충돌: 루돌프가 움직였으면 산타가 C점수 얻고 그 방향으로 C칸
        // 밀려남
        if (targetX == Rx && targetY == Ry) {
            int afterTargetX = targetX + Rdx * C;
            int afterTargetY = targetY + Rdy * C;
            santas[target].score += C;
            santas[target].isStunnedTo = turn + 1;
            // 게임판 밖이면 사망, 산타끼리 부딪히면 상호작용
            if (afterTargetX < 1 || afterTargetY < 1 || afterTargetX > N ||
                afterTargetY > N) {
                santas[target].isDead = true;
                board[Ry][Rx] = 0;
            } else {
                santas[target].y = afterTargetY;
                santas[target].x = afterTargetX;
                processCollision(board[afterTargetY][afterTargetX],
                                 afterTargetY, afterTargetX, Rdy, Rdx);
                board[afterTargetY][afterTargetX] = target;
                board[Ry][Rx] = 0;
            }
        }

        // 산타: 루돌프에게 가장 가까워지는 방향으로
        for (int i = 1; i <= P; i++) {
            if (santas[i].isDead || santas[i].isStunnedTo >= turn) continue;
            int dir = -1, minDst = dst(i);
            int curY = santas[i].y, curX = santas[i].x;
            for (int d = 0; d < 4; d++) {
                if (board[curY + dy[d]][curX + dx[d]] != 0) continue;
                int tmpDst = biasedDst(i, dy[d], dx[d]);
                if (tmpDst < minDst) {
                    minDst = tmpDst;
                    dir = d;
                }
            }
            if (dir != -1) {
                board[curY][curX] = 0;
                curY += dy[dir];
                curX += dx[dir];
                // 가까운쪽으로 움직이려는데 두곳이 막히면 안움직일듯
                // 산타가 움직였으면 산타는 D만큼 얻고 산타 방향 반대로
                // D칸 밀려남
                if (curY == Ry && curX == Rx) {
                    curY = Ry - dy[dir] * D;
                    curX = Rx - dx[dir] * D;
                    santas[i].score += D;
                    santas[i].isStunnedTo = turn + 1;
                    // 게임판 밖이면 사망, 산타끼리 부딪히면 상호작용
                    if (curY < 1 || curX < 1 || curY > N || curX > N) {
                        santas[i].isDead = true;
                    } else {
                        santas[i].y = curY;
                        santas[i].x = curX;

                        processCollision(board[curY][curX], curY, curX,
                                         -dy[dir], -dx[dir]);
                        board[curY][curX] = i;
                    }
                } else {
                    santas[i].x = curX;
                    santas[i].y = curY;
                    board[curY][curX] = i;
                }
            }
        }
        for (int i = 1; i <= P; i++) {
            if (santas[i].isDead) continue;
            santas[i].score++;
        }
    }
    for (int i = 1; i <= P; i++) {
        cout << santas[i].score << " ";
    }
    return 0;
}