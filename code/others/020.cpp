#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int x, y, z; cin >> x >> y >> z;
        x--, y--;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }

    vector<int> ans(n);
    rep(d, 30) {
        vector<int> a(n, -1);
        rep(v, n) {
            if (a[v] != -1) continue;

            vector<vector<int>> c(2);
            auto dfs = [&](auto dfs, int v, int xo) -> bool {
                if (a[v] != -1) return a[v] == xo;
                a[v] = xo;
                c[xo].push_back(v);
                for (auto [u, w] : g[v]) {
                    if (!dfs(dfs, u, xo ^ (w >> d & 1))) return false;
                }
                return true;
            };

            if (!dfs(dfs, v, 0)) {
                cout << -1 << endl;
                return 0;
            }

            if (c[0].size() > c[1].size()) swap(c[0], c[1]);
            for (auto x : c[0]) ans[x] |= 1 << d;
        }
    }

    rep(i, n) cout << ans[i] << ' ';
    cout << endl;
}
