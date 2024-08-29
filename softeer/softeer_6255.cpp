#include <iostream>
using namespace std;
char keyMap[26];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  string message;
  string key;
  cin >> message >> key;
  int idx = 0;

  // 1-1: 한글자씩 중복없이 채우기
  bool used[26] = {false};
  used['J' - 'A'] = true;
  for (auto cur : key) {
    if (idx == 26) break;
    if (used[cur - 'A']) continue;
    used[cur - 'A'] = true;
    keyMap[idx++] = cur;
  }
  // 1-2: 안쓰인 글자들로 마저 채우기
  for (int i = 0; i < 26; i++) {
    if (idx == 26) break;
    if (used[i]) continue;
    keyMap[idx++] = 'A' + i;
  }

  // 2: 암호문 두글자 겹치는거 쪼개주기
  string processedMessage;
  for (int i = 0; i < message.size();) {
    if (i == message.size() - 1) {
      processedMessage += message[i];
      break;
    }
    if (message[i] == message[i + 1]) {
      if (message[i] == 'X') {
        processedMessage += "XQ";
        i++;
      } else {
        processedMessage += message[i];
        processedMessage += 'X';
        i++;
      }
    } else {
      processedMessage += message[i];
      processedMessage += message[i + 1];
      i += 2;
    }
  }
  if (processedMessage.size() & 1) processedMessage += 'X';

  // 3-1: 행, 열 정보 저장
  int y[26], x[26];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      char cur = keyMap[i * 5 + j] - 'A';
      y[cur] = i;
      x[cur] = j;
    }
  }
  // 3-2: 두개씩 자르면서 연산
  int cipherLength = processedMessage.size();
  string cipher;
  cipher.reserve(cipherLength);
  for (int i = 0; i < cipherLength; i += 2) {
    int A = processedMessage[i] - 'A';
    int B = processedMessage[i + 1] - 'A';
    char cA, cB;
    // 3-2-1: 같은 행에 존재하면 오른쪽 한칸 이동한 글자로 암호화
    if (y[A] == y[B]) {
      cA = keyMap[y[A] * 5 + (x[A] + 1) % 5];
      cB = keyMap[y[B] * 5 + (x[B] + 1) % 5];
    }
    // 3-2-2: 같은 열에 존재하면 아래로 한칸
    else if (x[A] == x[B]) {
      cA = keyMap[(y[A] + 1) % 5 * 5 + x[A]];
      cB = keyMap[(y[B] + 1) % 5 * 5 + x[B]];
    }
    // 3-2-3: 열을 서로 교환
    else {
      cA = keyMap[y[A] * 5 + x[B]];
      cB = keyMap[y[B] * 5 + x[A]];
    }
    cipher += cA;
    cipher += cB;
  }
  cout << cipher;
  return 0;
}
