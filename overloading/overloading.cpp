#include "pch.h"
#include <iostream>
using namespace std;

//사용자가 정의한 클래스
class Point
{
	int x;
	int y;
public:
	Point(int _x = 0, int _y = 0) :x(_x), y(_y) { }
	void Print() const { cout << x << ',' << y << endl; }
	const Point operator+(const Point& arg)
	{
		Point pt;
		pt.x = this->x + arg.x;
		pt.y = this->y + arg.y;

		return pt;
	}
};

int main()
{
	Point p1(2, 3), p2(5, 5);

	Point p3 = p1 + p2; //=> p1.operator+(p2);와 같습니다
	p3.Print();

	return 0;
}