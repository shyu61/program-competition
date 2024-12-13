#include <bits/stdc++.h>
using namespace std;

const int NMAX = 5e5;
bool seen[NMAX], finished[NMAX];
stack<int> history;
vector<vector<int>> G;

int dfs(int v) {
    seen[v] = true;
    history.push(v);
    for (auto adj : G[v]) {
        if (finished[adj]) continue;
        if (seen[adj] && !finished[adj]) {
            return adj;
        }

        int pos = dfs(adj);
        if (pos != -1) return pos;
    }

    history.pop();
    finished[v] = true;
    return -1;
}

vector<int> reconstruct(int v) {
    vector<int> cyc;
    while (!history.empty()) {
        int u = history.top(); history.pop();
        cyc.push_back(u);
        if (u == v) break;
    }
    reverse(cyc.begin(), cyc.end());
    return cyc;
}

int main() {
    int n, m; cin >> n >> m;
    G = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }

    int pos = -1;
    vector<int> cyc;
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        pos = dfs(i);
        if (pos != -1) {
            cyc = reconstruct(pos);
            break;
        }
    }

    if (cyc.empty()) cout << -1 << endl;
    else {
        cout << cyc.size() << endl;
        for (auto v : cyc) cout << v << endl;
    }
}
