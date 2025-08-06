#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc168/tasks/abc168_d
// bfsで遷移した経路を復元する問題

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> ans(n);
    auto bfs = [&](int v) {
        queue<int> que;
        que.push(v);
        vector<int> dist(n, -1);
        dist[v] = 0;

        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto u : g[v]) {
                if (dist[u] != -1) continue;
                que.push(u);
                dist[u] = dist[v] + 1;
                ans[u] = v;
            }
        }
    };
    bfs(0);

    cout << "Yes" << endl;
    for (int i = 1; i < n; i++) cout << ans[i] + 1 << "\n";
}
