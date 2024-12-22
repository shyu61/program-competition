// 二部マッチング: p195
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最大フローを使った方法

struct Edge {
    int to, cap, rev;  // rev: 辺の番号
    Edge() {};
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8;  // 最大頂点数+1
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

int main() {
    int N, K, M; cin >> N >> K >> M;
    G = vector<vector<Edge>>(N + K + 2);  // s,tを含む
    int s = N + K, t = s + 1;
    // sourceから各コンピュータにedgeを張る
    // 各コンピュータは1つの仕事しかできないので、sourceからコンピュータへの流量は1にする
    // -> 各コンピュータが同時に2つの仕事ができるなら、2流す
    for (int i = 0; i < N; i++) addEdge(s, i, 1);
    // 各仕事からsinkにedgeを張る
    for (int i = 0; i < K; i++) addEdge(i + N, t, 1);

    for (int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        x--; y = y + N - 1;
        addEdge(x, y, 1);
    }

    used = vector<bool>(N + K + 2);
    int ans = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) ans += f;
        else break;
    }

    cout << ans << endl;
}
