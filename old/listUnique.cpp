#include <list>
#include <iostream>
using namespace std;

void printList(list<int> &li, string label = "list")
{
    cout << label << ": ";
    for (list<int>::iterator it = li.begin(); it != li.end(); it++)
        cout << *it << ' ';
    cout << endl;
}

bool Predicate(int first, int second)
{
    return first >= second;
}

int main()
{
    list<int> lt1;

    lt1.push_back(10);
    lt1.push_back(20);
    lt1.push_back(30);
    lt1.push_back(30);
    lt1.push_back(20);
    lt1.push_back(40);
    lt1.push_back(30);
    lt1.push_back(50);

    printList(lt1, "lt1");

    lt1.unique(Predicate); //같거나 낮은 항목은 지우면서 순회
    cout << "==lt1.unique(Predicate)==" << endl;
    printList(lt1, "lt1");
}