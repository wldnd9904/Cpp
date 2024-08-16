#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct node {
  list<string> colors;
  node* parent;
};

map<string, node*> m;

node* getNode(string color) {
  if (m.count(color)) return m[color];
  node* ret = new node;
  ret->colors.push_back(color);
  ret->parent = ret;
  m[color] = ret;
  return ret;
}

node* findAncestor(string color) {
  node* start = m[color];
  node* cur = m[color];
  while (cur->parent != cur) {
    cur = cur->parent;
  }
  start->parent = cur;
  return cur;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    string a, b;
    cin >> a >> b;
    node* nodeA = getNode(a);
    node* nodeB = getNode(b);
    node* ancestorA = findAncestor(a);
    node* ancestorB = findAncestor(b);
    if (ancestorA == ancestorB) continue;
    ancestorA->parent = ancestorB;
    ancestorB->colors.insert(ancestorB->colors.end(), ancestorA->colors.begin(),
                             ancestorA->colors.end());
  }
  string s;
  cin >> s;
  node* ancestor = findAncestor(s);
  priority_queue<string, vector<string>, greater<string>> pq;
  for (string color : ancestor->colors) pq.push(color);
  while (!pq.empty()) {
    cout << pq.top() << "\n";
    pq.pop();
  }
  return 0;
}
