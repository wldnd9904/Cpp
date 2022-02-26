#include <list>
#include <iostream>
using namespace std;

void printList(list<int> &li)
{
    for (list<int>::iterator it = li.begin(); it != li.end(); it++)
        cout << *it << ' ';
    cout << endl;
}

int main()
{
    list<int> lt1;
    list<int> lt2;

    lt1.push_back(10);
    lt1.push_back(20);
    lt1.push_back(30);
    lt1.push_back(40);
    lt1.push_back(50);

    lt2.push_back(100);
    lt2.push_back(200);
    lt2.push_back(300);
    lt2.push_back(400);
    lt2.push_back(500);

    cout << "lt1: ";
    printList(lt1);
    cout << "lt2: ";
    printList(lt2);
    cout << "============" << endl;

    list<int>::iterator iter;
    iter = lt1.begin();
    ++iter;
    ++iter; // 30
    lt1.splice(iter, lt2);
    cout << "lt1: ";
    printList(lt1);
    cout << "lt2: ";
    printList(lt2);
}