#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    vector<int>::iterator it = v.begin();
    cout << *it << endl;
    it = find(v.begin(), v.end(), 20);
    cout << *it << endl;
    it = find(v.begin(), v.end(), 100);
    cout << *it << endl;

    for (vector<int>::iterator i = v.begin(); i < v.end(); i++)
    {
        cout << *i << endl;
    }
}