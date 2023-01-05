#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void PrintVec(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it < v.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

int main()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    sort(v.begin(), v.end(), less<int>());
    PrintVec(v);

    sort(v.begin(), v.end(), greater<int>());
    PrintVec(v);
}