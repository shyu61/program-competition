// グラフの探索: p93
#include <bits/stdc++.h>
using namespace std;

// n部グラフ: 隣接する頂点を異なる色で塗る時、n色で塗り切れるグラフ
// 正確には、「同集合内の頂点同士は互いに隣接しない」という条件を満たすn個の頂点集合に分けることができるグラフ

int n;
vector<vector<int>> G;
vector<int> color;

bool dfs(int v, int c) {
    for (auto adj : G[v]) {
        if (color[adj] != 0) {
            if (color[adj] == c) return false;
            continue;
        }
        color[adj] = -c;
        if (!dfs(adj, -c)) return false;
    }
    return true;
}

int main() {
    cin >> n;
    G = vector<vector<int>>(n);
    color = vector<int>(n);

    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        if (color[i] != 0) continue;
        if (!dfs(i, 1)) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
