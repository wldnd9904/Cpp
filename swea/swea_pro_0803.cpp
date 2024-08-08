// 2024. 08. 03 삼성 SW 역량테스트 B형(Pro)
// 1245062 최지웅

// 최대 5개의 해시태그를 가진 포스팅을 업로드할 수 있는
// SNS 서비스를 구현하고자 한다. 요구사항은 다음과 같다:
// * 포스팅 등록
// * 포스팅 삭제
// * 해시태그로 포스팅 검색(최대 2개)
// 제한시간: 50개 테스트 케이스 기준 3.0초

#include <list>
#include <unordered_map>
using namespace std;

#define BUCKET_SIZE 80  // 버킷 사이즈, 실제 성능에 영향

struct Bucket;

struct Posting {
  int id;  // 실제 ID
  list<list<Posting*>::iterator>
      bucketList;  // 이 포스팅을 가지고 있는 버킷들을 역참조
};

struct Bucket {
  list<Posting*> postingList;  // 포스팅 리스트 (최대 BUCKET_SIZE개)
  int cnt;                     // 포스팅 수
  Bucket *next, *prev;         // 다음 버킷(양방향 연결 리스트)
};

unordered_map<int, int> postingIDToID;  // 실제 아이디 -> 노드풀 아이디
unordered_map<string, int> hashTagToBit;  // 해시태그 -> 비트
Bucket* bitToBucket[25];  // 해시태그 조합 별 첫 번째 버킷 (최대값: 11000 = 24)
int bitCnt;

Posting post_pool[110001];  // 최대 초기 10,000 개 + 추가 100,000개
Bucket bucket_pool[25000];  // 포스팅 수 * 가능한 해시태그 조합 수 / 버킷 사이즈
                            // -> 넉넉하게
int postCnt;
int bucketCnt;

Bucket* newBucket() {
  bucket_pool[bucketCnt].cnt = 0;
  bucket_pool[bucketCnt].next = nullptr;
  bucket_pool[bucketCnt].prev = nullptr;
  bucket_pool[bucketCnt].postingList.clear();
  return &bucket_pool[bucketCnt++];
}

Posting* newPost(int mID) {
  post_pool[postCnt].id = mID;
  post_pool[postCnt].bucketList.clear();
  postingIDToID[mID] = postCnt;
  return &post_pool[postCnt++];
}

int tagToBit(const string& tag) {
  const auto it = hashTagToBit.find(tag);
  if (it != hashTagToBit.end()) {
    return it->second;
  }
  hashTagToBit[tag] = bitCnt;
  const int ret = bitCnt;
  bitCnt <<= 1;
  return ret;
}

void appendPosting(int mID, int mHashTagCnt, char mHashTags[][10]) {
  Posting* post = newPost(mID);
  int tagBits[5];
  // 태그를 비트로 변환
  for (int i = 0; i < mHashTagCnt; ++i) {
    tagBits[i] = tagToBit(mHashTags[i]);
  }
  // 모든 태그 조합에 따른 버킷에 넣기 (태그가 5개라면 총 15개의 버킷에 존재)
  for (int i = 0; i < mHashTagCnt; ++i) {
    for (int j = i; j < mHashTagCnt; ++j) {
      const int tagBit = tagBits[i] | tagBits[j];
      Bucket* curBucket = bitToBucket[tagBit];
      // 버킷이 꽉 찼다면 새 버킷을 만들고 연결해주기
      if (curBucket->cnt == BUCKET_SIZE) {
        Bucket* tmp = newBucket();
        tmp->next = curBucket;
        curBucket->prev = tmp;
        bitToBucket[tagBit] = tmp;
        curBucket = tmp;
      }
      // 버킷 맨 앞에 포스트 추가 및 포스트에 역참조 추가
      curBucket->postingList.push_front(post);
      curBucket->cnt += 1;
      post->bucketList.push_back(curBucket->postingList.begin());
    }
  }
}

// init: N개의 포스팅이 해시태그와 함께 주어진다. (최신 포스팅부터)
//
// N: 기존 포스팅 수
// mIDs: 포스팅 아이디 목록
// mHashTagCnts: 포스팅별 해시태그 수 목록 (포스팅당 최대 5개)
// mHashTags: 포스팅별 해시태그 목록
void init(int N, int mIDs[], int mHashTagCnts[], char mHashTags[][5][10]) {
  // 맵 및 카운팅용 전역변수 초기화
  postingIDToID.clear();
  hashTagToBit.clear();
  bitCnt = 1;
  postCnt = 0;
  bucketCnt = 0;
  for (int i = 0; i <= 24; ++i) bitToBucket[i] = newBucket();
  // 초기 포스팅들 추가(오래된 것부터)
  for (int i = N - 1; i >= 0; --i)
    appendPosting(mIDs[i], mHashTagCnts[i], mHashTags[i]);
}

