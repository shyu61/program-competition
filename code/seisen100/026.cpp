#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 木上で累積和を取る ← 木を1次元配列的に捉える

// 罠
// なし

int main() {
    int n, q; cin >> n >> q;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> c(n);
    rep(i, q) {
        int p, x; cin >> p >> x, p--;
        c[p] += x;
    }

    auto dfs = [&](auto dfs, int v, int p, ll cost) -> void {
        c[v] += cost;
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v, c[v]);
        }
    };

    dfs(dfs, 0, -1, 0);

    rep(i, n) cout << c[i] << ' ';
    cout << endl;
}
