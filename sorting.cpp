#include <iostream>
#include <vector>
#include <list>
#include <random>
#define INF 999999
using namespace std;
void swap(int &, int &);
void generate(vector<int> &, int);
template <typename Iterator>
void printContainer(Iterator, Iterator);
void insertionSort(list<int> &);
void quickSort(vector<int> &, int = 0, int = INF);
void merge(vector<int> &, int, int, int);
void mergeSort(vector<int> &, int = 0, int = INF);
void heapify(vector<int> &, int);
void heapSort(vector<int> &);
int selection(const vector<int> &, int);
template <typename Iterator>
void check(Iterator, Iterator);

int main()
{
    vector<int> v, vQuick, vMerge, vHeap;
    clock_t start;
    generate(v, 100000);
    vQuick = vMerge = vHeap = v;
    list<int> lInsertion(v.begin(), v.end()); // v와 원소가 같은 연결 리스트 생성

    cout << "Insertion Sort:" << endl;
    start = clock(); // 실행시간 측정용 클락
    insertionSort(lInsertion);
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms, ";
    check<list<int>::const_iterator>(lInsertion.begin(), lInsertion.end());
    // printContainer<vector<int>::const_iterator>(lInsertion.begin(), lInsertion.end());

    cout << "Quick Sort:" << endl;
    start = clock(); // 실행시간 측정용 클락
    quickSort(vQuick);
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms, ";
    check<vector<int>::const_iterator>(vQuick.begin(), vQuick.end());
    // printContainer<vector<int>::const_iterator>(vQuick.begin(), vQuick.end());

    cout << "Merge Sort:" << endl;
    start = clock(); // 실행시간 측정용 클락
    mergeSort(vMerge);
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms, ";
    check<vector<int>::const_iterator>(vMerge.begin(), vMerge.end());
    // printContainer<vector<int>::const_iterator>(vMerge.begin(), vMerge.end());

    cout << "Heap Sort:" << endl;
    start = clock(); // 실행시간 측정용 클락
    heapSort(vHeap);
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms, ";
    check<vector<int>::const_iterator>(vHeap.begin(), vHeap.end());
    // printContainer<vector<int>::const_iterator>(vHeap.begin(), vHeap.end());

    cout << "Selection:" << endl;
    cout << "49999번째 원소는... ";
    start = clock(); // 실행시간 측정용 클락
    cout << selection(v, 49999) << endl;
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms";
}

