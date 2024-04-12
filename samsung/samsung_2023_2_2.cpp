#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

// t에 x앞에 name 초밥, 회전일어난 직후, 같은위치에 여러개 가능

// name이 t에 x로 앉음. 회전일어난 직후
//  이때부터 x앞에 자기이름인거 n개먹고 떠남
//  이미있으면 착석하자마자 먹음, 여러개 먹을 수 있음

// t에 촬영, 회전 -> 앉아서 먹기 -> 촬영
// 사람 수 / 남은초밥 수

// 사람 좌석은 안 바뀜, 초밥도 무조건 다 먹음 -> 초밥이 사람보다
// 먼저오는지/나중에오는지가 문제 한바퀴 돌고나면 사람이 언제오는지 미리 알 수
// 있음 -> 초밥이 언제 사라지는지 알게됨

struct query {
    int no, t, x;
    string name;
};
struct person {
    int t, x, n;
};
struct newQuery {
    int t, dperson, dsushi, id;
};
struct cmp {
    bool operator()(newQuery a, newQuery b) {
        if (a.t == b.t) return a.dperson > b.dperson;
        return a.t < b.t;
    }
};
int L,
    Q;  // 테이블길이, 쿼리개수
int peopleCnt = 1;
int queryCnt = 0;
map<string, int> nameMap;
vector<query> queries;
person* people[15001];

void saveQuery(int no, int t, int x, string name) {
    queries.push_back({no, t, x, name});
}

void newPerson(string name, int t, int x, int n) {
    nameMap[name] = peopleCnt;
    person* tmp = new person;
    tmp->t = t;
    tmp->x = x;
    tmp->n = n;
    people[peopleCnt] = tmp;
    peopleCnt++;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    cin >> L >> Q;
    while (Q--) {
        int input;
        cin >> input;
        switch (input) {
            case 100: {
                int t, x;
                string name;
                cin >> t >> x;
                cin >> name;
                saveQuery(input, t, x, name);
                break;
            }
            case 200: {
                int t, x, n;
                string name;
                cin >> t >> x >> name >> n;
                newPerson(name, t, x, n);
                saveQuery(input, t, 0, "");
                break;
            }
            case 300: {
                int t;
                cin >> t;
                saveQuery(input, t, 0, "");
                break;
            }
        }
    }

    // 쿼리 저장함, 이제 이걸 한번 가공하고 돌리면 됨
    vector<newQuery> qs;
    for (query& q : queries) {
        switch (q.no) {
            case 100: {
                int id = nameMap[q.name];
                int tEaten;
                // 사람보다 스시가 먼저라면
                if (people[id]->t > q.t) {
                    int placeAtsameTime = ((people[id]->t - q.t) + q.x) % L;
                    if (people[id]->x >= placeAtsameTime)
                        tEaten =
                            people[id]->t + people[id]->x - placeAtsameTime;
                    else
                        tEaten = people[id]->t + L -
                                 (placeAtsameTime - people[id]->x);
                } else {
                    // 스시가 나중에 왔으면
                    if (people[id]->x >= q.x)
                        tEaten = q.t + people[id]->x - q.x;
                    else
                        tEaten = q.t + L - (q.x - people[id]->x);
                }
                qs.push_back({q.t, 0, 1, 0});
                qs.push_back({tEaten, 0, -1, id});
                break;
            }
            case 200:
                qs.push_back({q.t, 1, 0, 0});
                break;
            case 300:
                qs.push_back({q.t, -500, 0, 0});  // -500이면 출력하기
                break;
        }
    }
    sort(qs.begin(), qs.end(), cmp());
    int pp = 0, ps = 0;
    for (newQuery& q : qs) {
        if (q.dperson == -500) {
            cout << pp << ' ' << ps << '\n';
            continue;
        }
        pp += q.dperson;
        ps += q.dsushi;
        if (q.id) {
            people[q.id]->n--;
            if (people[q.id]->n == 0) pp--;
        }
    }
    return 0;
}