// 巡回セールスマン問題: p173
// メモ化再帰
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

// bitDPのように添字が整数ではないDPは、漸化式+ループよりメモ化再帰の方が書きやすいことが多い
// dpは前か後かどちらからdpテーブルが埋まっていくのかを意識する

struct Edge {
    int to, d;
    Edge(int to, int d): to(to), d(d) {}
};

const int INF = 2e4;
int V, E;
vector<vector<Edge>> a;
vector<vector<int>> dp;

int rec(int S, int v) {
    // メモ化
    if (dp[S][v] > 0) return dp[S][v];

    // 始点に戻ってきた
    if (S == (1 << V) - 1 && v == 0) return dp[S][v] = 0;

    int res = INF;
    for (auto adj : a[v]) {
        int u = adj.to;
        if (!(S >> u & 1)) {
            // 再帰実行により、S==Vの状態から順にdpテーブルが埋まっていく
            res = min(res, rec(S | (1 << u), u) + adj.d);
        }
    }
    return dp[S][v] = res;
}

int main() {
    cin >> V >> E;
    a = vector<vector<Edge>>(V);
    for (int i = 0; i < E; i++) {
        int s, t, d; cin >> s >> t >> d;
        a[s].emplace_back(t, d);
    }

    dp = vector<vector<int>>(1 << V, vector<int>(V, 0));

    int ans = rec(0, 0);
    ans = ans != INF ? ans : -1;
    int ans = dp[0][0] != INF ? dp[0][0] : -1;
    cout << ans << endl;
}
