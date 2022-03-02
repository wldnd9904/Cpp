#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printVector(vector<int> &v, vector<int>::iterator end)
{
    for (vector<int>::iterator i = v.begin(); i != end; i++)
    {
        cout << *i << ' ';
    }
    cout << endl;
}

int main()
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(20);
    v2.push_back(30);
    v2.push_back(60);

    vector<int> v3(10);
    vector<int>::iterator iter_end;

    iter_end = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    cout << "교집합: ";
    printVector(v3, iter_end);

    iter_end = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    cout << "차집합: ";
    printVector(v3, iter_end);

    iter_end = set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    cout << "대칭 차집합: ";
    printVector(v3, iter_end);

    
}