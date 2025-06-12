#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 100101001;

int main() {
    int n, q; cin >> n >> q;
    vector<vector<P>> g(n);

    auto dijkstra = [&](int s, int t) {
        priority_queue<P, vector<P>, greater<P>> pq; pq.emplace(0, s);
        vector<int> dist(n, INF); dist[s] = 0;
        while (!pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if (d > dist[v]) continue;
            for (auto [u, w] : g[v]) {
                int nd = d + w;
                if (nd < dist[u]) pq.emplace(dist[u] = nd, u);
            }
        }
        return dist[t] == INF ? -1 : dist[t];
    }; 

    rep(i, q) {
        int t; cin >> t;
        if (t == 0) {
            int u, v; cin >> u >> v, u--, v--;
            cout << dijkstra(u, v) << '\n';
        } else {
            int u, v, w; cin >> u >> v >> w, u--, v--;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
    }
}
