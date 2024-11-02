#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev;  // rev: 辺の番号
    Edge() {};
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8;  // 重みの最大値+1
vector<vector<Edge>> G;
vector<bool> used;

void addEdge(int from, int to, int cap) {
    G[from].emplace_back(to, cap, G[to].size());
    G[to].emplace_back(from, 0, G[from].size() - 1);
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;

    // 逆辺も含めて探索する
    for (auto &adj : G[v]) {
        if (!used[adj.to] && adj.cap > 0) {
            int d = dfs(adj.to, t, min(f, adj.cap));
            if (d > 0) {
                // 残余グラフを計算
                adj.cap -= d;
                G[adj.to][adj.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow() {
    // n: 頂点数, s: source, t: sink
    int n, s, t; cin >> n >> s >> t;

    used = vector<bool>(n);
    int ans = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) ans += f;
        else break;
    }
    return ans;
}
