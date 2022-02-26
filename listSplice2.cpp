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

    printList(lt1, "lt1");
    printList(lt2, "lt2");
    cout << "============" << endl;

    list<int>::iterator iter1;
    list<int>::iterator iter2;
    iter1 = lt1.begin();
    iter1++;
    iter1++; // 30
    iter2 = lt2.begin();
    iter2++; // 200

    // lt1의 iter1 위치에 lt2의 iter2위치를 갖다붙임
    lt1.splice(iter1, lt2, iter2);

    printList(lt1, "lt1");
    printList(lt2, "lt2");
    cout << "============" << endl;

    // lt1의 end위치에 lt2의 begin부터 end를 붙임
    lt1.splice(lt1.end(), lt2, lt2.begin(), lt2.end());

    printList(lt1, "lt1");
    printList(lt2, "lt2");
    cout << "======reverse======" << endl;

    lt1.reverse();

    printList(lt1, "lt1");
    printList(lt2, "lt2");
    cout << "============" << endl;
}