#include <iostream>
#include <vector>
using namespace std;
//--------------------------------------//
// Simplified DES 알고리즘.
// 8비트의 평문, 10비트의 키로 8비트의 암호문 생성
//암호문=invIP(fk2(SW(fk1(IP(평문)))))
//복호문=invIP(fk1(SW(fk2(IP(암호문)))))
// K1=P8(Shift-1(P10(암호키)))
// K2=P8(Shift-3(P10(암호키)))
//--------------------------------------//
vector<int> IP = {2, 6, 3, 1, 4, 8, 5, 7};
vector<int> invIP = {4, 1, 3, 5, 7, 2, 8, 6};
vector<int> EP = {4, 1, 2, 3, 2, 3, 4, 1};
vector<int> P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
vector<int> P8 = {6, 3, 7, 4, 8, 5, 10, 9};
vector<int> P4 = {2, 4, 3, 1};
vector<vector<int> > SB0 = {{1, 0, 3, 2},
                            {3, 2, 1, 0},
                            {0, 2, 1, 3},
                            {3, 1, 3, 2}};
vector<vector<int> > SB1 = {{0, 1, 2, 3},
                            {2, 0, 1, 3},
                            {3, 0, 1, 0},
                            {2, 1, 0, 3}};
// general Permutation
string P(const string &input, const vector<int> &vec)
{
    string output = "";
    for (vector<const int>::iterator it = vec.begin(); it != vec.end(); it++)
        output += input[(*it) - 1];
    return output;
}
// Left half
string L(const string &input)
{
    size_t length = input.length();
    return input.substr(0, length / 2);
}
// Right half
string R(const string &input)
{
    size_t length = input.length();
    return input.substr(length / 2, length);
}
// Left Shift
string LShift(const string &input, const int amt)
{
    int shamt = amt % input.length();
    string output = input;
    reverse(output.begin(), output.begin() + shamt);
    reverse(output.begin() + shamt, output.end());
    reverse(output.begin(), output.end());
    return output;
}
// Half and Half Shift
string HaHShift(const string &input, const int shamt)
{
    return LShift(L(input), shamt) + LShift(R(input), shamt);
}
// XOR
string XOR(const string &input1, const string &input2)
{
    size_t length = input1.length();
    if (length != input2.length())
        return "error";
    string output = "";
    for (size_t i = 0; i < length; i++)
    {
        output += input1[i] == input2[i] ? "0" : "1";
    }
    return output;
}
// Int to Binary string (2bit)
string I2B(int input)
{
    string output = "";
    for (int i = 0; i < 2; i++)
    {
        output += (input % 2 == 1) ? "1" : "0";
        input /= 2;
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
// S-Box
string SBox(const string &input, const vector<vector<int> > box)
{
    return I2B(box[B2I(input.substr(0, 1) + input.substr(input.length() - 1, 1))][B2I(input.substr(1, input.length() - 2))]);
}
// one Round
string Round(const string &plainText, const string &key)
{
    cout << "-----Round-----" << endl;
    string output = plainText;
    const string Lhalf = L(output); // L(IP(P))
    const string Rhalf = R(output); // R(IP(P))
    output = XOR(P(Rhalf, EP), key);
    cout << "E/P(R)○+K: " << output << endl;

    const string S0 = SBox(L(output), SB0);
    const string S1 = SBox(R(output), SB1);
    cout << "SB(E/P(R)○+K1): " << S0 << S1 << endl;

    output = P(S0 + S1, P4); // F(R,SK)
    cout << "P4(SB(E/P(R)○+K)): " << output << endl;

    output = XOR(Lhalf, output) + Rhalf;
    cout << "---------------" << endl;
    return output;
}
// simplified DES
string DES(const string &plainText, const string &key)
{
    const string K1 = P(HaHShift(P(key, P10), 1), P8);
    const string K2 = P(HaHShift(P(key, P10), 3), P8);
    cout << "K1: " << K1 << ", K2: " << K2 << endl;

    string output = P(plainText, IP); // IP(P)
    cout << "IP(P): " << output << endl;

    output = Round(output, K1); // Round 1
    cout << "after R1: " << output << endl;

    output = R(output) + L(output); // SW(L,R)
    cout << "SW(L,R): " << output << endl;

    output = Round(output, K2); // Round 2
    cout << "after R2: " << output << endl;

    output = P(output, invIP); // invIP(P)

    return output;
}
int main()
{
    string plainText = "00101000";
    string key = "1100011110";
    cout << DES(plainText, key) << endl;
    return 0;
}