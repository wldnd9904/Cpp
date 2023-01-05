#include <iostream>
#include <vector>
using namespace std;

int Answer;

int main(int argc, char **argv)
{
    int T, test_case;

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        int N, M, K; // nodes, edges, undirected edges
        cin >> N;
        cin >> M;
        cin >> K;
        vector<vector<int>> Graph = vector<vector<int>>(N + 1, vector<int>());
        for (int i = 0; i < M; i++)
        {
            int v, w; // v->w
            cin >> v;
            cin >> w;
            Graph[v].push_back(w);
        }
        for (int i = 0; i < K; i++)
        {
            int v, w; // v->w
            cin >> v;
            cin >> w;
            Graph[v].push_back(w);
            Graph[w].push_back(v);
        }
        
        
        Answer = 0;

        cout << "Case #" << test_case + 1 << endl;
        cout << Answer << endl;
    }

    return 0; // Your program should return 0 on normal termination.
}

int solution()