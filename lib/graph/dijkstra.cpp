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

// priority_queueを使う場合は、すでに最短経路木に含まれるノードはpqに追加されないので、
// usedで管理する必要がない

void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d = vector<int>(n, INF); d[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [cost, v] = pq.top(); pq.pop();
        if (cost > d[v]) continue;

        for (auto adj : G[v]) {
            if (d[adj.to] > d[v] + adj.cost) {
                d[adj.to] = d[v] + adj.cost;
                pq.emplace(d[adj.to], adj.to);
            }
        }
    }
}
