// 有向グラフの閉路検出: dfs
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 5e5;
bool seen[NMAX], finished[NMAX];
vector<vector<int>> G;

int dfs(int v) {
    seen[v] = true;
    for (auto adj : G[v]) {
        if (finished[adj]) continue;
        if (seen[adj] && !finished[adj]) return adj;

        int pos = dfs(adj);
        if (pos != -1) return pos;
    }

    finished[v] = true;
    return -1;
}

int main() {
    int n, m; cin >> n >> m;
    G = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }

    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        pos = dfs(i);
        if (pos != -1) {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}
