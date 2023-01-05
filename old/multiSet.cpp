#include <iostream>
#include <set>
using namespace std;

void printMultiset(multiset<int> &ms)
{
    multiset<int>::iterator iter;
    for (iter = ms.begin(); iter != ms.end(); iter++)
    {
        cout << *iter << ' ';
    }
    cout << endl;
}

int main()
{
    multiset<int> ms;

    ms.insert(50);
    ms.insert(30);
    ms.insert(80);
    ms.insert(80);
    ms.insert(30);
    ms.insert(70);
    ms.insert(10);
    ms.insert(30);

    printMultiset(ms);

    cout << "30 원소의 개수: " << ms.count(30) << endl;

    multiset<int>::iterator lower_iter;
    multiset<int>::iterator upper_iter;

    lower_iter = ms.lower_bound(30);
    upper_iter = ms.upper_bound(30);
    cout << "lower_iter: " << *lower_iter << ", "
         << "upper_iter: " << *upper_iter << endl;

    cout << "구간 [lower_iter, upper_iter)의 순차열: ";
    for (multiset<int>::iterator iter = lower_iter; iter != upper_iter; ++iter)
        cout << *iter << " ";
    cout << endl;
}