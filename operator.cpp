#include <iostream>
using namespace std;

struct Struct
{
    int a = 3; // public?
};
class Class
{
    int a = 3; // private?
public:
    int b = 3; // public
};

class Point
{
    int x;
    int y;

public:
    explicit Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    void Print() const { cout << x << ',' << y << endl; }
    int GetX() const { return x; }
    int GetY() const { return y; }
};

const Point operator-(const Point &a, const Point &b)
{
    return Point(a.GetX() - b.GetX(), a.GetY() - b.GetY());
}
int main()
{
    Point a(5, 2);
    Point b(3, 0);
    (a - b).Print();

    Struct st;
    Class cl;
    cout << Struct().a << cl.b << endl;

    Point c;
    // c = 10; 암시적 형변환 Point(10,0) 호출됨, explicit 키워드로 막음
    c.Print();
}