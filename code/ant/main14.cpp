// Traveling by Stagecoach(POJ 2686)
// http://poj.org/problem?id=2686
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1138&lang=ja
// 漸化式での解法
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double d;
    Edge(int to, double d): to(to), d(d) {}
};

const double INF = 1e3;
int n, m, p, a, b;
vector<double> t;
vector<vector<Edge>> e;
vector<vector<double>> dp;

int main() {
    while (cin >> n >> m >> p >> a >> b) {
        if (n == 0) break;
        a--; b--;
        t = vector<double>(n);
        e = vector<vector<Edge>>(m);
        dp = vector<vector<double>>(1 << n, vector<double>(m, INF));
        for (int i = 0; i < n; i++) cin >> t[i];
        for (int i = 0; i < p; i++) {
            int x, y, z; cin >> x >> y >> z;
            x--; y--;
            e[x].emplace_back(y, z);
            e[y].emplace_back(x, z);
        }

        for (int i = 0; i < (1 << n); i++) dp[i][b] = 0;
        // TSPと同じ考え方で、dpテーブルは後ろ(S==(1<<n)-1)から埋めていく
        for (int S = (1 << n) - 1; S >= 0; S--) {
            // 現在の位置
            for (int v = 0; v < m; v++) {
                // どのチケットを使うか
                for (int i = 0; i < n; i++) {
                    // すでに使用済みの場合はskip
                    if (S >> i & 1) continue;
                    for (auto adj : e[v]) {
                        // i番目のチケットを使って、点uへ遷移する(正確には逆方向)
                        dp[S][v] = min(dp[S][v], dp[S | (1 << i)][adj.to] + (adj.d / t[i]));
                    }
                }
            }
        }

        if (dp[0][a] != INF) cout << fixed << setprecision(3) << dp[0][a] << endl;
        else cout << "Impossible" << endl;
    }
}
