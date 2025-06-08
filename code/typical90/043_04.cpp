#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
using TP = tuple<int, int, int>;
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// 制約がある重み付き最短路問題なので、グラフを拡張して制約をグラフとして取り込みつつ、ダイクストラで解くことを考える。
// グラフ拡張は、ノードを頂点ではなく状態と考えるのが定石。制約はt=0,2の頂点からの経過時間なので、経過時間情報を状態として持てば良い。
// 寒い/暑いは±の時間で表せば1つの次元で表現できる。2次元使っても良い。

// 🔷抑えるべき抽象論は？
// 本質は最短路問題だが、グラフ拡張が必要なケースでは「頂点を状態と見る」

int main() {
    int n, m, x; cin >> n >> m >> x;
    vector<int> t(n);
    rep(i, n) cin >> t[i], t[i]--;

    vector<vector<P>> g(n);
    rep(i, m) {
        int u, v, cost; cin >> u >> v >> cost;
        u--, v--;
        if (t[u] * t[v] == -1 && cost < x) continue;
        g[u].emplace_back(v, cost);
        g[v].emplace_back(u, cost);
    }

    // dijkstra
    priority_queue<TP, vector<TP>, greater<TP>> pq;
    pq.emplace(0, 0, 0);
    vector<vector<int>> dist(n, vector<int>(401, INF));
    dist[0][0] = 0;
    while (!pq.empty()) {
        auto [d, v, temp] = pq.top(); pq.pop();
        if (d > dist[v][temp]) continue;
        for (auto [u, c] : g[v]) {
            int ntemp = temp;
            if (temp < x) ntemp = min(x, temp + c);
            if (temp > x) ntemp = max(x, temp - c);

            if (t[u] < 0) {
                if (ntemp > x) continue;
                ntemp = 0;
            }
            if (t[u] > 0) {
                if (ntemp < x) continue;
                ntemp = x * 2;
            }

            int nd = dist[v][temp] + c;
            if (nd < dist[u][ntemp]) pq.emplace(dist[u][ntemp] = nd, u, ntemp);
        }
    }

    int ans = INF;
    rep(i, 401) ans = min(ans, dist[n - 1][i]);
    cout << ans << endl;
}
