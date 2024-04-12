#include <iostream>
#include <algorithm>
using namespace std;
#define N 5  // 사이즈
#define L 20 // 찾으려는 단어의 최대 길이
const char board[N][N] = {
    {'N', 'N', 'N', 'N', 'N'},
    {'N', 'N', 'N', 'N', 'N'},
    {'N', 'N', 'Y', 'N', 'N'},
    {'N', 'N', 'N', 'N', 'N'},
    {'N', 'N', 'N', 'N', 'N'},
};
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dp[N][N][L];
bool inRange(int y, int x)
{
    return (x < N && x >= 0 && y < N && y >= 0) ? true : false;
}
// 완전탐색
bool hasword(int y, int x, const string &word)
{
    if (!inRange(y, x))
        return false;
    if (board[y][x] != word[0])
        return false;
    if (word.size() == 1)
        return true;
    for (int direction = 0; direction < 8; ++direction)
    {
        int nextY = y + dy[direction], nextX = x + dx[direction];
        if (hasword(nextY, nextX, word.substr(1)))
            return true;
    }
    return false;
}
// dp
bool hasword2(int y, int x, int cnt, const string &word)
{
    if (!inRange(y, x))
        return false;
    if (dp[y][x][cnt] != -1)
        return dp[y][x][cnt];
    if (board[y][x] != word[cnt])
    {
        dp[y][x][cnt] = 0;
        return false;
    }
    if (word.size() == cnt + 1)
    {
        dp[y][x][cnt] = 1;
        return true;
    }
    for (int direction = 0; direction < 8; ++direction)
    {
        int nextY = y + dy[direction], nextX = x + dx[direction];
        if (hasword2(nextY, nextX, cnt + 1, word))
            return true;
    }
    return false;
}
bool hasword_dp(int y, int x, const string &word)
{
    fill_n(dp[0][0], N * N * L, -1);
    return hasword2(y, x, 0, word);
}

int main(void)
{
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    cout << (hasword(2, 2, "YNNNNNNNNNNNA") ? "true" : "false") << endl;
    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::milliseconds millisecond =
        std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Time Cost: " << millisecond.count() << " ms\n";
}