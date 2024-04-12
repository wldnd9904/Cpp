#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        int input;
        cin >> input;
        v[i] = input;
    }
    sort(v.begin(), v.end());

    int result = 0;
    for (int i = 0; i < N; i++) {
        int target = v[i];
        int left = 0, right = N - 1;
        while (left < right) {
            // 합이랑 같으면 종료
            int tmpSum = v[left] + v[right];
            if (tmpSum == target) {
                if (left != i && right != i) {
                    result++;
                    break;
                } else {
                    if (left == i) left++;
                    if (right == i) right--;
                }
                continue;
            }
            if (tmpSum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    cout << result << '\n';
}