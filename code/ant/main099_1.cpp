// 最小費用流: p199
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ベルマンフォード法による解法
// 最小費用は`最短路問題に容量制限を加えたもの`と考えることができる
// 重みは負を取り得るので、ベルマンフォーを使う。容量制限を守りつつ最短路にmin(F,最大フロー)を流し、残余グラフに対してこの操作を繰り返す

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int INF = 1e8; // 最大距離
int n;
vector<vector<Edge>> G;
vector<int> dist, prevv, preve;

void addEdge(int from, int to, int cap, int cost) {
    G[from].emplace_back(to, cap, cost, G[to].size());
    G[to].emplace_back(from, 0, -cost, G[from].size() - 1);  // 逆辺
}

int minCostFlow(int s, int t, int f) {
    int res = 0;
    while (f > 0) {
        // ベルマンフォード法でs-tの最短路を求める
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        while (1) {
            bool update = false;
            for (int v = 0; v < n; v++) {
                for (int i = 0; i < G[v].size(); i++) {
                    Edge e = G[v][i];
                    if (e.cap > 0 && dist[v] != INF && dist[e.to] > dist[v] + e.cost) {
                        dist[e.to] = dist[v] + e.cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        update = true;
                    }
                }
            }
            if (!update) break;
        }
        // 現在の残余グラフでsからtへ辿り着けない、つまりこれ以上フローを増やせない
        if (dist[t] == INF) return -1;

        // s-tの最短路に目一杯流す
        // 保存しておいた最短路を逆順に辿りつつ最小容量を求める
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * dist[t];
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
    int m, s, t, f; cin >> n >> m >> s >> t >> f;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int from, to, cap, cost; cin >> from >> to >> cap >> cost;
        addEdge(from, to, cap, cost);
    }

    dist = prevv = preve = vector<int>(n);
    cout << minCostFlow(s, t, f) << endl;
}
