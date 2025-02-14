#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using P = pair<int, int>;

// ジャンル
// グラフ理論, 最短経路問題, 経由地問題, 重み付き無向グラフ

// 方針
// 1,Nそれぞれからダイクストラで任意の頂点への最短路を計算しておけば良い

int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    auto dijkstra = [&](int s, vector<int>& d) -> void {
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.emplace(0, s);
        d[s] = 0;
        while (!pq.empty()) {
            auto [c, v] = pq.top(); pq.pop();
            if (c > d[v]) continue;
            for (auto [to, nc] : g[v]) {
                int nd = d[v] + nc;
                if (nd < d[to]) pq.emplace(d[to] = nd, to);
            }
        }
    };

    vector<int> d1(n, INF), d2(n, INF);
    dijkstra(0, d1);
    dijkstra(n - 1, d2);

    rep(i, n) cout << d1[i] + d2[i] << '\n';
}
