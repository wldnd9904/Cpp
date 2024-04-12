#include <iostream>
#include <string>
#include <vector>

using namespace std;
int dp[50][1000][3];

int outside, tmin, tmax, t, aa, bb, endTime;
vector<int> onBoard;
bool check(int temp) { return tmin <= temp && temp <= tmax; }

int jagwi(int temp, int time, int diff) {  // diff: 0:내린거, 1:그대로, 2:올른거
    if (dp[temp][time][diff] != -1) return dp[temp][time][diff];
    // 손님 있는데 온도안맞으면 리턴
    if (time != 0 && diff == 0 && onBoard[time] && !check(temp)) return 9999999;
    // 시간다되면 리턴
    if (time == endTime) return 0;
    // 꺼서 온도 자동으로 변할때
    int dif = (outside > temp) ? 1 : ((outside < temp) ? -1 : 0);
    int acdif = (outside > t) ? -1 : ((outside < t) ? 1 : 0);
    int a0 = (check(temp + dif) || onBoard[time + 1] == 0)
                 ? jagwi(temp + dif, time + 1, dif + 1)
                 : 9999999;
    // 키고 온도 그대로
    int a1 = (check(temp) || onBoard[time + 1] == 0)
                 ? jagwi(temp, time + 1, 1) + bb
                 : 9999999;
    // 키고 온도 바꿈
    int a2 = (check(temp + acdif) || onBoard[time + 1] == 0)
                 ? jagwi(temp + acdif, time + 1, acdif + 1) + aa
                 : 9999999;
    int ret = min(a0, min(a1, a2));
    dp[temp][time][diff] = ret;
    return ret;
}
int solution(int temperature, int t1, int t2, int a, int b,
             vector<int> onboard) {
    outside = temperature + 10;
    tmin = t1 + 10;
    tmax = t2 + 10;
    t = (tmin + tmax) / 2;
    aa = a;
    bb = b;
    onBoard = onboard;
    endTime = onboard.size() - 1;
    onBoard.push_back(0);
    int answer = jagwi(temperature + 10, 0, 1);
    return answer;
}
int main(void) {
    memset(dp, -1, sizeof(dp));
    // vector<int> onboard = {0, 0, 0, 0, 0, 1, 0};
    // cout << solution(-10, -5, 5, 5, 1, onboard) << endl;
    vector<int> onboard = {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1};
    cout << solution(11, 8, 10, 10, 1, onboard) << endl;
    // vector<int> onboard = {0, 0, 1, 1, 1, 1, 1};
    // cout << solution(28, 18, 26, 10, 8, onboard) << endl;
}