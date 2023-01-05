#include <iostream>
#include <vector>
using namespace std;

int Answer, N, K, pivot;
vector<vector<int>> dp;
int divide(int, int);
vector<int> nums;
int main(int argc, char **argv)
{
    int T, test_case;

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        int sum = 0, tmp;
        cin >> N;
        cin >> K;
        dp = vector<vector<int>>(N + 1, vector<int>(K + 1, -1));
        nums = {};
        for (int i = 0; i < N; i++)
        {
            cin >> tmp;
            sum += tmp;
            nums.push_back(tmp);
        }

        cout << endl;
        pivot = sum / K;
        Answer = divide(0, K);
        cout << "Case #" << test_case + 1 << endl;
        cout << Answer % 1000000007 << endl;
    }

    return 0;
}

int divide(int i, int remain)
{
    const int _i = i;
    if (dp[i][remain] != -1)
        return dp[i][remain];
    if (i == N)
    {
        if (remain == 0)
        {
            dp[i][remain] = 1;
            return 1;
        }
        else
        {
            dp[i][remain] = 0;
            return 0;
        }
    }
    int ret = 0, tmp = 0;
    while (i < N)
    {
        tmp += nums[i++];
        if (tmp == pivot)
            ret += divide(i, remain - 1);
        if (tmp > 10 * pivot)
            break;
    }
    dp[_i][remain] = ret;
    return ret;
}