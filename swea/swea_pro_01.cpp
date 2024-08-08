#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#include <iostream>
using namespace std;
#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_ALLY 300
#define CMD_ATTACK 400
#define CMD_RECRUIT 500

/////////////////////////////////////////////////////////////////////////
extern void init(int N, int mSoldier[25][25], char mGeneral[25][25][11]);
extern void destroy();
extern int ally(char mMonarchA[11], char mMonarchB[11]);
extern int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]);
extern int recruit(char mMonarch[11], int mNum, int mOption);
/////////////////////////////////////////////////////////////////////////

#define MAX_N 25
#define MAX_L 10

static int Sol[MAX_N][MAX_N];
static char General[MAX_N][MAX_N][MAX_L + 1];

static int run() {
  int isOK = 0;

  int N;
  int cmd;
  int result;
  int check;

  int mN;
  char mMonarchA[11];
  char mMonarchB[11];
  char mGeneral[11];
  int mOption;
  int num;

  scanf("%d", &N);

  for (int c = 0; c < N; ++c) {
    scanf("%d", &cmd);
    switch (cmd) {
      case CMD_INIT:
        scanf("%d", &mN);
        for (int j = 0; j < mN; j++)
          for (int i = 0; i < mN; i++) scanf("%d", &Sol[j][i]);

        for (int j = 0; j < mN; j++)
          for (int i = 0; i < mN; i++) scanf("%s", General[j][i]);

        init(mN, Sol, General);
        isOK = 1;
        break;

      case CMD_ALLY:
        scanf("%s %s", mMonarchA, mMonarchB);
        result = ally(mMonarchA, mMonarchB);
        scanf("%d", &check);
        if (result != check) isOK = 0;
        break;

      case CMD_ATTACK:
        scanf("%s %s %s", mMonarchA, mMonarchB, mGeneral);
        result = attack(mMonarchA, mMonarchB, mGeneral);
        scanf("%d", &check);
        if (result != check) isOK = 0;
        break;

      case CMD_RECRUIT:
        scanf("%s %d %d", mMonarchA, &num, &mOption);
        result = recruit(mMonarchA, num, mOption);
        scanf("%d", &check);
        if (result != check) isOK = 0;
        break;

      default:
        isOK = 0;
        break;
    }
  }

  destroy();

  return isOK;
}

int main() {
  setbuf(stdout, NULL);
  freopen("input.txt", "r", stdin);

  int T, MARK;
  scanf("%d %d", &T, &MARK);

  for (int tc = 1; tc <= T; tc++) {
    if (run())
      printf("#%d %d\n", tc, MARK);
    else {
      printf("#%d %d\n", tc, 0);
      return 0;
    }
  }
  return 0;
}

#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;
struct Nation {
  int id;  // id가 작은 쪽이 부모가 됨
  int y, x, soldier;
  Nation* boss;
  unordered_set<Nation*> enemies;
};
Nation nation_pool[9000];
Nation* board[27][27];

int boardSize;

int monIdCnt;
unordered_map<string, Nation*> monarchToNation;

Nation* findBoss(Nation* nation) {
  Nation* boss = nation;
  while (boss->boss != boss) boss = boss->boss;
  nation->boss = boss;
  return boss;
}

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11]) {
  boardSize = N;
  monIdCnt = 0;
  monarchToNation.clear();
  // 테두리 초기화
  for (int i = 0; i <= N + 1; i++) {
    board[i][0] = nullptr;
    board[i][N + 1] = nullptr;
    board[0][i] = nullptr;
    board[N + 1][i] = nullptr;
  }
  // 입력받기
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      nation_pool[monIdCnt].y = i + 1;
      nation_pool[monIdCnt].x = j + 1;
      nation_pool[monIdCnt].soldier = mSoldier[i][j];
      nation_pool[monIdCnt].id = monIdCnt;
      nation_pool[monIdCnt].boss = &nation_pool[monIdCnt];
      nation_pool[monIdCnt].enemies.clear();
      monarchToNation[mMonarch[i][j]] = &nation_pool[monIdCnt];
      board[i + 1][j + 1] = &nation_pool[monIdCnt];
      monIdCnt++;
    }
  }
}

