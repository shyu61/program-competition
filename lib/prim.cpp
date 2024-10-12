#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {};
};

const int INF = 1e9 + 1;
int n;
vector<vector<Edge>> G;
vector<int> d;

int prim(int s) {
    int total = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d = vector<int>(n, INF); d[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [cost, v] = pq.top(); pq.pop();
        if (cost > d[v]) continue;

        total += cost;

        for (auto adj : G[v]) {
            if (d[adj.to] > adj.cost) {
                d[adj.to] = adj.cost;
                pq.emplace(d[adj.to], adj.to);
            }
        }
    }
    return total;
}
