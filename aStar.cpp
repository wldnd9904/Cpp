#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
using is = pair<int, string>;
class my_greater
{
public:
    bool operator()(is a, is b)
    {
        return a.first > b.first;
    }
};
priority_queue<is, vector<is>, my_greater> pq;
string src = "165738042", dst = "123456780";
string slide(const string &src, const char dir)
{
    int pos = src.find('0') + 1;
    cout << "pos:" << pos << endl;
    string output(src);
    switch (dir)
    {
    case 'L':
        if (pos % 3 != 1)
        {
            output[pos - 2] = '0';
            output[pos - 1] = src[pos - 2];
            return output;
        }
        break;
    case 'R':
        if (pos % 3 != 0)
        {
            output[pos] = '0';
            output[pos - 1] = src[pos];
            return output;
        }
        break;
    case 'U':
        if (pos > 3)
        {
            output[pos - 4] = '0';
            output[pos - 1] = src[pos - 4];
            return output;
        }
        break;
    case 'D':
        if (pos < 7)
        {
            output[pos + 2] = '0';
            output[pos - 1] = src[pos + 2];
            return output;
        }
        break;
    }
    return output;
}
int minDist(string src, string dst)
{
    pq.push({0, src});
    bool success = false;
    string adj;
    while (!pq.empty())
    {
        is v = pq.top();
        pq.pop();
        if (v == dst)
        {
            success = true;
            break;
        }
        for (char dir : "LRUD")
        {
            adj = slide(v.second, dir);
            if (adj == v.second)
                break;
            pq.push({v.first + 1, adj});
        }
    }
    if (!success)
        return -1;
    else
        return;
}
void print(const string &src)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << src[3 * i + j] << ' ';
        }
        cout << endl;
    }
}

int main(void)
{
    cout << "hi" << endl;
    print(slide("123456078", 'U'));
}