#include <iostream>
#include <vector>
using namespace std;
int solution(int, int, vector<string>);
bool getFirstBlank();
int dfs(int, int);
void printMap();
vector<string> map;
vector<vector<pair<int, int>>> blocks = {
    {{0, 0}, {0, 1}, {1, 1}},  //ㄱ
    {{0, 0}, {1, 0}, {1, 1}},  //ㄴ
    {{0, 0}, {1, 0}, {0, 1}},  // r
    {{0, 0}, {1, 0}, {1, -1}}, // J
};
int height, width;
int firstBlankX = -1, firstBlankY = -1;

int main(void)
{
    vector<string> question = {"#.....#",
                               "#.....#",
                               "##..###"};
    cout << solution(question.size(), question[0].size(), question) << endl;
}

int solution(int _height, int _width, vector<string> _map)
{
    height = _height;
    width = _width;
    map = _map;
    getFirstBlank();
    return dfs(firstBlankY, firstBlankX);
}

bool getFirstBlank()
{
    while (firstBlankY < height)
    {
        while (firstBlankX < height)
        {
            if (map[firstBlankY][firstBlankX] == '.')
                return true;
            firstBlankX++;
        }
        firstBlankX = 0;
        firstBlankY++;
    }
    return false;
}

int dfs(int y, int x)
{
    if (y == height)
    {
        cout << "found one!" << endl;
        return 1;
    }
    if (x == width)
        return dfs(y + 1, 0);
    if (map[y][x] == '#')
        return dfs(y, x + 1);
    printMap();
    int ret[4];
    for (int i = 0; i < 4; i++)
    {
        if (y + blocks[i][0].first < height && x + blocks[i][0].second < width &&
            y + blocks[i][1].first < height && x + blocks[i][1].second < width &&
            y + blocks[i][2].first < height && x + blocks[i][2].second < width &&
            x + blocks[i][0].second >= 0 &&
            map[y + blocks[i][0].first][x + blocks[i][0].second] == '.' &&
            map[y + blocks[i][1].first][x + blocks[i][1].second] == '.' &&
            map[y + blocks[i][2].first][x + blocks[i][2].second] == '.')
        {
            map[y + blocks[i][0].first][x + blocks[i][0].second] = '#';
            map[y + blocks[i][1].first][x + blocks[i][1].second] = '#';
            map[y + blocks[i][2].first][x + blocks[i][2].second] = '#';
            ret[i] = dfs(y, x + 1);
            map[y + blocks[i][0].first][x + blocks[i][0].second] = '.';
            map[y + blocks[i][1].first][x + blocks[i][1].second] = '.';
            map[y + blocks[i][2].first][x + blocks[i][2].second] = '.';
        }
        else
            ret[i] = 0;
    }
    return ret[0] + ret[1] + ret[2] + ret[3];
}

void printMap()
{
    for (auto it = map.begin(); it != map.end(); it++)
    {
        for (auto jt = (*it).begin(); jt != (*it).end(); jt++)
        {
            cout << *jt;
        }
        cout << endl;
    }
    cout << endl;
}