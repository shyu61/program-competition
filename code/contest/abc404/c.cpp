#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// グラフの形状は次数が絡むことが多い

struct UnionFind {
    int _n;
    vector<int> parents;
    UnionFind(int n) : _n(n), parents(n, -1) {}

    void init(int n) { parents.assign(n, -1); }
    int leader(int x) { return parents[x] < 0 ? x : parents[x] = leader(parents[x]); }
    bool same(int x, int y) { return leader(x) == leader(y); }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) { return -parents[leader(x)]; }

    vector<vector<int>> groups() {
        vector<int> lds(_n);
        for (int i = 0; i < _n; i++) lds[i] = leader(i);
        vector<vector<int>> res(_n);
        for (int i = 0; i < _n; i++) res[lds[i]].push_back(i);
        res.erase(
            remove_if(
                res.begin(),
                res.end(),
                [&](const vector<int>& vec) { return vec.empty(); }
            ),
            res.end()
        );
        return res;
    }
};

bool solve() {
    int n, m; cin >> n >> m;
    UnionFind uf(n);
    vector<int> deg(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        uf.merge(u, v);
        deg[u]++, deg[v]++;
    }

    rep(i, n) {
        if (deg[i] != 2) return false;
    }
    return uf.size(0) == n;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
