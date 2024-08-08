#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  for (int test_case = 0; test_case < T; test_case++) {
    int SM, SC, SI;
    cin >> SM >> SC >> SI;
    vector<unsigned char> memory(SM, 0);
    string code, input;
    cin >> code >> input;
    // 메모리 포인터, 프로그램 카운터, 버퍼카운터, 실행수
    int MP = 0, PC = 0, BC = 0, cnt = 0;
    int pair = 4096, loopEnd = -1;
    vector<int> stack;
    while (cnt < 100000000) {
      if (PC == SC) break;

      switch (code[PC]) {
        case '+':
          memory[MP]++;
          break;

        case '-':
          memory[MP]--;
          break;

        case '<':
          MP--;
          if (MP == -1) MP = SM - 1;
          break;

        case '>':
          MP++;
          if (MP == SM) MP = 0;
          break;

        case ',':
          if (BC == SI)
            memory[MP] = 255;
          else
            memory[MP] = input[BC++];
          break;

        case '[':
          if (memory[MP] == 0) {
            //]까지 점프
            int innerLoopCnt = 0;
            while (true) {
              PC++;
              if (code[PC] == '[') innerLoopCnt++;
              if (code[PC] == ']') {
                if (innerLoopCnt == 0) break;
                innerLoopCnt--;
              }
            }
          } else {
            stack.push_back(PC);
          }
          break;

        case ']':
          if (memory[MP] != 0) {
            //[까지 점프
            if (cnt > 50000000) {
              if (stack[stack.size() - 1] < pair) {
                loopEnd = PC;
                pair = stack[stack.size() - 1];
              }
            }
            PC = stack[stack.size() - 1];
          } else {
            stack.pop_back();
          }
          break;
        default:
          break;
      }
      cnt++;
      PC++;
    }
    if (cnt == 100000000)
      cout << "Loops " << pair << " " << loopEnd << "\n";
    else
      cout << "Terminates\n";
  }

  return 0;
}