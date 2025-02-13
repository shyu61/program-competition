#include <bits/stdc++.h>
using namespace std;

// O(n)
int main() {
    int n;
    vector<vector<int>> g(n);

    // 前処理
    vector<int> parent(n), depth(n);
    auto dfs = [&](auto dfs, int v, int p, int d) -> void {
        parent[v] = p;
        depth[v] = d;
        for (auto to : g[v]) {
            if (to == p) continue;
            dfs(dfs, to, v, d + 1);
        }
    };
    dfs(dfs, 0, -1, 0);

    auto lca = [&](int u, int v) -> int {
        // 深さを揃える
        while (depth[u] > depth[v]) u = parent[u];
        while (depth[v] > depth[u]) v = parent[v];
        while (u != v) {
            u = parent[u];
            v = parent[v];
        }
        return u;
    };
}
