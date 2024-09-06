// 巡回セールスマン問題: p173
// 漸化式での解法
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

// 遷移の方向が逆方向になっている
// これは、そもそも漸化式が必要な情報が少ない方から埋めていくというのが鉄則であり、
// TSPの場合は逆から考えた方が選択肢となる経路が少なく探索範囲が限定されるため良いわけである

struct Edge {
    int to, d;
    Edge(int to, int d): to(to), d(d) {}
};

const int INF = 2e4;
int V, E;
vector<vector<Edge>> a;
vector<vector<int>> dp;

int main() {
    cin >> V >> E;
    a = vector<vector<Edge>>(V);
    for (int i = 0; i < E; i++) {
        int s, t, d; cin >> s >> t >> d;
        a[s].emplace_back(t, d);
    }

    dp = vector<vector<int>>(1 << V, vector<int>(V, INF));
    dp[(1 << V) - 1][0] = 0;
    // 始点に戻ってくる一つ前の点からスタート
    for (int S = (1 << V) - 2; S >= 0; S--) {
        for (int v = 0; v < V; v++) {
            // vは訪問済みのはず
            if (S >> v & 0) continue;
            for (auto adj : a[v]) {
                int u = adj.to;
                if (!(S >> u & 1)) {
                    dp[S][v] = min(dp[S][v], dp[S | (1 << u)][u] + adj.d);
                }
            }
        }
    }

    int ans = dp[0][0] != INF ? dp[0][0] : -1;
    cout << ans << endl;
}
