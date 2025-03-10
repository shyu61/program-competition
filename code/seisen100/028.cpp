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

    vector<int> dist(n, -1);
    auto bfs = [&](int s) -> void {
        queue<int> que;
        que.push(s);
        dist[s] = 0;
        while (!que.empty()) {
            auto v = que.front(); que.pop();
            for (auto u : g[v]) {
                if (dist[u] != -1) continue;
                que.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    };
    bfs(0);

    rep(i, n) {
        cout << i + 1 << ' ' << dist[i] << '\n';
    }
}
