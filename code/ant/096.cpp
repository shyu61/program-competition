// 最大流: p188
#include <bits/stdc++.h>
using namespace std;

// フォードファルカーソンのアルゴリズム
// 根幹は貪欲法で、dfsでcapが残っているpathを見つける度に目一杯流すという操作を繰り返す
// 逆辺を導入している点がこのアルゴリズムのコアである。
// 逆辺は見つかったpathでの流し方を後から修正するという操作を表現している。
// これは今見つかったpathに目一杯流すのが最適なのか、後から見つかるpathに目一杯流すことが最適なのか現時点では判断できないため、
// 未来に向けて過去を修正する権限を与えることこれを解決していると捉えることができる。

struct Edge {
    int to, cap, rev;  // rev: 辺の番号
    Edge() {};
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8;  // 重みの最大値+1
vector<vector<Edge>> G;
vector<bool> used;

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
    int n, m; cin >> n >> m;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int from, to, cap; cin >> from >> to >> cap;
        // from->toのedgeにとっての逆辺は次の行で追加するto->fromのedgeなので、
        // そのedge番号はtoの最後のedge番号+1であり0-indexedなのでtoのedgeの本数と一致する
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, 0, G[from].size() - 1);  // 同時にcap=0で逆辺も加える
    }
    int s, t; cin >> s >> t;

    used = vector<bool>(n);
    int ans = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) ans += f;
        else break;
    }
    cout << ans << endl;
}