void destroy() {}

int ally(char mMonarchA[11], char mMonarchB[11]) {
  Nation* nationA = monarchToNation[mMonarchA];
  Nation* nationB = monarchToNation[mMonarchB];
  Nation* bossA = findBoss(nationA);
  Nation* bossB = findBoss(nationB);
  if (bossA == bossB) return -1;

  // 적대관계 찾기
  for (auto it = bossA->enemies.begin(); it != bossA->enemies.end();) {
    Nation* boss = findBoss(*it);
    if (boss != *it) {
      it = bossA->enemies.erase(it);
      bossA->enemies.insert(boss);
    } else {
      ++it;
    }
    if (boss == bossB) return -2;
  }

  for (auto it = bossB->enemies.begin(); it != bossB->enemies.end();) {
    Nation* boss = findBoss(*it);
    if (boss != *it) {
      it = bossB->enemies.erase(it);
      bossB->enemies.insert(boss);
    } else {
      ++it;
    }
    if (boss == bossA) return -2;
  }

  bossA->enemies.insert(bossB->enemies.begin(), bossB->enemies.end());
  bossB->boss = bossA;
  nationA->boss = bossA;  // 경로간소화
  nationB->boss = bossA;
  return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]) {
  Nation* nationA = monarchToNation[mMonarchA];
  Nation* nationB = monarchToNation[mMonarchB];
  Nation* bossA = findBoss(nationA);
  Nation* bossB = findBoss(nationB);
  if (bossA == bossB) return -1;

  int noHelperCnt = 0;
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      Nation* helper = board[nationB->y + dy][nationB->x + dx];
      if (helper == nullptr || findBoss(helper) != bossA) {
        noHelperCnt++;
      }
    }
  }
  if (noHelperCnt == 9) return -2;
  bossA->enemies.insert(bossB);
  bossB->enemies.insert(bossA);

  int attacker = 0;
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      Nation* helper = board[nationB->y + dy][nationB->x + dx];
      if (helper == nullptr || findBoss(helper) != bossA) {
        continue;
      }
      attacker += helper->soldier / 2;
      helper->soldier = (helper->soldier + 1) / 2;
    }
  }

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      Nation* helper = board[nationB->y + dy][nationB->x + dx];
      if (helper == nullptr || helper == nationB || findBoss(helper) != bossB) {
        continue;
      }
      nationB->soldier += helper->soldier / 2;
      helper->soldier = (helper->soldier + 1) / 2;
    }
  }

  if (attacker > nationB->soldier) {
    board[nationB->y][nationB->x] = &nation_pool[monIdCnt];
    nation_pool[monIdCnt].boss = bossA;
    nation_pool[monIdCnt].y = nationB->y;
    nation_pool[monIdCnt].x = nationB->x;
    nation_pool[monIdCnt].enemies.clear();
    nation_pool[monIdCnt].id = monIdCnt;
    nation_pool[monIdCnt].soldier = attacker - nationB->soldier;
    monarchToNation[mGeneral] = &nation_pool[monIdCnt];
    monIdCnt++;
    return 1;
  } else {
    nationB->soldier -= attacker;
    return 0;
  }
}

int recruit(char mMonarch[11], int mNum, int mOption) {
  if (mOption == 0) return monarchToNation[mMonarch]->soldier += mNum;

  Nation* boss = findBoss(monarchToNation[mMonarch]);
  int ret = 0;
  for (int i = 1; i <= boardSize; i++)
    for (int j = 1; j <= boardSize; j++)
      if (findBoss(board[i][j]) == boss) ret += board[i][j]->soldier += mNum;
  return ret;
}