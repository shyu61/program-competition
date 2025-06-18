#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        deg[v]++;
    }

    queue<P> que;
    rep(i, n) if (deg[i] == 0) que.emplace(i, 0);

    int ans = 0;
    while (!que.empty()) {
        auto [v, d] = que.front(); que.pop();
        ans = max(ans, d);
        for (auto u : g[v]) {
            deg[u]--;
            if (deg[u] == 0) {
                que.emplace(u, d + 1);
            }
        }
    }
    cout << ans << endl;
}
