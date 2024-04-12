#include <iostream>
#include <map>
using namespace std;
int N;

int main(void) {
    ios_base ::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i <= 4000000; i++) {
        bool isP = true;
        for (int j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                isP = false;
                break;
            }
        }
        if (isP) cout << i << " ";
    }
    return 0;
}