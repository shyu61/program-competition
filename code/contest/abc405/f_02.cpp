#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷初見でどうやったら解けるか
// 🔷抑えるべき抽象論は？
// 線分交差問題は、1次元配列の区間問題に変換できる
// 所与の線分が互いに交差しない場合、包含グラフを考えと良い
// - 包含グラフにおいて、ある頂点の祖先は、その区間を完全に包含する区間の集合と一致する

// 🔷類問を考える
// 包含グラフの活用
// - 2区間を包含する最小区間: lca(u,v)
// - 2区間を包含する区間の個数: depth[lca(u,v)]
// - 2区間どちらも包含しない区間の個数: 

struct LCA {
    const int LOG = 18;
    int n;
    vector<int> depth;
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
        rep(i, LOG) {
            if (depth[v] - depth[u] >> i & 1) v = parent[i][v];
        }
        if (u == v) return u;
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

int main() {
    int n, m; cin >> n >> m;
    vector<int> id(n * 2);
    rep(i, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        id[a] = 1, id[b] = -1;
    }

    vector<int> ms(n * 2);
    vector<vector<int>> g(m + 1);
    {
        stack<int> st; st.push(0);
        int num = 1;
        rep(i, n * 2) {
            if (id[i] == 1) {
                int par = st.top();
                g[par].push_back(num);
                g[num].push_back(par);
                st.push(num);
                num++;
            }
            if (id[i] == -1) st.pop();
            ms[i] = st.top();
        }
    }

    LCA gg(g);
    int q; cin >> q;
    while (q--) {
        int c, d; cin >> c >> d;
        c--, d--;
        cout << gg.len(ms[c], ms[d]) << '\n';
    }
}
