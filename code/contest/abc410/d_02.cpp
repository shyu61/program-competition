#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, ll>;
const ll INF = numeric_limits<ll>::max();

// https://atcoder.jp/contests/abc396/tasks/abc396_d

// 🔷抑えるべき抽象論は？
// 全パス探索
// 計算量はO(V!)だが、V<=10より可能
// xorは局所最適性が成立しないので、まずは全探索を考えるのがセオリー

int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int u, v; ll w; cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    // 全パス探索: 帰りがけに訪問済み頂点をリセットしていく
    ll ans = INF;
    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v, ll xo) {
        if (v == n - 1) {
            ans = min(ans, xo);
            return;
        }

        seen[v] = true;
        for (auto [u, w] : g[v]) {
            if (!seen[u]) dfs(dfs, u, xo ^ w);
        }
        seen[v] = false;
    };
    dfs(dfs, 0, 0);
    cout << ans << endl;
}
