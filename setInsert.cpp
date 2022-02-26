#include <set>
#include <iostream>
using namespace std;

void myInsert(set<int> &s, int data)
{
    pair<set<int>::iterator, bool> pr;
    pr = s.insert(data);
    if (pr.second == true)
        cout << *pr.first << " 삽입 성공" << endl;
    else
        cout << *pr.first << " 삽입 실패, 이미 있습니다." << endl;
}

void printSet(set<int> &s)
{
    set<int>::iterator it;
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

int main()
{
    set<int> s;

    myInsert(s, 50);
    myInsert(s, 40);
    myInsert(s, 60);

    printSet(s);

    myInsert(s, 50);
}