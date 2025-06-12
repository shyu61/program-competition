#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

int main() {
    int n, m, s; cin >> n >> m >> s;
    vector<vector<P>> g(n);
    rep(i, m) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }

    // dijkstra
    priority_queue<P, vector<P>, greater<P>> pq; pq.emplace(0, s);
    vector<int> dist(n, INF);
    dist[s] = 0;
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d > dist[v]) continue;
        for (auto [u, w] : g[v]) {
            int nd = d + w;
            if (nd < dist[u]) pq.emplace(dist[u] = nd, u);
        }
    }

    rep(i, n) {
        if (dist[i] == INF) cout << "INF" << '\n';
        else cout << dist[i] << '\n';
    }
}
