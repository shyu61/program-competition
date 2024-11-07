#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8;  // 重みの最大値
int V;
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

int maxFlow(int s, int t) {
    used = vector<bool>(V);

    int res = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) res += f;
        else break;
    }
    return res;
}

int main() {
    int n, m, s, t; cin >> n >> m >> s >> t;
    V = n + 2;
    G = vector<vector<Edge>>(V);
    for (int i = 0; i < m; i++) {
        int x, y, c; cin >> x >> y >> c;
        addEdge(x, y, c);
    }
    maxFlow(s, t);
}
