#include <iostream>
#include <vector>
using namespace std;
//--------------------------------------//
// DES 알고리즘.
// 64비트의 평문, 56비트의 키로 64비트의 암호문 생성
// 암호문=invIP(fk16(...SW(fk1(IP(평문)))...))
// 복호문=invIP(fk1(...SW(fk16(IP(암호문)))...))
// K1=P48(Shift-1(P56(암호키)))
//--------------------------------------//
vector<int> IP = {58, 50, 42, 34, 26, 18, 10, 2,
                  60, 52, 44, 36, 28, 20, 12, 4,
                  62, 54, 46, 38, 30, 22, 14, 6,
                  64, 56, 48, 40, 32, 24, 16, 8,
                  57, 49, 41, 33, 25, 17, 9, 1,
                  59, 51, 43, 35, 27, 19, 11, 3,
                  61, 53, 45, 37, 29, 21, 13, 5,
                  63, 55, 47, 39, 31, 23, 15, 7};
vector<int> invIP = {40, 8, 48, 16, 56, 24, 64, 32,
                     39, 7, 47, 15, 55, 23, 63, 31,
                     38, 6, 46, 14, 54, 22, 62, 30,
                     37, 5, 45, 13, 53, 21, 61, 29,
                     36, 4, 44, 12, 52, 20, 60, 28,
                     35, 3, 43, 11, 51, 19, 59, 27,
                     34, 2, 42, 10, 50, 18, 58, 26,
                     33, 1, 41, 9, 49, 17, 57, 25};
vector<int> EP = {32, 1, 2, 3, 4, 5,
                  4, 5, 6, 7, 8, 9,
                  8, 9, 10, 11, 12, 13,
                  12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21,
                  20, 21, 22, 23, 24, 25,
                  24, 25, 26, 27, 28, 29,
                  28, 29, 30, 31, 32, 1};
vector<int> P56 = {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                   7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4};
vector<int> SHAMT = {1, 1, 2, 2, 2, 2, 2, 2,
                     1, 2, 2, 2, 2, 2, 2, 1};
vector<int> P48 = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
                   23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                   44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
vector<int> P32 = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
vector<vector<vector<int> > > SB = {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                                     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                                     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                                     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
                                    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                                     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                                     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                                     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
                                    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                                     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                                     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                                     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
                                    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                                     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                                     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                                     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
                                    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                                     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                                     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                                     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
                                    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                                     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                                     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                                     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
                                    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                                     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                                     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                                     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
                                    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                                     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                                     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                                     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
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
// Int to Binary string (4bit)
string I2B(int input)
{
    string output = "";
    for (int i = 0; i < 4; i++)
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
// Binary to Hex
string B2H(const string &binary)
{
    string output = "";
    int tmp = 0;
    const int length = binary.length();
    if (length % 4 != 0)
        return "error";
    for (int i = 0; i < length; i += 4)
    {
        tmp = B2I(binary.substr(i, 4));
        output.push_back(tmp < 10 ? (tmp + '0') : (tmp + 'A' - 10));
    }
    return output;
}
// Hex to Binary
string H2B(const string &hex)
{
    string output = "";
    int tmp = 0;
    const int length = hex.length();
    for (int i = 0; i < length; i++)
    {
        tmp = hex[i];
        tmp = tmp < 'A' ? (tmp - '0') : (tmp - 'A' + 10);
        output += I2B(tmp);
    }
    return output;
}
// S-Box
string SBox(const string &input, const int offset, const vector<vector<int> > box)
{
    const string slice = input.substr(offset * 6, 6);
    return I2B(box[B2I(string(slice).erase(1, 4))][B2I(slice.substr(1, 4))]);
}
// one Round
string Round(const string &plainText, const string &key)
{
    string output = plainText;
    const string Lhalf = L(output); // L(IP(P))
    const string Rhalf = R(output); // R(IP(P))
    output = XOR(P(Rhalf, EP), key);
    string S = "";
    const int SBoxCount = SB.size();
    for (int i = 0; i < SBoxCount; i++)
    {
        S += SBox(output, i, SB[i]);
    }
    output = P(S, P32);
    output = Rhalf + XOR(Lhalf, output);
    return output;
}
// Key Generation
void KeyGen(const string &key, vector<string> &v)
{
    string tempKey = P(key, P56);
    int keyCount = SHAMT.size();
    for (int i = 0; i < keyCount; i++)
    {
        tempKey = HaHShift(tempKey, SHAMT[i]);
        v[i] = P(tempKey, P48);
        // cout << "K" << i + 1 << ": " << v[i] << endl;
    }
}
// DES
string DES(const string &plainText, const string &key)
{
    vector<string> keys = vector<string>(16);
    KeyGen(H2B(key), keys);

    string output = P(H2B(plainText), IP); // Initial Permutation
    for (int i = 0; i < 16; i++)           // 16 Rounds
        output = Round(output, keys[i]);   // LiRi
    output = R(output) + L(output);        // R16L16
    output = P(output, invIP);             // IP-1
    return B2H(output);
}
// unDES
string unDES(const string &cipherText, const string &key)
{
    vector<string> keys = vector<string>(16);
    KeyGen(H2B(key), keys);

    string output = P(H2B(cipherText), IP); // Initial Permutation
    for (int i = 15; i >= 0; i--)           // 16 reverse Rounds
        output = Round(output, keys[i]);    // LiRi
    output = R(output) + L(output);         // R16L16
    output = P(output, invIP);              // IP-1
    return B2H(output);
}
int main()
{
    string plainText = "0123456789ABCDEF"; // 0000000100100011010001010110011110001001101010111100110111101111
    string key = "133457799BBCDFF1";       // 0001001100110100010101110111100110011011101111001101111111110001
    cout << "plainText:\t" << plainText << endl;
    cout << "key:\t\t" << key << endl;
    string cipherText = DES(plainText, key);
    cout << "cipherText:\t" << cipherText << endl;
    string decryptedText = unDES(cipherText, key);
    cout << "decryptedText:\t" << decryptedText << endl;
    return 0;
}