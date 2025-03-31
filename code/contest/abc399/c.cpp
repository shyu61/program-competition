#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// 木の性質, 無向グラフの閉路判定
// 木の性質: N頂点の木はN-1本の辺を持つ or 閉路を持たな のどちらかを使う
// 無向グラフの閉路判定: union-findが簡単

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
    int n, m; cin >> n >> m;
    vector<P> es(m);
    rep(i, m) {
        int u, v; cin >> u >> v, u--, v--;
        es[i] = {u, v};
    }

    int ans = 0;
    UnionFind uf(n);
    for (auto [u, v] : es) {
        if (uf.same(u, v)) ans++;
        else uf.merge(u, v);
    }

    cout << ans << endl;
}
