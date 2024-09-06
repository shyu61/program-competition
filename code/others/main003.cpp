// 有向グラフの閉路検出: SCC分解
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 5e5;
bool seen[NMAX];
vector<vector<int>> G, rG, scc;
vector<int> po;

void dfs(int v) {
    if (seen[v]) return;
    seen[v] = true;
    for (auto adj : G[v]) dfs(adj);
    po.push_back(v);
}

void rdfs(int v, int k) {
    if (seen[v]) return;
    seen[v] = true;
    for (auto adj : rG[v]) rdfs(adj, k);
    // k番目の連結成分の一つがv
    scc[k].push_back(v);
}

int main() {
    int n, m; cin >> n >> m;
    G = vector<vector<int>>(n);
    rG = vector<vector<int>>(n);
    scc = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        rG[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        if (!seen[i]) dfs(i);
    }

    int k = 0;
    memset(seen, 0, sizeof(seen));
    for (int i = n - 1; i >= 0; i--) {
        if (!seen[po[i]]) rdfs(po[i], k++);
    }

    // 自己ループの確認
    // for (int i = 0; i < n; i++) {
    //     for (auto adj : G[i]) {
    //         if (adj == i) {
    //             cout << 1 << endl;
    //             return 0;
    //         }
    //     }
    // }

    // 要素数が2以上の強連結成分があれば閉路が存在する
    for (auto vec : scc) {
        if (vec.size() > 1) {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}
