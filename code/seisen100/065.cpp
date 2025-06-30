#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using TP = tuple<int, int, int>;

// mstを使うケース
// グラフのパス/重みの和に関する最小化問題で、
// - クラスタリング(連結成分構築)
//   - クラスカル法そのもの
// - グラフのボトルネック最小化(最大コストの最小化)
//   - mstは辺の総和の最小グラフであると同時に、最大重みの最小化グラフでもある
// イメージ
// - 最短路: 線(パス)
// - mst: 面(ネットワーク)

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
};

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<TP> es(m);
    rep(i, m) {
        int u, v, c; cin >> u >> v >> c, u--, v--;
        es[i] = {c, u, v};
    }
    sort(es.begin(), es.end());

    int ans = 0, cnt = 0;
    UnionFind uf(n);
    for (auto [c, u, v] : es) {
        if (uf.same(u, v)) continue;
        if (n == k) break;
        uf.merge(u, v);
        ans += c;
        n--;
    }

    cout << ans << endl;
}
