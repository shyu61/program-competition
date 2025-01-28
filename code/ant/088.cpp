// ビットDP(巡回セールスマン問題): p173
#include <bits/stdc++.h>
using namespace std;

// ポイント
// bitDPはメモ化再帰が考えやすい

struct Edge { int to, cost; };

int main() {
    int n, m; cin >> n >> m;
    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int s, t, d; cin >> s >> t >> d;
        g[s].push_back(Edge{t, d});
    }

    // dp[s][i]:=訪問済み頂点集合sかつ、現在頂点iの状態から残りの全頂点を訪問する最小コスト
    int n2 = 1 << n;
    const int INF = 1000 * m + 1;
    vector<vector<int>> dp(n2, vector<int>(n, -1));

    auto rec = [&](auto rec, int s, int v) -> int {
        if (dp[s][v] >= 0) return dp[s][v];
        if (s == n2 - 1 && v == 0) return dp[s][v] = 0;  // 終了条件

        int res = INF;
        for (auto [u, c] : g[v]) {
            if (s >> u & 1) continue;
            res = min(res, rec(rec, s | 1 << u, u) + c);
        }
        return dp[s][v] = res;
    };

    rec(rec, 0, 0);
    cout << (dp[0][0] == INF ? -1 : dp[0][0]) << endl;
}
