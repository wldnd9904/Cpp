#include <iostream>
#include <string>
#include <vector>

using namespace std;
int waitedTime(vector<vector<int>> reqs, int k) {
    vector<int> end(k, 0);
    int answer = 0;
    for (vector<vector<int>>::iterator it = reqs.begin(); it != reqs.end();
         it++) {
        bool matched = false;
        vector<int> req = *it;
        for (int candi = 0; candi < k; candi++) {
            if (end[candi] <= req[0]) {
                end[candi] = req[0] + req[1];
                matched = true;
                break;
            }
        }
        if (!matched) {
            int idx = min_element(end.begin(), end.end()) - end.begin();
            answer += end[idx] - req[0];
            end[idx] = end[idx] + req[1];
        }
    }
    return answer;
}
int solution(int k, int n, vector<vector<int>> reqs) {
    vector<vector<vector<int>>> dividedReqs(k);
    int nleft = n - k;
    vector<int> ns(k, 1);
    vector<int> times(k, 0);
    int answer = 0;
    for (vector<vector<int>>::iterator it = reqs.begin(); it != reqs.end();
         it++) {
        vector<int> req = *it;
        dividedReqs[req[2] - 1].push_back(req);
    }
    for (int i = 0; i < k; i++) {
        times[i] = waitedTime(dividedReqs[i], ns[i]);
    }
    while (nleft > 0) {
        int idx = max_element(times.begin(), times.end()) - times.begin();
        ns[idx]++;
        times[idx] = waitedTime(dividedReqs[idx], ns[idx]);
        nleft--;
    }
    for (int i = 0; i < k; i++) {
        answer += times[i];
        cout << ns[i] << " " << times[i] << endl;
    }
    return answer;
}

int main(void) {
    vector<vector<int>> reqs = {
        {10, 60, 1}, {15, 100, 3}, {20, 30, 1}, {30, 50, 3},
        {50, 40, 1}, {60, 30, 2},  {65, 30, 1}, {70, 100, 2},
    };
    cout << solution(3, 5, reqs) << endl;
    // vector<vector<int>> reqs = {
    //     {5, 55, 2}, {10, 90, 2}, {20, 40, 2}, {50, 45, 2}, {100, 50, 2}};
    // cout << solution(2, 3, reqs) << endl;
}