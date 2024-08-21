// scc分解
#include <bits/stdc++.h>
using namespace std;

const int V_MAX = 1e5;
bool seen[V_MAX];
int scc[V_MAX];
vector<vector<int>> G, rG;
vector<int> po;

void dfs(int v) {
    if (seen[v]) return;
    seen[v] = true;
    for (auto adj : G[v]) dfs(adj);
    po.push_back(v);  // node番号がpost_orderで格納される
}

void rdfs(int v, int k) {
    if (seen[v]) return;
    seen[v] = true;
    for (auto adj : rG[v]) rdfs(adj, k);
    scc[v] = k;
}

int main() {
    int v, e; cin >> v >> e;
    G = vector<vector<int>>(v);
    rG = vector<vector<int>>(v);
    po.reserve(v);
    for (int i = 0; i < e; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        rG[v].push_back(u);
    }

    for (int i = 0; i < v; i++) {
        if (!seen[i]) dfs(i);
    }

    memset(seen, 0, sizeof(seen));
    int k = 0;
    for (int i = v - 1; i >= 0; i--) {
        if (!seen[po[i]]) rdfs(po[i], k++);
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        int ans = scc[u] == scc[v] ? 1 : 0;
        cout << ans << endl;
    }
}
