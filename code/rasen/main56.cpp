// トロポジカルソート
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int NIL = -1;
vector<vector<int> > A;
vector<pair<int, int> > B;

int solve(int v) {
    if (B[v].second != NIL) return B[v].second;
    if (A[v].size() == 0) return 0;

    int maxv = 0;
    for (int in_node : A[v]) {
        maxv = max(maxv, solve(in_node));
    }
    return B[v].second = maxv + 1;
}

bool secondLess(const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; }

int main() {
    int v, e; cin >> v >> e;
    A = vector<vector<int> >(v, vector<int>());
    B = vector<pair<int, int> >(v);
    for (int i = 0; i < v; i++) B[i] = make_pair(i, NIL);
    for (int i = 0; i < e; i++) {
        int in, out; cin >> in >> out;
        A[out].push_back(in);
    }

    for (int i = 0; i < v; i++) {
        B[i].second = solve(i);
    }
    sort(B.begin(), B.end(), secondLess);

    for (int i = 0; i < v; i++) {
        cout << B[i].first << endl;
    }
}
