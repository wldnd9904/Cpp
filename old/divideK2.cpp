#include <iostream>
#include <vector>
using namespace std;

int Answer, N, K, pivot;
vector<vector<int>> dp;
int make(int);
vector<int> nums;
vector<int> minuses;
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
        minuses = {};
        for (int i = 0; i < N; i++)
        {
            cin >> tmp;
            sum += tmp;
            nums.push_back(tmp);
            if (tmp <= 0)
                minuses.push_back(i);
        }

        cout << endl;
        pivot = sum / K;
        Answer = 0;
        for (int i = 0; i < minuses.size(); i++)
        {
            Answer += make(minuses[i]);
        }
        cout << "Case #" << test_case + 1 << endl;
        cout << Answer % 1000000007 << endl;
    }

    return 0;
}

int make(int pos)
{
    int _pos = pos;
    int ret = 0, tmp = nums[pos];
    int pos1, pos2;
    while (pos > 0)
    {
        tmp += nums[--pos];
        if (tmp == pivot)
        {
            ret += 1;
            break;
        }
        if (tmp > pivot)
            break;
    }
    pos1 = pos;

    pos = _pos;
    tmp = nums[pos];
    while (pos < N)
    {
        tmp += nums[++pos];
        if (tmp == pivot)
        {
            ret += 1;
            break;
        }
        if (tmp > pivot)
            break;
    }
    pos2 = pos;

    for (int i = pos1 + 1; i <= _pos; i++)
    {
        for (int j = i; j < pos2; j++)
        {
            tmp = 0;
            for (int k = i; k <= j; k++)
            {
                tmp += nums[k];
                if (tmp == pivot)
                {
                    ret += 1;
                    break;
                }
                if (tmp > pivot)
                {
                    break;
                }
            }
        }
    }
    return ret;
}