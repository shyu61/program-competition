#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const int INF = 1001001001;

// warshall_floyd: O(n^3)
// 原理: 始点終点以外の全ての点を経由する経路とコスト比較して更新していく。
// 始点と終点が一致する経路で負になれば負の閉路がある
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, INF));
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
            if (dist[i][j] == INF) cout << "INF" << ' ';
            else cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
}
