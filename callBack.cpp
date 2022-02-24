#include <iostream>
using namespace std;

/////서버/////
// 배열의 모든 원소에 반복적인 작업을 수행하게 추상화됨
void For_each(int *begin, int *end, void (*pf)(int))
{
    while (begin != end)
    {
        pf(*begin++); // 클라이언트 함수 호출(콜백)
    }
}
/////클라이언트/////
void Print1(int n)
{ // 공백을 이용해 원소를 출력
    cout << n << ' ';
}
void Print2(int n)
{ // 각 원소를 제곱해 출력
    cout << n * n << ' ';
}
void Print3(int n)
{ // 문자열과 endl을 이용해 원소를 출력
    cout << "정수: " << n << endl;
}

int main()
{
    int arr[5] = {10, 20, 30, 40, 50};

    For_each(arr, arr + 5, Print1);
    cout << endl;
    For_each(arr, arr + 5, Print2);
    cout << endl;
    For_each(arr, arr + 5, Print3);
}