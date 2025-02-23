#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using P = pair<int, int>;

// ジャンル
// グラフ理論, 回文, 最短経路問題

// 方針
// 始点から順に辿る戦略では回文の判定が終点までできない。単純パス以外も含むパスではこの戦略では求解できない。
// 故に戦略を変えて中央から双方向に回文となるパスを選択しつつ伸ばしていくことを考える。
// 回文となるようにパスを張った新たなグラフを定義し、そのグラフ上で最短経路問題を解く

int main() {
    int n; cin >> n;
    vector<string> g(n);
    rep(i, n) cin >> g[i];

    vector<vector<int>> dist(n, vector<int>(n, INF));
    queue<P> que;

    // 新しいグラフを定義する
    rep(i, n) {
        dist[i][i] = 0;
        que.emplace(i, i);
    }
    rep(i, n) rep(j, n) {
        if (i == j || g[i][j] == '-') continue;
        dist[i][j] = 1;
        que.emplace(i, j);
    }

    while (!que.empty()) {
        auto [s, t] = que.front(); que.pop();
        rep(i, n) rep(j, n) {
            if (g[i][s] == '-' || g[t][j] == '-') continue;
            if (g[i][s] != g[t][j]) continue;
            if (dist[i][j] != INF) continue;
            dist[i][j] = dist[s][t] + 2;
            que.emplace(i, j);
        }
    }

    rep(i, n) {
        rep(j, n) {
            if (dist[i][j] == INF) cout << -1 << ' ';
            else cout << dist[i][j] << ' ';
        }
        cout << endl;
    }
}
