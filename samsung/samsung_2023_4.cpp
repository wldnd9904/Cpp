#include <iostream>
using namespace std;

int N, Q;            // 채팅방수, 명령어수
int parent[100001];  // 부모 노드
bool isOpen[100001];
int power[100001];     // 권한(세기)
int send[100001][22];  // 내가 위로 전달할것들 세기별로

void toggleOpen(int id) {
    bool plus = !isOpen[id];
    isOpen[id] = plus;
    int cur = parent[id];
    int maxPower = power[id];
    int curLevel = 1;
    for (int i = maxPower + 1; i <= 21;
         i++) {  // 내가 올릴 것중에 제일 센거 찾기
        if (send[id][i]) maxPower = i;
    }
    while (cur) {
        if (curLevel > maxPower) break;
        for (int i = curLevel; i <= maxPower; i++) {
            send[cur][i - curLevel] += send[id][i] * (plus ? 1 : -1);
        }
        if (!isOpen[cur]) break;
        cur = parent[cur];
        curLevel++;
    }
}
void setMySends(int id, int amount) {
    int curPower = power[id];
    send[id][curPower] += amount;
    if (!isOpen[id]) return;
    int cur = parent[id];
    curPower--;
    while (cur) {  // 부모 따라가면서 올릴 알림 초기화
        if (curPower == -1) break;
        send[cur][curPower] += amount;
        if (!isOpen[cur]) break;
        cur = parent[cur];
        curPower--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //freopen("input.txt", "r", stdin);
    cin >> N >> Q;
    int trash;
    cin >> trash;  // 1번명령:100
    for (int i = 1; i <= N; i++) {
        cin >> parent[i];
        isOpen[i] = true;
        for (int j = 0; j <= 21; j++) {
            send[i][j] = 0;
        }
    }
    for (int i = 1; i <= N; i++) {
        int tmp;
        cin >> tmp;
        power[i] = min(21, tmp);  // 권한 받기
        setMySends(i, 1);
    }
    while (--Q) {
        int input, id, a, b;
        bool aToggled, bToggled;
        cin >> input;
        switch (input) {
            case 200:
                cin >> id;
                toggleOpen(id);
                break;
            case 300:
                int newPower;
                cin >> id >> newPower;
                setMySends(id, -1);
                power[id] = min(21, newPower);
                setMySends(id, 1);
                break;
            case 400:
                cin >> a >> b;
                aToggled = false;
                bToggled = false;
                if (isOpen[a]) {
                    aToggled = true;
                    toggleOpen(a);
                }
                if (isOpen[b]) {
                    bToggled = true;
                    toggleOpen(b);
                }
                swap(parent[a], parent[b]);
                if (aToggled) {
                    toggleOpen(a);
                }
                if (bToggled) {
                    toggleOpen(b);
                }
                break;
            case 500:
                cin >> id;
                int ret = -1;
                for (int i = 0; i <= 21; i++) ret += send[id][i];
                cout << ret << '\n';
                break;
        }
    }

    return 0;
}