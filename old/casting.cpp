#include <iostream>
using namespace std;

class A
{
};

class B
{
public:
    B() { cout << "B()" << endl; }
    operator A()
    {
        cout << "B(A _a)" << endl;
        return A();
    }
    operator int()
    {
        cout << "B(int n)" << endl;
        return 10;
    }
    operator double()
    {
        cout << "B(double d)" << endl;
        return 5.5;
    }
};

int main()
{
    A a;
    int n;
    double d;
    B b;
    a = b;
    n = b;
    d = b;

    cout << endl;
    a = b.operator A();
    n = b.operator int();
    d = b.operator double();
}
