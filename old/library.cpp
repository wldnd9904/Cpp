#include <iostream>
#include <string>
using namespace std;

int main(void)
{
    int seat[100][100];
    int N, M, ret = 0;
    cin >> N >> M;
    getchar();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            seat[i][j] = getchar();
        }
        getchar(); //줄바꿈 무시
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (seat[i][j] != 'C')
                continue;
            if (i > 0 && seat[i - 1][j] == 'P')
                continue;
            if (i < N - 1 && seat[i + 1][j] == 'P')
                continue;
            if (j > 0 && seat[i][j - 1] == 'P')
                continue;
            if (j < M - 1 && seat[i][j + 1] == 'P')
                continue;
            ret++;
        }
    }
    cout << ret;
    return 0;
}