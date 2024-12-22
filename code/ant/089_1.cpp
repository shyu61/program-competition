// ビットDP(Traveling by Stagecoach): p175
// bitDPによる解法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// TSPと全く同じ
// 最短経路問題だがチケット制約があるので、そのままだとダイクストラは使えない。
// グラフ問題のうちDAGはDPで解くことができるのでDPを考えると、チケット制約を集合で表現するとTSPと同じになる

// DPxグラフ
// DAGもしくは閉路のループが有限回で終わるケースじゃないとDPできない
// 今回はチケット制約があるので仮にループがあっても有限になるのでDPが使える

struct Edge {
    int to; int w;
    Edge(int to, double w) : to(to), w(w) {};
};

const int INF = 3e3;
int n, m, p, a, b;
vector<double> t;
vector<vector<Edge>> G;
vector<vector<double>> dp;

double f(int S, int v) {
    if (dp[S][v] >= 0) return dp[S][v];
    if (v == b) return dp[S][v] = 0;

    double res = INF;
    for (auto [u, w] : G[v]) {
        for (int i = 0; i < n; i++) {
            if (!(S >> i & 1)) {
                res = min(res, f(S | (1 << i), u) + w / t[i]);
            }
        }
    }
    return dp[S][v] = res;
}

int main() {
    while (cin >> n >> m >> p >> a >> b) {
        if (n == 0) break;
        a--; b--;
        t = vector<double>(n);
        G = vector<vector<Edge>>(m);
        for (int i = 0; i < n; i++) cin >> t[i];
        for (int i = 0; i < p; i++) {
            int x, y, w; cin >> x >> y >> w;
            x--; y--;
            G[x].emplace_back(y, w);
            G[y].emplace_back(x, w);
        }

        dp = vector<vector<double>>(1 << n, vector<double>(m, -1));
        f(0, a);
        if (dp[0][a] == INF) cout << "Impossible" << endl;
        else cout << fixed << setprecision(3) << dp[0][a] << endl;
    }
}
