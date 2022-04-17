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
    while (++begin != end)
    {
        cout << *begin << ' ';
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
// Heap Sort
void heapSort(vector<int> &v)
{
    // TODO
}
// Selection
void selection(vector<int> &v, int target)
{
    // TODO
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
    vector<int> v, vQuick, vMerge;
    generate(v, 100000);
    vQuick = v;
    vMerge = v;
    list<int> l(v.begin(), v.end()); // v와 원소가 같은 연결 리스트 생성
    cout << "Insertion Sort:" << endl;
    clock_t start = clock(); // 실행시간 측정용 클락
    insertionSort(l);
    cout << "Time : " << ((int)clock() - start) / (CLOCKS_PER_SEC / 1000) << "ms, ";
    check<list<int>::const_iterator>(l.begin(), l.end());
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
}