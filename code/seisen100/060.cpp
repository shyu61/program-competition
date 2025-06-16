#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const ll INF = 1000000000000000000LL;  // 1e18

// 🔷抑えるべき抽象論は？
// 最短路アルゴリズム
// - spsp
//   - ダイクストラ: O(nlogn), 負は扱えない
//   - ベルマンフォード: O(n^2)
// - apsp
//   - ワーシャルフロイド: O(n^3), 負も扱える

int main() {
    int n, m; cin >> n >> m;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    rep(i, n) dist[i][i] = 0;
    rep(i, m) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = w;
    }

    rep(k, n) rep(i, n) rep(j, n) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }

    rep(i, n) {
        if (dist[i][i] < 0) {
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    rep(i, n) {
        rep(j, n) {
            if (dist[i][j] == INF) cout << "INF";
            else cout << dist[i][j];
            cout << (j < n - 1 ? ' ' : '\n');
        }
    }
}
