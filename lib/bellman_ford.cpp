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

void bellmanFord(int s) {
    d = vector<int>(n, INF);
    d[s] = 0;
    while (1) {
        bool update = false;
        for (int i = 0; i < n; i++) {
            for (auto adj : G[i]) {
                if (d[i] != INF && d[adj.to] > d[i] + adj.cost) {
                    d[adj.to] = d[i] + adj.cost;
                    update = true;
                }
            }
        }
        if (!update) break;
    }
}
