#include <iostream>
#include <vector>
#include <list>
#include <random>
#define INF 999999
using namespace std;
// Simple int swap
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
// Generate random [count] integers and shuffle
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
void quickSort(vector<int> &v, int first = 0, int last = INF)
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
void mergeSort(vector<int> &v, int first = 0, int last = INF)
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
// Selection
int selection(const vector<int> &v, int target)
{
    vector<vector<int> > fives; // 다섯개씩 넣은 배열을 담은 2차원 벡터
    int i = 0, vSize = v.size();
    while (i < vSize)
    {
        vector<int> minivec;
        for (int j = 0; j < 5; j++)
        {
            minivec.push_back(v[i++]);
            cout << minivec[j] << ' ';
            if (i == vSize)
                break;
        }
        if (minivec[0] > minivec[1])
            swap(minivec[0], minivec[1]); //[0]<[1]
        if (minivec[2] > minivec[3])
            swap(minivec[2], minivec[3]); //[0]<[1], [2]<[3]
        if (minivec[1] > minvec[3])
        { // [1] 제외
            if (minivec[4] > minivec[0])
            { //[0]<[4], [2]<[3]
                if (minivec[4] > minivec[3])
                { // [4] 제외
                    if (minivec[0] > minivec[3])
                    {
                        //[2]<[3]<[0]<[1],[4]
                    }
                    else
                    {
                        //[0],[2]<[3]<[1],[4]
                    }
                }
                else
                { // [3] 제외
                    if (minivec[4] > minivec[2])
                    {
                        //[0],[2]<[4]<[3],[1]
                    }
                    else
                    {
                        //[0]<[4]<[2]<[3],[1]
                    }
                }
            }
            else
            { // []
            }
        }
    } // 5~6번의 비교로 minivec[2]가 중간값, 그 앞은 작은 값, 그 뒤는 큰 값 만들기.
    fives.push_back(minivec);
    cout << endl;
}
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
int main()
{
    vector<int> v, vQuick, vMerge, vHeap;
    clock_t start;
    generate(v, 23);
    vQuick = vMerge = vHeap = v;
    list<int> lInsertion(v.begin(), v.end()); // v와 원소가 같은 연결 리스트 생성

    /*

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

        */
    selection(v, 49999);
}