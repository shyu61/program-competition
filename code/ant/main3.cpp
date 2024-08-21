// scc分解2
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e4;

bool seen[NMAX];
int scc[NMAX];
vector<int> po;
vector<vector<int>> G, rG;

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
    scc[v] = k;
}

int main() {
    int n, m; cin >> n >> m;
    G = vector<vector<int>>(n);
    rG = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        rG[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!seen[i]) dfs(i);
    }

    memset(seen, 0, sizeof(seen));
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (!seen[po[i]]) rdfs(po[i], k++);
    }

    int last_scc, ans = 0;
    for (int i = 0; i < n; i++) {
        if (scc[i] == k - 1) {
            last_scc = i;
            ans++;
        }
    }
    memset(seen, 0, sizeof(seen));
    rdfs(last_scc, 0);
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            ans = 0;
            break;
        }
    }
    if (!seen[last_scc]) ans = 0;

    cout << ans << endl;
}