// newPosting: 최신 포스팅을 하나 추가한다.
//
// mID: 포스팅 아이디
// mHashTagCnt: 해시태그 수
// mHashTags: 해시태그 목록
//
// 테스트 케이스 당 100,000번 이하
//
// O( 태그 경우의 수 )
void newPosting(int mID, int mHashTagCnt, char mHashTags[][10]) {
  appendPosting(mID, mHashTagCnt, mHashTags);
}

// deletePosting: 특정 포스팅을 삭제한다.
//
// mID: 포스팅 아이디
//
// 테스트 케이스 당 10,000번 이하
//
// O( 태그 경우의 수 * 버킷 수 * 버킷 사이즈 )
void deletePosting(int mID) {
  int id = postingIDToID[mID];
  Posting* post = &post_pool[id];
  // 포스팅이 속한 모든 버킷에서
  for (Bucket* bucket : post->bucketList) {
    // 포스팅을 찾아서 삭제
    auto postingList = bucket->postingList;
    for (auto it = postingList.begin(); it != postingList.end(); ++it) {
      if (*it == post) {
        postingList.erase(it);  // it는 항상 존재
        break;
      }
    }
    bucket->cnt -= 1;
    // 버킷이 비었다면 버킷 삭제 (양옆에 다른 버킷이 있는 경우에만)
    if (bucket->cnt == 0) {
      if (bucket->next != nullptr && bucket->prev != nullptr) {
        bucket->next->prev = bucket->prev;
        bucket->prev->next = bucket->next;
      }
    }
  }
}

// findPosting: 포스팅을 최신 순으로 검색한다.
// 주어진 1~2개의 해시태그를 동시에 가지는 포스팅만을 검색한다.
// 1페이지가 최신이며, 페이지당 최대 10개의 포스팅을 가진다.
//
// mPage: 페이지 번호
// mHashTagCnt: 해시태그 수
// mHashTags: 해시태그 목록
// mPostingIDs: 포스팅 아이디를 채울 배열
// 반환값: mPage페이지의 포스팅 수
//
// 테스트 케이스 당 100,000번 이하
//
// O( 버킷 수 + 버킷 사이즈 )
int findPosting(int mPage, int mHashTagCnt, char mHashTags[][10],
                int mPostingIDs[10]) {
  // 태그를 비트로 변환
  int tagBit = tagToBit(mHashTags[0]);
  if (mHashTagCnt == 2) tagBit |= tagToBit(mHashTags[1]);
  int skipCnt = (mPage - 1) * 10;  // 지나칠 포스팅 수
  int retCnt = 0;                  // 출력/채우기용 카운트

  // 버킷을 순회하며 페이지에 맞게 출력
  Bucket* curBucket = bitToBucket[tagBit];
  while (skipCnt > curBucket->cnt) {
    skipCnt -= curBucket->cnt;
    if (curBucket->next == nullptr) return 0;
    curBucket = curBucket->next;
  }
  while (curBucket != nullptr) {
    for (Posting* curPosting : curBucket->postingList) {
      if (skipCnt) {
        skipCnt -= 1;
        continue;
      }
      mPostingIDs[retCnt++] = curPosting->id;
      if (retCnt == 10) return 10;
    }
    curBucket = curBucket->next;
  }

  return retCnt;
}

//-------------------------------테스트용 코드-------------------------------//

#include <bitset>
#include <iostream>
void printBucket() {
  for (int i = 0; i < 25; i++) {
    bitset<5> bit(i);
    Bucket* cur = bitToBucket[i];
    if (cur->cnt == 0) continue;

    cout << bit << ":";
    while (cur != nullptr) {
      cout << "[ ";
      for (auto post : cur->postingList) {
        cout << post->id << " ";
      }
      cout << "] ";
      cur = cur->next;
    }
    cout << endl << endl;
  }
}

int main() {
  int mIDs[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  int mHashTagCnts[10] = {1, 1, 1, 2, 2, 2, 3, 4, 5, 5};
  char mHashTags[10][5][10] = {
      {"A"},
      {"B"},
      {"C"},
      {"A", "C"},
      {"D", "C"},
      {"B", "E"},
      {"A", "B", "C"},
      {"B", "C", "D", "E"},
      {"A", "B", "C", "D", "E"},
      {"A", "B", "C", "D", "E"},
  };
  init(10, mIDs, mHashTagCnts, mHashTags);

  char newPostsHashTags[3][10] = {"C", "D", "E"};
  for (int i = 1000; i <= 2000; ++i) newPosting(i, 3, newPostsHashTags);
  for (int i = 1025; i <= 1400; ++i) deletePosting(i);

  // printBucket(); // 엄청많이나옴

  for (int page = 60; page < 65; ++page) {
    int arr[10];
    char findPostsHashTags[2][10] = {"C", "E"};
    int arrCnt = findPosting(page, 2, findPostsHashTags, arr);
    cout << "#C, #E - " << page << " 페이지: " << arrCnt << "개" << endl;
    for (int i = 0; i < arrCnt; i++) cout << arr[i] << ", ";
    cout << endl << endl;
  }
  return 0;
}