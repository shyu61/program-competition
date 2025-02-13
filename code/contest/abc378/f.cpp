#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 経路探索問題, 数え上げ, 連結成分問題, 木DP

// 方針
// 木における経路探索は適当なLCAを決めて木DPするのが基本戦略
// また、グラフにおいて同一構造の考慮が必要なケースは、縮約して問題を単純化できないか検討するのも鉄則
// -> 縮約にはunionfindを使うとよい

// ポイント
// 単純グラフ: 多重辺も自己ループももたないグラフ
// グラフにおける同一構造は縮約して考えることを検討する
// 木の経路探索問題は、適当なLCAを決めて木DPで解けるケースが多い
// 木DPは基本bottom-upなので、dfsの帰りがけで処理を行う
// 複数の子からの情報の扱いが重要。累積的に使うのか組み合わせ的に使うのかなど

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

// 同一構造の縮約を使った解法
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

// 木DPを使った解法
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

    ll ans = 0;
    vector<ll> dp(n);
    auto dfs = [&](auto dfs, int v, int p) -> void {
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v);
            // パスの中間点になる
            if (deg[v] == 3) {
                ans += dp[v] * dp[u];
                dp[v] += dp[u];
            }
            // パスの終点になる
            if (deg[v] == 2) ans += dp[u];
        }
        if (deg[v] == 2) dp[v]++;
    };

    dfs(dfs, 0, -1);

    // 次数2の頂点が隣接している部分を除外
    rep(i, n) {
        for (auto j : g[i]) {
            if (i < j && deg[i] == 2 && deg[j] == 2) ans--;
        }
    }

    cout << ans << endl;
}
