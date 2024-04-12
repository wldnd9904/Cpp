#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int N;
int postmap[100001];  // n이 포스트오더에서 어딘지
int inmap[100001];    // n이 인오더에서 어딘지
int segtree[200002];  // 인오더 기준 [l,r)에서 포스트오더 기준 인덱스 제일 큰 놈
                      // 반환
vector<int> inorder, postorder;

void makeTree() {
    for (int i = 0; i < N; i++) segtree[N + i] = inorder[i];
    for (int i = N - 1; i != 0; --i) {
        if (postmap[segtree[i << 1]] > postmap[segtree[i << 1 | 1]]) {
            segtree[i] = segtree[i << 1];
        } else {
            segtree[i] = segtree[i << 1 | 1];
        }
    }
}
// 인오더 기준 [l,r) -> 포스트오더 기준 제일 뒤에 있는 놈의 번호
// 완전탐섹
int whoIsRoot(int l, int r) {
    int ret = 0;
    int maxIndex = -1;
    for (int i = l; i < r; i++) {
        if (postmap[inorder[i]] > maxIndex) {
            ret = inorder[i];
            maxIndex = postmap[inorder[i]];
        }  // 포스트오더 기준 제일 뒤에있는애
    }
    return ret;  // 그놈의 번호
}
// 세그먼트트리
int whoIsRoot2(int l, int r) {
    int ret = 0;
    for (l += N, r += N; l != r; l >>= 1, r >>= 1) {
        if (l & 1) {
            ret = postmap[ret] > postmap[segtree[l]] ? ret : segtree[l];
            l++;
        }
        if (r & 1) {
            r--;
            ret = postmap[ret] > postmap[segtree[r]] ? ret : segtree[r];
        }
    }
    return ret;
}

void solve(int l, int r) {  // 인오더 기준 [l,r)
    // 길이 0이면 종료
    if (l == r) return;
    int root = whoIsRoot2(l, r);
    // 포스트오더의 맨끝에 있는애가 루트 -> 출력
    cout << root << " ";
    solve(l, inmap[root]);
    solve(inmap[root] + 1, r);
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    inorder = vector<int>(N);
    postorder = vector<int>(N);
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        inorder[i] = tmp;
        inmap[tmp] = i;
    }
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        postorder[i] = tmp;
        postmap[tmp] = i;
    }
    makeTree();
    solve(0, N);
    return 0;
}