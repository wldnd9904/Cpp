#include "pch.h"
#include <iostream>

//string 클래스를 사용하기 위한 헤더
#include <string>
using namespace std;

int main()
{
	string strName;
	cout << "이름: ";
	cin >> strName;
	cout << "당신의 이름은 " + strName + "입니다." << endl;

	string str1;
	string str2("Hello!");
	string str3("HelloHello", 5);
	string str4(5, 'c');
	string str5(strName.begin(), strName.end());
	const char* ptr = "Hello";
	string str6(ptr, ptr+3);


	string str("abcdefgabcdefg");
	cout << "str.find('c'): " << str.find('c') << endl; //c탐색
	cout << "str.find('c',5): " << str.find('c', 5) << endl; //index 5 이후의 c 탐색
	cout << "str.find(''asdf''): " << str.find("asdf") << endl; //asdf 검색
	cout << "탐색 실패 시: "<<string::npos << endl;

	str.insert(3, "insert"); //abc<insert>def
	str.erase(3, 6); //abcdefg












	return 0;
}
