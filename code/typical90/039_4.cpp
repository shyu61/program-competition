#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using P = pair<int, int>;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja

// LCA
// - naive: 深さを揃えて互いの親を辿る
// - rmq: オイラーツアーを利用し、u->vに至る間での最小のdを取る頂点を求める
// - ダブリング: naiveと考え方は同じ。深さを揃える部分と親を辿る部分をダブリングにする

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n) {
        int k; cin >> k;
        rep(j, k) {
            int u; cin >> u;
            g[i].push_back(u);
            g[u].push_back(i);
        }
    }

    const int LOG = 17;
    vector<int> depth(n);
    vector<vector<int>> parent(LOG, vector<int>(n));  // parent[i][j]:=jから親を2^i辿った先の頂点
    auto dfs = [&](auto dfs, int v, int p = -1, int d = 0) -> void {
        depth[v] = d;
        parent[0][v] = p;
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v, d + 1);
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
        if (depth[u] > depth[v]) swap(u, v);
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

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}
