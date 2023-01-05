#include <iostream>
#include <cmath>
using namespace std;

void isPrime(const __int64_t num)
{
    __int64_t root = sqrt(num);
    for (__int64_t i = 2; i < root; i++)
    {
        if (num % i == 0)
        {
            cout << i << " * " << num / i << " = " << num << endl;
            cout << num << " is not a prime number." << endl;
            return;
        }
    }
    cout << num << " is a prime number." << endl;
}

int main()
{
    clock_t start = clock(); // 실행시간 측정용 클락
    const __int64_t bigNum = (__int64_t)pow(2, 61) - 1;
    isPrime(bigNum);
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms" << endl;
}