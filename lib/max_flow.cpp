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

int maxFlow(int n, int s, int t) {
    used = vector<bool>(n);

    int res = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) res += f;
        else break;
    }
    return res;
}

int bipartiteMatching(int N, int K, int s, int t) {
    return maxFlow(N + K, s, t);
}

int main() {
    // ---------- 最大フロー ----------
    int n, m, s, t; cin >> n >> m >> s >> t;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int x, y, c; cin >> x >> y >> c;
        addEdge(x, y, c);
    }
    maxFlow(n, s, t);

    // ---------- 二部マッチング ----------
    int N, K; cin >> N >> K;
    G = vector<vector<Edge>>(N + K + 2);
    int s = N + K, t = s + 1;
    for (int i = 0; i < N; i++) addEdge(s, i, 1);
    for (int i = 0; i < K; i++) addEdge(t, i + N, 1);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        addEdge(x, y + N, 1);
    }
    bipartiteMatching(N, K, s, t);
}
