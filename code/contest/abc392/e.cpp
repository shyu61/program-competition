#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// グラフ問題, 連結成分

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}

    void init(int n) {
        par.assign(n, -1);
    }

    int leader(int x) {
        return par[x] < 0 ? x : par[x] = leader(par[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    bool merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[leader(x)];
    }
};

int main() {
    int n, m; cin >> n >> m;

    UnionFind uf(n);    
    vector<tuple<int, int, int>> ex;
    rep(i, m) {
        int a, b; cin >> a >> b; a--, b--;
        if (!uf.same(a, b)) uf.merge(a, b);
        else ex.emplace_back(i, a, b);
    }

    set<int> lds;
    rep(i, n) lds.insert(uf.leader(i));

    cout << lds.size() - 1 << endl;
    while (lds.size() > 1) {
        auto [ei, u, v] = ex.back(); ex.pop_back();
        lds.erase(uf.leader(u));

        int t = *lds.begin();
        lds.erase(t);

        uf.merge(uf.leader(u), t);
        lds.insert(uf.leader(u));

        cout << ei + 1 << ' ' << u + 1 << ' ' << t + 1 << '\n';
    }
}
