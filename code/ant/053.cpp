// Union-Find木: p84
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
vector<int> par(MAXN);
vector<int> ranks(MAXN);

void init(int n) {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        ranks[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) return x;
    // 圧縮しつつ探索
    return par[x] = find(par[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    // 深い木に浅い木をつける
    if (ranks[x] < ranks[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (ranks[x] == ranks[y]) ranks[x]++;
    }
}
