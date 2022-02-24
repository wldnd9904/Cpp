#include <iostream>
using namespace std;

template <typename IterT, typename Func>
void For_each(IterT begin, IterT end, Func pf)
{
    while (begin != end)
    {
        pf(*begin++);
    }
}

// void PrintInt(int data)
// {
//     cout << data << " ";
// }

// void PrintString(string data)
// {
//     cout << data << " ";
// }

// template <typename T>
// void Print(T data)
// {
//     cout << data << " ";
// }

template <typename T>
struct PrintFunctor
{
    string sep; // 출력 구분자 정보

    explicit PrintFunctor(const string &s = " ") : sep(s) {}

    void operator()(T data) const
    {
        cout << data << sep;
    }
};

int main()
{
    int arr[5] = {10, 20, 30, 40, 50};
    For_each(arr, arr + 5, PrintFunctor<int>());
    cout << endl;

    string sarr[3] = {"Im", "Fine", "Thankyou"};
    For_each(sarr, sarr + 3, PrintFunctor<string>("*\n"));
    cout << endl;
}