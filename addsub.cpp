#include <vector>
#include <string>
#include <iostream>
using namespace std;

int dmax(int, int);
int dmin(int, int);
vector<string> arr;
int solution(vector<string> arr0)
{
    // arr = arr0;
    // int size = arr.size()/2+1;
    // int tmp[size][size];
    // for(int i = 0 ; i < size; i++) tmp[i][i]=arr[i*2][0]-'0';
    return dmax(0, arr.size() / 2 + 1);
}

int dmax(int a, int b)
{
    if (b - a == 1)
        return arr[a * 2][0] - '0';
    int res = -9999999;
    for (int i = a; i < b; i++)
    {
        //[a..i-1] [+/-] [i..b-1]
        int tmp;
        switch (arr[i * 2 + 1][0])
        {
        case '+':
            tmp = dmax(a, i) + dmax(i, b);
            break;
        case '-':
            tmp = dmax(a, i) - dmin(i, b);
            break;
        }
        res = res < tmp ? tmp : res;
    }
    return res;
}
int dmin(int a, int b)
{
    if (b - a == 1)
        return arr[a * 2][0] - '0';
    int res = 9999999;
    for (int i = a; i < b; i++)
    {
        //[a..i-1] [+/-] [i..b-1]
        int tmp;
        switch (arr[i * 2 + 1][0])
        {
        case '+':
            tmp = dmax(a, i) + dmax(i, b);
            break;
        case '-':
            tmp = dmax(a, i) - dmin(i, b);
            break;
        }
        res = res > tmp ? tmp : res;
    }
    return res;
}

int main(void)
{
    arr = {"1", "-", "3", "+", "5", "-", "8"};
    cout << solution(arr) << endl;
}