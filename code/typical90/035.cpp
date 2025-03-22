#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<vector<P>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    vector<bool> used(n - 1);
    auto bfs = [&](int s, int t) -> int {
        int sum = 0;
        queue<int> que;
        que.push(s);
        vector<int> dist(n, -1);
        vector<P> parent(n, {-1, -1});
        dist[s] = 0;

        while (!que.empty()) {
            int v = que.front(); que.pop();
            if (v == t) break;
            for (auto [u, e] : g[v]) {
                if (dist[u] != -1) continue;
                que.push(u);
                dist[u] = dist[v] + 1;
                parent[u] = {v, e};
            }
        }

        int cur = t;
        while (cur != -1) {
            auto [v, e] = parent[cur];
            if (v != -1 && !used[e]) {
                sum++;
                used[e] = true;
            }
            cur = v;
        }
        return sum;
    };

    int q; cin >> q;
    rep(i, q) {
        used.assign(n - 1, false);
        int k, pre, ans = 0; cin >> k >> pre, pre--;
        rep(j, k - 1) {
            int v; cin >> v, v--;
            ans += bfs(pre, v);
            pre = v;
        }
        cout << ans << '\n';
    }
}

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    const int LOG = 17;
    vector<int> depth(n);
    vector<vector<int>> parent(LOG, vector<int>(n));
    auto dfs = [&](auto dfs, int v, int p, int d) -> void {
        parent[0][v] = p;
        depth[v] = d;
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v, d + 1);
        }
    };
    dfs(dfs, 0, -1, 0);
    rep(i, LOG - 1) {
        rep(j, n) {
            if (parent[i][j] < 0) parent[i + 1][j] = -1;
            else parent[i + 1][j] = parent[i][parent[i][j]];
        }
    }

    vector<int> square(LOG); square[0] = 1;
    rep(i, LOG - 1) {
        square[i + 1] = square[i] * 2;
    }

    auto lca = [&](int u, int v, int& d) -> int {
        if (depth[u] > depth[v]) swap(u, v);
        rep(i, LOG) {
            if (depth[v] - depth[u] >> i & 1) {
                v = parent[i][v];
                d += square[i];
            }
        }
        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
                d += square[i] * 2;
            }
        }
        return parent[0][u];
    };

    int q; cin >> q;
    rep(i, q) {
        int k, pre, ans = 0; cin >> k >> pre, pre--;
        rep(j, k - 1) {
            int v; cin >> v, v--;
            int res = lca(pre, v, ans);
            cout << "pre=" << pre + 1 << ", v=" << v + 1 << ", res=" << res + 1 << ", ans=" << ans << endl;
            // if (res != pre) ans++;
            // if (res != v) ans++;
            pre = res;
        }
        cout << ans << '\n';
    }
}
