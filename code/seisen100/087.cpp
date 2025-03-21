#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// ポイント
// - 連結を分離させていく操作は、時間を逆に見て連結させていく操作で考える
// - UnionFindに情報を持たせたい場合は、leader番号をindexに持つ配列を用意する

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
    ll n, m; cin >> n >> m;
    vector<P> edges(m);
    rep(i, m) {
        int u, v; cin >> u >> v, u--, v--;
        edges[i] = {u, v};
    }

    UnionFind uf(n);
    vector<ll> ans(m);
    ll x = n * (n - 1) / 2;
    ans[m - 1] = x;
    for (int i = m - 2; i >= 0; i--) {
        auto [u, v] = edges[i + 1];
        ll res = ans[i + 1];
        if (!uf.same(u, v)) {
            res -= ll(uf.size(u)) * uf.size(v);
            uf.merge(u, v);
        }
        ans[i] = res;
    }

    rep(i, m) cout << ans[i] << '\n';
}
