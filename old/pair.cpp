#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
    Pair(const T1 &ft, const T2 &sd) : first(ft), second(sd) {}
};

int main()
{
    Pair<int, int> p1(10, 20);
    cout << p1.first << ',' << p1.second << endl;
}