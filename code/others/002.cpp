// 有向グラフの閉路検出: トポロジカルソート
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 5e5;
int indeg[NMAX];
bool seen[NMAX];
vector<vector<int>> G;
vector<int> tsort;

void bfs(int v) {
    queue<int> que;
    que.push(v);
    seen[v] = true;
    while (!que.empty()) {
        int v = que.front(); que.pop();
        tsort.push_back(v);
        for (auto adj : G[v]) {
            indeg[adj]--;
            if (!seen[adj] && indeg[adj] == 0) {
                seen[adj] = true;
                que.push(adj);
            }
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    G = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        indeg[v]++;
    }

    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0 && !seen[i]) bfs(i);
    }

    cout << (tsort.size() != n) << endl;
}
