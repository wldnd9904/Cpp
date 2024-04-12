#include <iostream>
using namespace std;

long long onesFrom0(long long n) {
    if (n <= 1) return n;
    long long base, sum, cnt = 0;
    // 2^n-1까지는 모든 비트가 절반씩 나옴
    long long tmp = n;
    while (tmp) {
        tmp >>= 1;
        cnt++;
    }
    cnt--;
    base = ((long long)1 << (cnt));
    sum = cnt * (base / 2);

    // 2^n-1 까지 처리했음
    // 나머지는 MSB가 1인것만 빼곤 위 문제와 같음
    sum += (n - base + 1) + onesFrom0(n - base);
    return sum;
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    long long A, B;
    cin >> A >> B;
    cout << onesFrom0(B) - onesFrom0(A - 1) << '\n';

    return 0;
}
