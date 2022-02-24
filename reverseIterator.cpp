#include <iostream>
#include <vector>
using namespace std;

void PrintVec(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it < v.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}
void PrintVecRev(vector<int> &v)
{
    for (vector<int>::reverse_iterator it = v.rbegin(); it < v.rend(); it++)
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

    PrintVec(v);
    PrintVecRev(v);
}