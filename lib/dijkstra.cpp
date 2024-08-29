#include <bits/stdc++.h>
using namespace std;

int n;  // ノード数
vector<vector<pair<int, int>>> G;  // 隣接リスト

void dijkstra(int v) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n);

    pq.emplace(v, 0);
    while (!pq.empty()) {
        auto [u, w] = pq.top(); pq.pop();
        if (w > dist[u]) continue;

        // 距離の更新
        for (auto adj : G[u]) {
            auto [adj_u, adj_w] = adj;
            if (dist[adj_u] > dist[u] + adj_w) {
                dist[adj_u] = dist[u] + adj_w;
                pq.emplace(adj_u, dist[adj_u]);
            }
        }
    }

    // for (int i = 0; i < n; i++) cout << i << " " << dist[i] << endl;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int v, u, w; cin >> v >> u >> w;
        G[v].emplace_back(u, w);
    }

    dijkstra(0);
}
