#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename RType, typename AType>
class Ptr_fun_class : public unary_function<AType, RType>
{
    RType (*pf)(AType);

public:
    Ptr_fun_class(RType (*_pf)(AType)) : pf(_pf) {}
    RType operator()(AType n) const { return pf(n); }
};

template <typename RType, typename AType>
Ptr_fun_class<RType, AType> Ptr_fun(RType (*pf)(AType))
{
    return Ptr_fun_class<RType, AType>(pf);
}

bool Pred(int n)
{
    return 30 <= n && n <= 40;
}

int main()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    cout << "v: ";
    for (vector<int>::size_type i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "30이상 40이하의 원소 개수: " << count_if(v.begin(), v.end(), Pred) << endl;
    cout << "30이상 40이하가 아닌 원소 개수: " << count_if(v.begin(), v.end(), not1(Ptr_fun(Pred))) << endl;
}