#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// N개의 채점기, u0 주어짐 (도메인/id)
// 채점기는 1~N 번호, 우선순위 1인 u0들어옴 (대기큐)

// t초에 우선순위p, url u 들어옴
// 대기큐에 있음, url 중복되면 넘어감

// 도메인이 채점중이면 불가능,
// start ~ start+gap,  ... start+3gap 사이에는 채점못함
// p 낮을수록 빨리, p같으면 들어온 시간순
struct checker {
    bool isChecking;
    int start, id;
};
struct problem {
    int t, p, id, no;
    string uri;
};
struct cmp {
    bool operator()(problem* a, problem* b) const {
        if (a->p == b->p) return a->t > b->t;
        return a->p > b->p;
    }
};
struct domainInfo {
    bool isBeingProcessed;
    int start, canStartAt;
    priority_queue<problem*, vector<problem*>, cmp>
        pq;  // 못돌리는데 돌리라고 요청 들어올 때
             // 임시저장용
};

int N, Q;
priority_queue<problem*, vector<problem*>, cmp> pq;
priority_queue<int, vector<int>, greater<int>>
    availableCheckers;  // 가능한 채점기들
map<string, int> urlToId;
domainInfo domains[301];
checker checkers[50001];
int domainCounter = 0;
set<string> isWaiting = set<string>();

pair<int, int> parseUrl(string u) {
    auto slash = u.find('/');
    string url = u.substr(0, slash);
    if (urlToId.count(url) == 0) {
        domains[domainCounter] = {
            false, 0, 0, priority_queue<problem*, vector<problem*>, cmp>()};
        urlToId[url] = domainCounter++;
    }
    int id = stoi(u.substr(slash + 1, u.size()));
    return {urlToId[url], id};
}

problem* newProblem(int t, int p, int id, int no, string u) {
    problem* ret = new problem();
    ret->t = t;
    ret->p = p;
    ret->id = id;
    ret->no = no;
    ret->uri = u;
    return ret;
}

void init() {
    int trash;
    string u0;
    cin >> trash;  // 100
    cin >> N >> u0;
    for (int i = 1; i <= N; i++) {
        availableCheckers.push(i);
        checkers[i] = {false, -1, -1};
    }
    auto [id, no] = parseUrl(u0);
    pq.push(newProblem(0, 1, id, no, u0));
}

void startCheck(int t) {
    for (int i = 0; i < domainCounter; i++) {
        if (!domains[i].isBeingProcessed && domains[i].canStartAt <= t &&
            !domains[i].pq.empty()) {
            pq.push(domains[i].pq.top());
            domains[i].pq.pop();
        }
    }
    if (availableCheckers.empty()) return;
    // 문제 하나 뽑고
    problem* pr = pq.top();
    // 이미 채점중인지 확인
    // 채점 끝나고 시간 충분히 지났는지 확인
    if (domains[pr->id].isBeingProcessed || domains[pr->id].canStartAt > t) {
        // 안되면 문제별 큐에 넣음
        pq.pop();
        domains[pr->id].pq.push(pr);
        startCheck(t);
    } else {
        // 채점가능하다면 체커에서 하나 선택
        int checkerId = availableCheckers.top();
        availableCheckers.pop();
        // 채점시키기:
        checkers[checkerId].id = pr->id;
        checkers[checkerId].isChecking = true;
        // 문제 start, 채점기 start 갱신
        checkers[checkerId].start = t;
        domains[pr->id].start = t;
        domains[pr->id].isBeingProcessed = true;
        isWaiting.erase(pr->uri);
    }
}

void endCheck(int t, int J_id) {
    if (!checkers[J_id].isChecking) return;
    // 채점기에 있는 문제 아이디 가져오기
    int pid = checkers[J_id].id;
    checkers[J_id].isChecking = false;
    domains[pid].isBeingProcessed = false;
    int canStartAt = t + (t - checkers[J_id].start) * 2;
    domains[pid].canStartAt = canStartAt;
    // 임시저장된 문제 있으면 하나 빼기
    if (!domains[pid].pq.empty()) {
        problem* tmp = domains[pid].pq.top();
        tmp->t = canStartAt;
        pq.push(tmp);
        domains[pid].pq.pop();
    }
    availableCheckers.push(J_id);
}

void print() { cout << isWaiting.size() << '\n'; }

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    cin >> Q;
    init();
    while (--Q) {
        int input;
        cin >> input;
        switch (input) {
            case 200: {
                int t, p;
                string u;
                cin >> t >> p >> u;
                if (isWaiting.count(u)) break;
                auto [id, no] = parseUrl(u);
                pq.push(newProblem(t, p, id, no, u));
                isWaiting.insert(u);
                break;
            }
            case 300: {
                int t;
                cin >> t;
                startCheck(t);
                break;
            }
            case 400: {
                int t, J_id;
                cin >> t >> J_id;
                endCheck(t, J_id);
                break;
            }
            case 500: {
                int t;
                cin >> t;
                print();
                break;
            }
        }
    }
    return 0;
}