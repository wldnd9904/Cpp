#include <chrono>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    vector<int> answers;
    std::cin >> T;  // 테스트 수
    for (int i = 0; i < T; i++) {
        int N, M, Q, answer = 0;  // (1 ≤ N, M, Q ≤ 200000, N * M ≤ 200000)
        std::cin >> N >> M >> Q;
        vector<int> max_row(N, 0);
        vector<int> max_col(M, 0);
        vector<bool> radix(10000001, false);
        set<int> maxs;
        vector<vector<int>> matrix(N, vector<int>(M, 0));
        // 입력받기
        for (int j = 0; j < N; j++) {  // (1 ≤ Ai,j ≤ 107)
            for (int k = 0; k < M; k++) {
                int c;
                cin >> c;
                matrix[j][k] = c;
                max_row[j] = max(max_row[j], c);
                max_col[k] = max(max_col[k], c);
            }
        }
        // 기수표 업데이트
        for (int j = 0; j < N; j++) {
            radix[max_row[j]] = true;
        }
        for (int j = 0; j < M; j++) {
            if (radix[max_col[j]] == true) {
                maxs.insert(max_col[j]);
            }
            radix[max_col[j]] = true;
        }
        for (int j = 0; j < Q; j++) {  // (1 ≤ r ≤ N, 1 ≤ c ≤ M, 1 ≤ x ≤ 107)
            int r, c, x;
            std::cin >> r >> c >> x;
            matrix[r - 1][c - 1] = x;
            
            answer += maxs.size();
        }
        answers.push_back(answer);
    }
    for (int i = 0; i < T; i++) {
        cout << "#" << i + 1 << " " << answers[i] << "\n";
    }
    return 0;
}