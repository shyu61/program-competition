#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, int>;
using TP = tuple<ll, int, bool>;
const ll INF = 1e18;

// 想定解
// 拡張ダイクストラ

// トラップ
// なし

// 方針
// 重みが動的という点から、拡張ダイクストラを思いつける必要がある
// 拡張ダイクストラは、nodeを状態,edgeを遷移と捉える方法
// <= 各頂点での状態によって重みが変化する問題に対応できる

// 遷移時に拡張する方法
int main() {
    int n, m, x; cin >> n >> m >> x;
    vector<vector<int>> g(n), rg(n);
    rep(i, m) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    vector<vector<ll>> d(n, vector<ll>(2, INF));
    auto dijkstra = [&](int s) -> void {
        priority_queue<TP, vector<TP>, greater<TP>> pq;
        pq.emplace(0, s, 0);
        d[s][0] = 0;
        d[s][1] = x;
        while (!pq.empty()) {
            auto [c, v, flip] = pq.top(); pq.pop();
            if (c > d[v][flip]) continue;
            rep(r, 2) {
                for (auto to : g[v]) {
                    ll nd = d[v][r] + 1;
                    if (r == 1) nd += x;
                    if (nd < d[to][0]) pq.emplace(d[to][0] = nd, to, 0);
                }
                for (auto to : rg[v]) {
                    ll nd = d[v][r] + 1;
                    if (r == 0) nd += x;
                    if (nd < d[to][1]) pq.emplace(d[to][1] = nd, to, 1);
                }
            }
        }
    };
    dijkstra(0);
    cout << min(d[n - 1][0], d[n - 1][1]) << endl;
}

// 実際にグラフを拡張する方法
int main() {
    int n, m, x; cin >> n >> m >> x;
    int n2 = n * 2;
    vector<vector<P>> g(n2);
    rep(i, m) {
        int u, v; cin >> u >> v, u--, v--;
        g[u * 2].emplace_back(1, v * 2);
        g[v * 2 + 1].emplace_back(1, u * 2 + 1);
    }
    rep(i, n) {
        g[i * 2].emplace_back(x, i * 2 + 1);
        g[i * 2 + 1].emplace_back(x, i * 2);
    }

    vector<ll> d(n2, INF);
    auto dijkstra = [&](int s) -> void {
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.emplace(0, s);
        d[s] = 0;
        while (!pq.empty()) {
            auto [c, v] = pq.top(); pq.pop();
            if (c > d[v]) continue;
            for (auto [nc, to] : g[v]) {
                ll nd = d[v] + nc;
                if (nd < d[to]) pq.emplace(d[to] = nd, to);
            }
        }
    };
    dijkstra(0);
    cout << min(d[n2 - 1], d[n2 - 2]) << endl;
}
