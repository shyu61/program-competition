// ビットDP(Traveling by Stagecoach): p175
// ダイクストラによる解法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最短経路問題かつ重さは非負なのでダイクストラが使える形にできないか考えるのは自然
// -> チケット制約をグラフに落とし込めれば良い
// -> ノードにチケット情報を持たせて拡張すれば良さそう。そのチケット情報をもとに遷移できるノードを制限すれば良いので、遷移を問題なく記述できる
// ただのグラフの最短経路に帰着完了

// ポイント
// ノードに情報を追加することでグラフは拡張できる

using P = tuple<double, int, int>;

struct Edge {
    int to; int w;
    Edge(int to, double w) : to(to), w(w) {};
};

struct Comp {
    bool operator()(const P &a, const P &b) { return get<0>(a) > get<0>(b); };
};

const int INF = 3e3;
int n, m, p, a, b;
vector<double> t;
vector<vector<Edge>> G;

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

        // グラフのノードが持つ情報を、idと残りチケットの2つに拡張する
        priority_queue<P, vector<P>, Comp> pq;
        vector<vector<double>> d(m, vector<double>(1 << n, INF));
        pq.emplace(0, a, 0);
        d[a][0] = 0;
        while (!pq.empty()) {
            auto [w, v, S] = pq.top(); pq.pop();
            if (w > d[v][S]) continue;

            for (auto adj : G[v]) {
                for (int i = 0; i < n; i++) {
                    if (!(S >> i & 1)) {
                        int ns = S | (1 << i);
                        if (d[adj.to][ns] > d[v][S] + adj.w / t[i]) {
                            d[adj.to][ns] = d[v][S] + adj.w / t[i];
                            pq.emplace(d[adj.to][ns], adj.to, ns);
                        }
                    }
                }
            }
        }

        // グラフを拡張しているのでbはSの状態の数だけある
        double ans = INF;
        for (auto v : d[b]) ans = min(ans, v);

        if (ans == INF) cout << "Impossible" << endl;
        else cout << fixed << setprecision(3) << ans << endl;
    }
}
