#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n) {
        int u, k; cin >> u >> k, u--;
        rep(j, k) {
            int v; cin >> v, v--;
            g[u].push_back(v);
        }
    }

    int t = 1;
    vector<int> d(n), f(n);
    auto dfs = [&](auto dfs, int v) -> void {
        d[v] = t++;
        for (auto u : g[v]) {
            if (d[u] > 0) continue;
            dfs(dfs, u);
        }
        f[v] = t++;
    };

    rep(i, n) {
        if (f[i] == 0) dfs(dfs, i);
    }
    rep(i, n) {
        cout << i + 1 << ' ' << d[i] << ' ' << f[i] << '\n';
    }
}
