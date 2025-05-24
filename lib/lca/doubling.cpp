#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 初期化: O(nlogn), クエリ: O(logn)
struct LCA {
    const int LOG = 18;
    int n;
    vector<int> depth;
    // parent[i][j]:=jから親を2^i辿った先の頂点
    vector<vector<int>> g, parent;
    LCA(const vector<vector<int>>& g_) : g(g_) {
        n = g_.size();
        depth.assign(n, 0);
        parent.assign(LOG, vector<int>(n));

        dfs(0);
        rep(i, LOG - 1) {
            rep(j, n) {
                if (parent[i][j] < 0) parent[i + 1][j] = -1;
                else parent[i + 1][j] = parent[i][parent[i][j]];
            }
        }
    }

    int lca(int u, int v) {
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

    int len(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    private:
        void dfs(int v, int p = -1, int d = 0) {
            parent[0][v] = p;
            depth[v] = d;
            for (auto to : g[v]) {
                if (to == p) continue;
                dfs(to, v, d + 1);
            }
        }
};
