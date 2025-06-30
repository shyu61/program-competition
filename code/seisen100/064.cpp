#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
using TP = tuple<int, int, int>;

// MSTアルゴリズム
// - プリム法: O(ElogV)
//   - 一つの木を成長させていく戦略
//   - 適当な点から始めて、現在の木に隣接するedgeのうち最小のものを木に加えることを繰り返す
// - クラスカル法: O(ElogE)
//   - それぞれ木を成長させmergeしていく戦略
//   - 重みが小さいedgeから順に見ていき、閉路を形成しない限りmstに加えていく

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

// プリム法: O(ElogV)
int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int u, v, c; cin >> u >> v >> c;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }

    int ans = 0;
    priority_queue<P, vector<P>, greater<>> pq; pq.emplace(0, 0);
    vector<bool> in_mst(n);
    while (!pq.empty()) {
        auto [c, v] = pq.top(); pq.pop();
        if (in_mst[v]) continue;
        in_mst[v] = true;
        ans += c;
        for (auto [to, nc] : g[v]) {
            if (in_mst[to]) continue;
            pq.emplace(nc, to);
        }
    }
    cout << ans << endl;
}

// クラスカル法: O(ElogE)
int main() {
    int n, m; cin >> n >> m;
    vector<TP> es(m);
    rep(i, m) {
        int u, v, w; cin >> u >> v >> w;
        es[i] = {w, u, v};
    }

    sort(es.begin(), es.end());

    int ans = 0;
    UnionFind uf(n);
    for (auto [c, u, v] : es) {
        if (uf.same(u, v)) continue;
        uf.merge(u, v);
        ans += c;
    }

    cout << ans << endl;
}
