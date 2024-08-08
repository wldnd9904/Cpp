#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  int menWhoWantsTaller[100000];
  int mwwtCnt = 0;
  int menWhoWantsSmaller[100000];
  int mwwsCnt = 0;
  int womenWhoWantsTaller[100000];
  int wwwtCnt = 0;
  int womenWhoWantsSmaller[100000];
  int wwwsCnt = 0;
  for (int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    if (tmp > 0)
      menWhoWantsTaller[mwwtCnt++] = tmp;
    else
      menWhoWantsSmaller[mwwsCnt++] = -tmp;
  }

  for (int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    if (tmp > 0)
      womenWhoWantsTaller[wwwtCnt++] = tmp;
    else
      womenWhoWantsSmaller[wwwsCnt++] = -tmp;
  }

  int couple = 0;
  int im = 0, iw = 0;
  // 키큰여자 좋아하는사람중에 제일큰사람부터
  // 키작은남자 좋아하는 여자중에서 제일 큰사람부터 체크
  // 제일 작은애보다 작으면 다른 모든애들보다 작을것
  sort(menWhoWantsTaller, menWhoWantsTaller + mwwtCnt, less<int>());
  sort(womenWhoWantsSmaller, womenWhoWantsSmaller + wwwsCnt, less<int>());
  while (im != mwwtCnt && iw != wwwsCnt) {
    while (iw != wwwsCnt && menWhoWantsTaller[im] >= womenWhoWantsSmaller[iw]) {
      iw++;
    }
    if (iw == wwwsCnt) break;
    im++;
    iw++;
    couple++;
  }
  im = 0;
  iw = 0;
  // 키작은여자 좋아하는사람중에 젤큰사람부터
  // 키큰남자 좋아하는 여자중에서 제일큰사람부터 체크
  // 제일 키큰놈보다 크면 다른 모든놈들보다 큰 것
  sort(menWhoWantsSmaller, menWhoWantsSmaller + mwwsCnt, greater<int>());
  sort(womenWhoWantsTaller, womenWhoWantsTaller + wwwtCnt, greater<int>());
  while (im != mwwsCnt && iw != wwwtCnt) {
    while (iw != wwwtCnt && menWhoWantsSmaller[im] <= womenWhoWantsTaller[iw]) {
      iw++;
    }
    if (iw == wwwtCnt) break;
    im++;
    iw++;
    couple++;
  }
  cout << couple;
  return 0;
}