#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, ll>;

// 想定解
// 全パス探索

// ポイント
// 全パス探索の書き方を知っているか。
// → dfsの帰りがけにseenを戻すことで、使うエッジが違う時に頂点を再訪できる
// xorは局所最適性が成立しない集計値として有名

int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int u, v; ll w; cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    ll ans = numeric_limits<ll>::max();
    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v, ll xo) -> void {
        seen[v] = true;

        if (v == n - 1) ans = min(ans, xo);
        else {
            for (auto [u, w] : g[v]) {
                if (!seen[u]) dfs(dfs, u, xo ^ w);
            }
        }

        seen[v] = false;
    };
    dfs(dfs, 0, 0);

    cout << ans << endl;
}
