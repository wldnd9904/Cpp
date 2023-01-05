#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool pairFirstLess(pair<int, int>, pair<int, int>);
int Answer;

int main(int argc, char **argv)
{
    int T, test_case;

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        int N; // 개미 수
        cin >> N;
        vector<int> vP = vector<int>(N, 0);                            // 위치들
        vector<pair<int, int>> vA = vector<pair<int, int>>(N, {0, 0}); // 개미들
        for (int i = 0; i < N; i++)
        {
            cin >> vP[i];
        }
        for (int i = 0; i < N; i++)
        {
            int A;
            cin >> A;
            vA[i] = {A, i};
        }
        sort(vA.begin(), vA.end(), pairFirstLess);
        Answer = 0;
        for (int i = 0; i < N; i++)
        {
            Answer += abs(vP[vA[i].second] - vP[i]);
        }
        cout << "Case #" << test_case + 1 << endl;
        cout << Answer << endl;
    }

    return 0; // Your program should return 0 on normal termination.
}

bool pairFirstLess(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}