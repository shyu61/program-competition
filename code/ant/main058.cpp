// 最短路問題(経路復元): p98
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {};
};

const int INF = 1e5;
int n;
vector<vector<Edge>> G;
vector<int> pre;

void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> d(n, INF);
    pq.emplace(s, 0);

    while (!pq.empty()) {
        auto [v, dist] = pq.top(); pq.pop();
        if (dist > d[v]) continue;
        for (auto adj : G[v]) {
            if (d[adj.to] > d[v] + adj.cost) {
                d[adj.to] = d[v] + adj.cost;
                pq.emplace(adj.to, d[adj.to]);
                pre[adj.to] = v;
            }
        }
    }
}

int main() {
    int s, t; cin >> n >> s >> t;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < n; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        G[u].emplace_back(v, cost);
    }

    pre = vector<int>(n);
    dijkstra(s);

    // s->tへの最短経路の復元
    vector<int> path;
    for (; t != -1; t = pre[t]) path.push_back(t);
    sort(path.rbegin(), path.rend());

    for (auto x : path) cout << x << " ";
    cout << endl;
}
