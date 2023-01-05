#include <iostream>
#include <vector>
using namespace std;

// Int to Binary string
string I2B(int i)
{
    string output = "";
    while (i > 0)
    {
        output += i % 2 == 1 ? "1" : "0";
        i /= 2;
    }
    reverse(output.begin(), output.end());
    return output;
}
// Binary string to Int
int B2I(const string &input)
{
    int output = 0, base = 1;
    for (int i = input.length() - 1; i >= 0; i--)
    {
        if (input[i] == '1')
            output += base;
        base *= 2;
    }
    return output;
}

int main()
{
    cout << I2B(204) << endl;
    cout << B2I("11001100") << endl;
}