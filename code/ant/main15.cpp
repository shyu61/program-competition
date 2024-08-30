// Traveling by Stagecoach(POJ 2686)
// http://poj.org/problem?id=2686
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1138&lang=ja
// ダイクストラの拡張による解法
#include <bits/stdc++.h>
using namespace std;

using P = tuple<double, int, int>;  // d, to, S

struct Comp {
    bool operator()(const P &a, P &b) { return get<0>(a) > get<0>(b); };
};

const double INF = 1e3;

int main() {
    int n, m, p, a, b;
    while (cin >> n >> m >> p >> a >> b) {
        if (n == 0) break;
        a--; b--;
        vector<double> t(n);
        vector<vector<pair<int, double>>> G(m);
        for (int i = 0; i < n; i++) cin >> t[i];
        for (int i = 0; i < p; i++) {
            int x, y, z; cin >> x >> y >> z;
            x--; y--;
            G[x].emplace_back(y, z);
            G[y].emplace_back(x, z);
        }

        // ダイクストラ
        priority_queue<P, vector<P>, Comp> pq;
        vector<vector<double>> dist(m, vector<double>(1 << n, INF));

        pq.emplace(0, a, 0);
        dist[a][0] = 0;
        while (!pq.empty()) {
            auto [w, v, S] = pq.top(); pq.pop();
            if (w > dist[v][S]) continue;

            // 距離の更新
            for (auto adj : G[v]) {
                auto [adj_u, adj_d] = adj;
                for (int i = 0; i < n; i++) {
                    if (S >> i & 1) continue;
                    int s = S | (1 << i);
                    if (dist[adj_u][s] > dist[v][S] + adj_d / t[i]) {
                        dist[adj_u][s] = dist[v][S] + adj_d / t[i];
                        pq.emplace(dist[adj_u][s], adj_u, s);
                    }
                }
            }
        }

        double ans = INF;
        for (int i = 0; i < (1 << n); i++) ans = min(ans, dist[b][i]);

        if (ans != INF) cout << fixed << setprecision(3) << ans << endl;
        else cout << "Impossible" << endl;
    }
}
