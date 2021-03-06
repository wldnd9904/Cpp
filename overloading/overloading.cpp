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
	const Point operator+(const Point& arg)	// + 연산자
	{
		Point pt;
		pt.x = this->x + arg.x;
		pt.y = this->y + arg.y;

		return pt;
	}
	int GetX() const { return x; }
	int GetY() const { return y; }
	//----------------------------------------------------------------//
	const Point& operator++ () {	// 전위 ++ 연산자
		++x;
		++y;
		return *this;
	}
	const Point operator++ (int) {	// 후위 ++ 연산자, int값은 더미값
		Point tmp = *this;
		++*this;
		return tmp;
	}
	const Point& operator-- () {	// 전위 -- 연산자
		--x;
		--y;
		return *this;
	}
	const Point operator-- (int) {	// 후위 -- 연산자, int값은 더미값
		Point tmp = *this;
		--*this;
		return tmp;
	}
	bool operator==(const Point& arg) {	// == 연산자
		return x == arg.x && y == arg.y;
	}
	bool operator!=(const Point& arg) {	// == 연산자
		return !(*this == arg);
	}
	//----------------------------------------------------------------//

};
//전역 함수를 통한 오버로딩
const Point operator-(const Point& argL, const Point& argR) {
	return Point(argL.GetX() - argR.GetX(), argL.GetY() - argR.GetY());
}
int main()
{
	Point p1(2, 3), p2(5, 5);

	Point p3 = p1 + p2; //=> p1.operator+(p2);와 같습니다.
	p3.Print();
	(++p1).Print(); // p1.operator++ (); 와 같습니다.
	(p2++).Print(); // p2.operator++ (0); 와 같습니다.
	(--p1).Print(); // p1.operator-- (); 와 같습니다.
	(p2--).Print(); // p2.operator-- (0); 와 같습니다.

	Point p4(5, 5);
	if (p1 != p2) cout << "p1 != p2" << endl;
	if (p2 == p4) cout << "p2 == p4" << endl;

	(p4 - p3).Print();
	return 0;
}