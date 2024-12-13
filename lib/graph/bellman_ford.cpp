#include <bits/stdc++.h>
using namespace std;

// ベルマンフォード法の一言まとめ:
// ある頂点iへの最短路は、その隣接ノードjへの最短路d[j]+ejiによって作られ、
// 1回の緩和操作で少なくとも1頂点の最短路は確定する性質を利用し、最大V-1回の緩和操作を行うことで単一始点最短路問題を解くというもの

struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {};
};

const int INF = 1e9 + 1;
int n;
vector<vector<Edge>> G;
vector<int> d;

void bellman_ford(int s) {
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
