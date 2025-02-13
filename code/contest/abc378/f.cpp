#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 経路探索問題, 数え上げ, 連結成分問題

// ポイント
// 単純グラフ: 多重辺も自己ループももたないグラフ

struct UnionFind {
    int _n;
    vector<int> parents;
    UnionFind(int n) : _n(n), parents(n, -1) {}

    void init(int n) {
        parents.assign(n, -1);
    }

    int leader(int x) {
        return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) {
        return -parents[leader(x)];
    }

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

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++, deg[v]++;
    }

    UnionFind uf(n);
    vector<int> nodes(n);
    rep(i, n) {
        if (deg[i] != 3) continue;
        for (auto u : g[i]) {
            if (deg[u] == 3) uf.merge(i, u);
            if (deg[u] == 2) nodes[i]++;
        }
    }

    ll ans = 0;
    for (auto gp : uf.groups()) {
        if (deg[gp[0]] != 3) continue;
        ll sum = 0;
        for (auto u : gp) sum += nodes[u];
        ans += sum * (sum - 1) / 2;
    }

    cout << ans << endl;
}
