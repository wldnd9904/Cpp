#include <iostream>
#include <string>
using namespace std;

int main(void)
{
    int N = 0, schedule_s = -1, s = -1, d = 0; //날짜 수, 처음 인식한 날짜, 공차
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        if (s == -1 && tmp != -1)
        {
            s = i;
            schedule_s = tmp;
            continue;
        }
        if (s != -1 && tmp != -1)
        {
            d = (tmp - schedule_s) / (i - s);
        }
    }
    int ret = schedule_s - d * s;
    for (int i = 0; i < N; i++)
    {
        cout << ret << endl;
        ret += d;
    }
    return 0;
}