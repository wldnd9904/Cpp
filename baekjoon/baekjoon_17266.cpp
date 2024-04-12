#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N,M;
vector<int> v;

bool solve(int h){
    if(v[0]-h > 0) return false;
    if(v[v.size()-1]+h < N) return false;
    for(int i=0;i<v.size()-1;i++)
        if(v[i]+h < v[i+1]-h) return false;
    return true;
}

int main(void) {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N>>M;
    v = vector<int>();
    for(int i=0;i<M;i++){
        int x;
        cin>>x;
        v.push_back(x);
    }
    
    int l=0,r=N+1;
    while(l!=r){
        int mid = l+(r-l)/2;
        if(solve(mid))
        r = mid;
        else 
        l = mid+1;
    }

    cout << l << "\n";
    return 0;
}