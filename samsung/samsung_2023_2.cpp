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

struct person {
    int t, x, n;
};
int L,
    Q;  // 길이, 명령수
int T = 1;
map<string, list<pair<int, int>>> table;  // 사람이름별 놓은시간/자리

map<string, person> people;  // 온 시간, 자리, 남은 초밥

void processAndPrint(int t) {
    vector<string> names;
    for (auto tit = table.begin(); tit != table.end(); tit++) {
        auto name = tit->first;
        if (!people.count(name)) continue;
        int sitTime = people[name].t;
        int sitPlace = people[name].x;
        for (auto it = tit->second.begin(); it != tit->second.end();) {
            int putTime = it->first;
            int putPlace = it->second;
            if (putTime < sitTime) {  // 앉기 전에 놓여있던건 앉을때기준으로
                                      // 바꿈
                putPlace = it->second = (putPlace + sitTime - putTime) % L;
                putTime = it->first = sitTime;
            }
            // 놓인 시점에서 현재시간까지 초밥이 한바퀴 돌았으면 무조건 먹은 것
            if (t - putTime >= L) {
                people[name].n--;
                it = tit->second.erase(it);
                continue;
            }
            // 아니면 처음 초밥 위치 ~ 현재 초밥 위치가 앉은 자리를
            // 지나야함
            int afterPlace = (putPlace + (t - putTime)) % L;
            if (putPlace <= afterPlace) {
                if (putPlace <= sitPlace && sitPlace <= afterPlace) {
                    people[name].n--;
                    it = tit->second.erase(it);
                    continue;
                }
            } else {
                if (!(afterPlace < sitPlace && sitPlace < putPlace)) {
                    people[name].n--;
                    it = tit->second.erase(it);
                    continue;
                }
            }
            it++;
        }
        if (people[name].n <= 0) {
            names.push_back(name);
        }
    }
    for (auto name : names) {
        people.erase(name);
        table.erase(name);
    }
    int sushi = 0;
    for (auto sushies : table) {
        sushi += sushies.second.size();
    }
    cout << people.size() << ' ' << sushi << '\n';
}

void enter(int t, int x, string name, int n) { people[name] = {t, x, n}; }

void put(int t, int x, string name) {
    if (!table.count(name)) table[name] = list<pair<int, int>>();
    table[name].push_back({t, x});
    return;
};

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
                put(t, x, name);
                break;
            }
            case 200: {
                int t, x, n;
                string name;
                cin >> t >> x >> name >> n;
                enter(t, x, name, n);
                break;
            }
            case 300: {
                int t;
                cin >> t;
                processAndPrint(t);
                break;
            }
        }
    }

    return 0;
}