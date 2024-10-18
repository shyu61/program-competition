// 最短路問題(ワーシャルフロイド法): p98
#include <bits/stdc++.h>
using namespace std;

// APSPを求める方法。計算量はO(V^3)、負の重みがあってもOK
// いわゆるナップサックDP。i->jへ移動するのに0-kのノードを考慮するとすると、
// dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])となる
// これは2項間DPなので添字の省略が可能

struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {};
};

const int INF = 1e9 + 1;
int n, m, s;
vector<vector<Edge>> G;
vector<vector<int>> d;

void warshallFloyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main() {
    cin >> n >> m >> s;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        G[u].emplace_back(v, cost);
    }

    d = vector<vector<int>>(n, vector<int>(n));
    warshallFloyd();
}
