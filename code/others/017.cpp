// TSP
// htttps://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

// bitdp
// - 集合sは最終状態でフルになる(全bitが立つ)ように定義すると良い
//   - 遷移の方向に注意する。必ずしも集合が増える方向とは限らない
// - 全集合を走査することが多いが、到達しない状態が多いsparseな遷移なら再帰なら計算量を削減できる
//   - 再帰はループとは実装は逆方向だが、実際には遷移の方向は同じ

// tsp
// 最終状態: 全ての頂点を訪問して始点に戻ってくる -> 集合sは訪問済み頂点とするのが良い
// 遷移の方向: 残りのsを訪問するコストなので、残りがない=集合がフルの状態からの逆方向が遷移の向き
// dp[s][i]:=現在頂点iから残り集合sを訪問する最小コスト
//   - dp[s][v]=min{dp[sUu][u]+cost(v,u) | u∉s}
//   - 頂点vから残りsを訪問する最小コストは、頂点vから遷移可能な頂点uでの最小コストにcost(u,v)を加えたもの

struct Edge { int to, cost; };

int main() {
    int n, m; cin >> n >> m;
    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int s, t, d; cin >> s >> t >> d;
        g[s].push_back(Edge{t, d});
    }

    int n2 = 1 << n;
    const int INF = 1000 * m + 1;
    vector<vector<int>> dp(n2, vector<int>(n, INF));
    dp[n2 - 1][0] = 0;
    for (int s = n2 - 1; s >= 0; s--) {
        for (int v = 0; v < n; v++) {
            for (auto [u, c] : g[v]) {
                if (s >> u & 1) continue;
                dp[s][v] = min(dp[s][v], dp[s | 1 << u][u] + c);
            }
        }
    }
    cout << (dp[0][0] == INF ? -1 : dp[0][0]) << endl;
}
