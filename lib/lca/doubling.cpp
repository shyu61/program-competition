#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 初期化: O(nlogn), クエリ: O(logn)
int main() {
    int n;
    vector<vector<int>> g(n);

    const int LOG = 17;
    vector<int> depth(n);
    vector<vector<int>> parent(LOG, vector<int>(n));  // parent[i][j]:=jから親を2^i辿った先の頂点
    auto dfs = [&](auto dfs, int v, int p = -1, int d = 0) -> void {
        parent[0][v] = p;
        depth[v] = d;
        for (auto to : g[v]) {
            if (to == p) continue;
            dfs(dfs, to, v, d + 1);
        }
    };
    dfs(dfs, 0);
    rep(i, LOG - 1) {
        rep(j, n) {
            if (parent[i][j] < 0) parent[i + 1][j] = -1;
            else parent[i + 1][j] = parent[i][parent[i][j]];
        }
    }

    auto lca = [&](int u, int v) -> int {
        if (depth[u] > depth[v]) swap(u,v);
        // 深さを揃える
        rep(i, LOG) {
            if (depth[v] - depth[u] >> i & 1) v = parent[i][v];
        }
        if (u == v) return u;

        // lcaより親の頂点はu,vで全て一致することを利用する
        for (int i = LOG - 1; i >= 0; i--) {
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    };
}
