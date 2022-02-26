#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, int> m;

    m.insert(pair<int, int>(5, 100));
    m.insert(pair<int, int>(3, 100));
    m.insert(pair<int, int>(8, 30));
    m.insert(pair<int, int>(4, 40));
    m.insert(pair<int, int>(1, 70));
    m.insert(pair<int, int>(7, 100));

    pair<int, int> pr(9, 50);
    m.insert(pr);

    map<int, int>::iterator iter;
    for (iter = m.begin(); iter != m.end(); iter++)
        cout << "(" << (*iter).first << ", " << (*iter).second << ") ";
    cout << endl;

    for (iter = m.begin(); iter != m.end(); iter++)
        cout << "(" << iter->first << ", " << iter->second << ") ";
    cout << endl;
}