#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int INF = 1e8; // 最大距離
int V;
vector<vector<Edge>> G;

void add_edge(int from, int to, int cap, int cost) {
    G[from].emplace_back(to, cap, cost, G[to].size());
    G[to].emplace_back(from, 0, -cost, G[from].size() - 1);
}

int min_cost_flow(int s, int t, int f) {
    vector<int> dist(V), prevv(V), preve(V), h(V);
    int res = 0;
    while (f > 0) {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [w, v] = pq.top(); pq.pop();
            if (w > dist[v]) continue;

            for (int i = 0; i < G[v].size(); i++) {
                Edge e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    pq.emplace(dist[e.to], e.to);
                }
            }
        }
        // 現在の残余グラフでsからtへ辿り着けない、つまりこれ以上フローを増やせない
        if (dist[t] == INF) return -1;
        // ポテンシャルの更新
        for (int i = 0; i < V; i++) h[i] += dist[i];
        // s-tの最短路に目一杯流す
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        // 残余グラフの更新
        for (int v = t; v != s; v = prevv[v]) {
            Edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

int main() {
    int n, m, s, t, f; cin >> n >> m >> s >> t >> f;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int from, to, cap, cost; cin >> from >> to >> cap >> cost;
        add_edge(from, to, cap, cost);
    }

    int V = n;
    cout << min_cost_flow(s, t, f) << endl;
}
