#include <iostream>
#include <vector>
using namespace std;
const int MIN = numeric_limits<int>::min();
const vector<int> v = {-7, 4, -3, 6, 3, -8, 3, 4};

int inefficientMaxSum(const vector<int> &A) // O(n^3)
{
    int N = A.size(), ret = MIN;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int sum = 0;
            for (int k = i; k <= j; ++k)
            {
                sum += A[k];
            }
            ret = max(ret, sum);
        }
    }
    return ret;
}

int betterMaxSum(const vector<int> &A) // O(n^2)
{
    int N = A.size(), ret = MIN;
    for (int i = 0; i < N; ++i)
    {
        int sum = 0;
        for (int j = i; j < N; ++j)
        {
            sum += A[j];
            ret = max(sum, ret);
        }
    }
    return ret;
}

int fastMaxSum(const vector<int> &A, int lo, int hi) // O(nlogn)
{
    if (lo == hi)
        return A[lo];
    int mid = (lo + hi) / 2;
    // 중간에 걸침
    int left = MIN, right = MIN, sum = 0;
    for (int i = mid; i >= lo; --i)
    {
        sum += A[i];
        left = max(left, sum);
    }
    sum = 0;
    for (int i = mid + 1; i <= hi; ++i)
    {
        sum += A[i];
        right = max(right, sum);
    }
    // 한쪽에만 있음
    int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid + 1, hi));

    return max(left + right, single);
}

int fastestMaxSum(const vector<int> &A) // O(n)
{
    int N = A.size(), ret = MIN, psum = 0;
    for (int i = 0; i < N; ++i)
    {
        psum = max(psum, 0) + A[i];
        ret = max(psum, ret);
    }
    return ret;
}

int main(void)
{
    cout << inefficientMaxSum(v) << endl;
    cout << betterMaxSum(v) << endl;
    cout << fastMaxSum(v, 0, v.size() - 1) << endl;
    cout << fastestMaxSum(v) << endl;
}