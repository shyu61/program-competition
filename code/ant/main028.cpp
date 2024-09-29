// 最大流: p188
#include <bits/stdc++.h>
using namespace std;

// フォードファルカーソンのアルゴリズムは、一度に最大流を求めるのではなく、
// 一度作成したs->tの経路を何度もdfsすることで繰り返し更新し、更新がなくなった時点で最大流とする考え方
// つまりはdfsによるルート探索と重みに応じた流量の決定を1セットとして、これを複数セット行うイメージ
// 1. 経路探索
// 2. その経路内で目一杯水を流す(最初のfはINFとし、各エッジで流れる流量をmin(f, adj.cap)とすることで表現)
// 3. 逆辺という概念を導入しつつ1,2を繰り返す

struct Edge {
    int to, cap, rev; // 逆辺(edge番号)
    Edge(int to, int cap, int rev): to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8;  // 重みのmax+1以上を設定
int n, m, s, t;
vector<vector<Edge>> g;
vector<bool> seen;

// f: 現時点でノードvに流し込める最大流量
// 戻り値: 後続も考慮した結果流し込めた最大流量
int dfs(int v, int f) {
    if (v == t) return f;
    seen[v] = true;

    for (auto &adj : g[v]) {
        if (seen[adj.to] || adj.cap <= 0) continue;
        // min(f, adj.cap)によって目一杯水を流すという操作を表現している
        int d = dfs(adj.to, min(f, adj.cap));
        if (d > 0) {
            adj.cap -= d;
            g[adj.to][adj.rev].cap += d;
            return d;
        }
    }
    return 0;
}

int main() {
    cin >> n >> m;
    g = vector<vector<Edge>>(n);
    seen = vector<bool>(n);
    for (int i = 0; i < m; i++) {
        int a, b, cap;
        cin >> a >> b >> cap;
        g[a].emplace_back(b, cap, g[b].size());
        g[b].emplace_back(a, 0, g[a].size() - 1);
    }
    cin >> s >> t;

    int ans = 0;
    while (1) {
        fill(seen.begin(), seen.end(), 0);
        int f = dfs(s, INF);
        if (f == 0) {
            cout << ans << endl;
            return 0;
        }
        ans += f;
    }
}
