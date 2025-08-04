#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

void solve() {
    int n, m, x, y; cin >> n >> m >> x >> y;
    x--, y--;
    vector<vector<int>> g(n + 1);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    g[n].emplace_back(x);

    rep(i, n) sort(g[i].begin(), g[i].end());

    // 貪欲にyに辿り着くまでdfs
    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v, vector<int>& ps) -> bool {
        ps.push_back(v);
        if (v == y) {
            int sz = ps.size();
            for (int i = 1; i < sz; i++) cout << ps[i] + 1 << " ";
            cout << "\n";
            return true;
        }
        seen[v] = true;
        for (auto u : g[v]) {
            if (!seen[u] && dfs(dfs, u, ps)) return true;
        }
        ps.pop_back();
        return false;
    };
    vector<int> ini;
    dfs(dfs, n, ini);
}

int main() {
    int t; cin >> t;
    rep(i, t) solve();
}
