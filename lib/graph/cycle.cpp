#include <bits/stdc++.h>
using namespace std;

// | --          | Undirected | Directed | Functional |
// | Detect      | union-find | dfs      | union-find |
// | Reconstruct | dfs        | dfs      | union-find |

vector<vector<int>> G;
vector<int> color, ht;

int dfs(int v) {
    color[v] = 1;
    ht.push_back(v);
    for (auto adj : G[v]) {
        if (color[adj] == 2) continue;
        if (color[adj] == 1){
            return adj;
        }
        int pos = dfs(adj);
        if (pos != -1) return pos;
    }
    color[v] = 2;
    ht.pop_back();
    return -1;
}

// サイクル復元
vector<int> reconstruct(int pos) {
    vector<int> res;
    bool in_cyc = false;
    for (auto v : ht) {
        if (v == pos) in_cyc = true;
        if (in_cyc) res.push_back(v);
    }
    return res;
}

int main() {
    int N, M; cin >> N >> M;
    G = vector<vector<int>>(N);
    color = vector<int>(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }

    int pos = dfs(0);
    if (pos == -1) cout << -1 << endl;
    else {
        vector<int> cyc = reconstruct(pos);
        for (auto v : cyc) cout << v << endl;
    }
}

namespace dsu_cycle_detection {
    #include <lib/union_find.cpp>

    int main() {
        int N, M; cin >> N >> M;
        vector<vector<int>> G(N);
        for (int i = 0; i < M; i++) {
            int u, v; cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        vector<bool> seen(N);
        UnionFind uf(N);
        for (int i = 0; i < N; i++) {
            seen[i] = true;
            for (auto v : G[i]) {
                if (seen[v]) continue;
                if (!uf.unite(i, v)) {
                    cout << 1 << endl;
                    return 0;
                }
                seen[v] = true;
            }
        }
    }
}
