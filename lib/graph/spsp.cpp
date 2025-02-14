#include <bits/stdc++.h>
using namespace std;
const int INF = 1001001001;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// Single-Point-Shortest-Path

// ダイクストラ法
// 単一始点最短路を O(ElogV) で計算できる
// 負の重みは扱えない
// 既に最短路が確定した頂点を基準に、合計距離が小さい頂点を貪欲に選択し最短路を拡張していく戦略

// ベルマンフォード法
// 単一始点最短路を O(EV) で計算できる
// 負の閉路検出にも使える(whileがV-1回以上回る)
// 頂点iへの最短距離をd[i]とすると、iに隣接するノード集合sについて、
// d[i]=min{d[j]+cost(j,i)|j∋s} が成立する。
// 1回の緩和で少なくとも1頂点の最短路は確定するので、負の閉路がない場合は高々V-1回の緩和で求めることができる

int main() {
    int n, m;
    vector<vector<P>> g;

    vector<int> d(n, INF);
    auto dijkstra = [&](int s) -> void {
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

    auto bellman_ford = [&](int s) -> void {
        while (1) {
            bool update = false;
            rep(i, n) {
                for (auto [to, c] : g[i]) {
                    if (d[i] != INF && d[i] + c < d[to]) {
                        d[to] = d[i] + c;
                        update = true;
                    }
                }
            }
            if (!update) break;
        }
    };
}
