#include <iostream>
#include <vector>
#define BITSIZE 8
using namespace std;
//-----------------------------//
// RC4 알고리즘
// 바이트단위로 암호화, 가변 키 사이즈
//-----------------------------//
vector<int> S, T, Z, C;
vector<int> K = {1, 2, 3, 6};
vector<int> P = {1, 2, 2, 2};

void printVec(const vector<int> v)
{
    for (vector<const int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << ' ';
    }
}
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int i, j = 0;
    // init setting
    cout << "[Init-Setting]" << endl;
    // init S[]
    for (i = 0; i < BITSIZE; i++)
        S.push_back(i);
    cout << "S[]: ";
    printVec(S);
    cout << endl;

    // init T[]
    const int keylength = K.size();
    for (i = 0; i < BITSIZE; i++)
        T.push_back(K[i % keylength]);
    cout << "T[]: ";
    printVec(T);
    cout << endl;

    // Key-scheduling algorithm
    cout << endl
         << "[Key-Generation]" << endl;
    // permute S[]
    for (i = 0; i < BITSIZE; i++)
    {
        j = (j + S[i] + T[i]) % BITSIZE;
        swap(S[i], S[j]);
    }
    cout << "S[]: ";
    printVec(S);
    cout << endl;

    // Pseudo-random generation algorithm
    const int textlength = P.size();
    int index, z;
    i = j = 0;
    for (int k = 0; k < textlength; k++)
    {
        j = (j + S[++i]) % BITSIZE;
        swap(S[i], S[j]);
        index = (S[i] + S[j]) % BITSIZE;
        z = S[index];
        Z.push_back(z);
        cout << "i: " << i << ", j: " << j << ", S=[";
        printVec(S);
        cout << "], index: " << index << " -> Z[" << i << "]=S[" << index << "]=" << z << endl;
        C.push_back(z ^ P[i - 1]);
    }
    cout << endl
         << "Z[]: ";
    printVec(Z);
    cout << endl
         << "C[]: ";
    printVec(C);
}