// Traveling by Stagecoach(POJ 2686)
// http://poj.org/problem?id=2686
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1138&lang=ja
// メモ化再帰での解法
#include <bits/stdc++.h>
using namespace std;

// 有向グラフの2点間最短距離問題なので、ダイクストラかDPを検討する
// DAGであることがわかる(前後関係を規定できる)のでDPで解くことを考える
// 状態遷移は、明らかに残り使えるチケットに依存するのでまずbit列で使ったチケットを持つことを考える
// その上で点v→点uへの遷移を考えるとき、点vから出ている全てのエッジに対して残り全てのチケットを使う組み合わせを考えて、距離が最小のもの選ぶ
// bitDPはメモ化再帰で考えた方が実装しやすい。
// 本問題ではdpテーブルは後ろから埋めていくことになる。理由はTSPと同じで、残りの距離の最小値を考えるので、bに辿り着いた状態から逆算していく方が考えやすいため

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

double rec(int S, int v) {
    // メモ化
    if (dp[S][v] > 0) return dp[S][v];

    // bに辿り着いたら終了
    if (v == b) return 0;

    double res = INF;
    // チケットを使い切ったら終了
    if (S == (1 << n) - 1) return res;
    for (int i = 0; i < n; i++) {
        // すでに使用済みならskip
        if (S >> i & 1) continue;
        for (auto adj : e[v]) {
            res = min(res, rec(S | (1 << i), adj.to) + (adj.d / t[i]));
        }
    }

    return dp[S][v] = res;
}

int main() {
    while (cin >> n >> m >> p >> a >> b) {
        if (n == 0) break;
        a--; b--;
        t = vector<double>(n);
        e = vector<vector<Edge>>(m);
        dp = vector<vector<double>>(1 << n, vector<double>(m, 0));
        for (int i = 0; i < n; i++) cin >> t[i];
        for (int i = 0; i < p; i++) {
            int x, y, z; cin >> x >> y >> z;
            x--; y--;
            e[x].emplace_back(y, z);
            e[y].emplace_back(x, z);
        }

        double ans = rec(0, a);
        if (ans != INF) cout << fixed << setprecision(3) << ans << endl;
        else cout << "Impossible" << endl;
    }
}
