#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Point
{
    int x;
    int y;

public:
    explicit Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    int GetX() const { return x; }
    int GetY() const { return y; }
};

ostream &operator<<(ostream &out, const Point &arg)
{
    out << "(" << arg.GetX() << ", " << arg.GetY() << ")";
    return out;
}

bool Pred(const Point &left, const Point &right)
{
    return left.GetY() < right.GetY();
}

int main()
{
    vector<Point> v;
    v.push_back(Point(5, 1));
    v.push_back(Point(7, 2));
    v.push_back(Point(5, 3));
    v.push_back(Point(1, 4));

    int i = 0;
    do
    {
        cout << "v" << ++i << ": " << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << endl;
    } while (next_permutation(v.begin(), v.end(), Pred) == true);
}