// Simple int swap
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
// Generate [1,2,...,count] and shuffle
void generate(vector<int> &v, int count)
{
    for (int i = count; i != 0; i--)
    {
        v.push_back(i);
    }
    std::random_device rd;
    std::default_random_engine re(rd());
    shuffle(v.begin(), v.end(), re);
}
// Print
template <typename Iterator>
void printContainer(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        cout << *begin++ << ' ';
    }
    cout << endl;
}
// Insertion Sort
void insertionSort(list<int> &l)
{
    list<int>::iterator it1, it2;
    const list<int>::iterator end = l.end();
    int tmp;
    it1 = ++l.begin();
    while (it1 != end)
    {
        tmp = *it1;
        it1 = l.erase(it1);
        it2 = it1;
        it2--;
        while (*it2 > tmp && it2 != l.begin())
            it2--;
        if (*it2 > tmp)
            l.insert(it2, tmp);
        else
            l.insert(++it2, tmp);
    }
}
// Quick Sort
void quickSort(vector<int> &v, int first, int last)
{
    if (last == INF)
        last = v.size() - 1;
    if (first >= last)
        return;
    int front, back, pivot;
    pivot = v[first];
    front = first;
    back = last;
    while (front < back)
    {
        while (pivot < v[back])
            back--;
        while (front < back && pivot >= v[front])
            front++;
        swap(v[front], v[back]);
    }
    swap(v[first], v[front]);
    quickSort(v, first, front - 1);
    quickSort(v, front + 1, last);
}
// vector Merge
void merge(vector<int> &v, int left, int mid, int right)
{
    vector<int> tmpv;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (v[i] <= v[j])
        {
            tmpv.push_back(v[i]);
            i++;
        }
        else
        {
            tmpv.push_back(v[j]);
            j++;
        }
    }
    if (i > mid)
    {
        while (j <= right)
            tmpv.push_back(v[j++]);
    }
    else
    {
        while (i <= mid)
            tmpv.push_back(v[i++]);
    }
    for (int k = 0; k < tmpv.size(); k++)
        v[k + left] = tmpv[k];
}
// Merge Sort
void mergeSort(vector<int> &v, int first, int last)
{
    if (first >= last)
        return;
    if (last == INF)
        last = v.size() - 1;
    int mid = (first + last) / 2;
    mergeSort(v, first, mid);
    mergeSort(v, mid + 1, last);
    merge(v, first, mid, last);
}
// Construct Heap
void heapify(vector<int> &v, int i)
{
    int vac = i * 2;
    if (vac < v.size() - 1 && v[vac] < v[vac + 1])
        vac++;
    if (v[i] < v[vac])
    {
        swap(v[i], v[vac]);
        if (vac <= v.size() / 2)
            heapify(v, vac);
    }
}
// Heap Sort
void heapSort(vector<int> &v)
{
    int heapsize, cur;
    v.insert(v.begin(), 0); // root index를 1로 설정하기 위해 맨 앞에 0 추가
    for (int i = v.size() / 2; i > 0; i--)
        heapify(v, i);
    heapsize = v.size() - 1;
    while (heapsize > 0)
    {
        swap(v[1], v[heapsize]);
        cur = 1;
        while (cur * 2 < heapsize)
        {
            cur *= 2;
            if (cur < heapsize - 1 && v[cur] < v[cur + 1])
                cur++;
            if (v[cur / 2] < v[cur])
                swap(v[cur / 2], v[cur]);
        }
        heapsize--;
    }
    v.erase(v.begin());
}
// Select [target]th Element
int selection(const vector<int> &v, int target)
{
    vector<vector<int> > fives; // 다섯개씩 넣은 배열을 담은 2차원 벡터
    vector<int> medians, lesses, greaters;
    int i = 0, vSize = v.size(), MoM;
    if (target > vSize)
        return 0;
    if (vSize <= 10) // 원소가 10개 이하라면 그냥 정렬
    {
        vector<int> vc(v);
        sort<vector<int>::iterator>(vc.begin(), vc.end());
        return vc[target];
    }
    while (i < vSize)
    {
        vector<int> minivec;
        for (int j = 0; j < 5; j++) // 5개씩 뽑아서 미니벡터 만들기
        {
            minivec.push_back(v[i++]);
            if (i == vSize)
                break;
        }
        if (minivec.size() == 5) // 5개가 들어갔으면 중간값 찾기, 그 이하인 배열은 맨 마지막 하나(없을수도)
        {
            if (minivec[0] > minivec[1])
                swap(minivec[0], minivec[1]); //[0]<[1]
            if (minivec[2] > minivec[3])
                swap(minivec[2], minivec[3]); //[0]<[1], [2]<[3]
            if (minivec[1] > minivec[3])
            {
                swap(minivec[0], minivec[2]);
                swap(minivec[1], minivec[3]); //[0]<[1], [2]<[3], [1]<[3]
            }
            swap(minivec[3], minivec[4]); // [3],[4] 바꾸고 [4] 제외 (1~2번째로 큰  수)
            if (minivec[2] > minivec[3])
                swap(minivec[2], minivec[3]); //[0]<[1], [2]<[3]< ( [4] )
            if (minivec[1] > minivec[3])
            {
                swap(minivec[0], minivec[2]);
                swap(minivec[1], minivec[3]); //[0]<[1], [2]< ( [3],[4] )
            }
            if (minivec[1] > minivec[2])
                swap(minivec[1], minivec[2]); // ( [0],[1] )<[2]<( [3],[4] )
        }
        fives.push_back(minivec);
    }
    for (int i = 0; i < fives.size(); i++) // 5개짜리 배열의 중간값들만 모아놓기 (medians)
    {
        if (fives[i].size() == 5)
            medians.push_back(fives[i][2]);
    }
    MoM = selection(medians, medians.size() / 2); // median of medians 재귀적으로 구하기
    for (int i = 0; i < fives.size() - 1; i++)
    {
        if (fives[i][2] < MoM) // 중간값이 중간중간값보다 작을 때: 3개가 작은쪽, 2개는 검사
        {
            for (int j = 0; j < 3; j++)
                lesses.push_back(fives[i][j]);
            for (int j = 3; j < 5; j++)
            {
                if (fives[i][j] < MoM)
                    lesses.push_back(fives[i][j]);
                else
                    greaters.push_back(fives[i][j]);
            }
        }
        else if (fives[i][2] > MoM)
        { // 중간값이 중간중간값보다 작을 때: 2개 검사, 3개는 큰쪽
            for (int j = 0; j < 2; j++)
            {
                if (fives[i][j] < MoM)
                    lesses.push_back(fives[i][j]);
                else
                    greaters.push_back(fives[i][j]);
            }
            for (int j = 2; j < 5; j++)
                greaters.push_back(fives[i][j]);
        }
        else
        { // 중간값이 중간중간값이면 2개는 작은쪽, 3개는 큰쪽
            for (int j = 0; j < 2; j++)
                lesses.push_back(fives[i][j]);
            for (int j = 2; j < 5; j++)
                greaters.push_back(fives[i][j]);
        }
    }
    for (int j = 0; j < fives[fives.size() - 1].size(); j++)
    {
        if (fives[fives.size() - 1][j] < MoM)
            lesses.push_back(fives[fives.size() - 1][j]);
        else
            greaters.push_back(fives[fives.size() - 1][j]);
    }

    if (target >= lesses.size())
        return selection(greaters, target - lesses.size());
    else
        return selection(lesses, target);
}
// Check if the container is ordered
template <typename Iterator>
void check(Iterator begin, Iterator end)
{
    Iterator it1 = begin, it2 = begin;
    it1++;
    while (it1 != end)
    {
        if (*(it2++) > *(it1++))
        {
            cout << "not ordered!" << endl;
            return;
        }
    }
    cout << "ordered" << endl;
}
