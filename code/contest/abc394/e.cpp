#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using P = pair<int, int>;

// ジャンル
// グラフ理論, 回文, 最短経路問題, 多始点bfs

// 方針
// 始点から順に辿る戦略では回文の判定が終点までできない。単純パス以外も許容されるのでパスの全列挙が不可能であるためこの戦略では求解できない。
// 故に戦略を変えて中央から双方向に回文となるパスを選択しつつ伸ばしていくことを考える
// 最短距離問題である全体を考えると、多始点bfsという考えが出てくる。
// 通常のbfsと違って遷移するときに始点と終点の両方の情報が必要なので、頂点をedgeとみなすグラフを考える必要性に気づく
// bfsの遷移は重さが一定じゃないと扱えないことに注意すると、0,1のedgeを初期状態としてあらかじめqueueに入れた上でbfsすれば良いことがわかる

// ポイント
// 重み付きbfs
// - bfsは重みが一定の遷移である必要がある。それ以外の重みは多始点bfsの初期状態として予め入れておけるなら扱える
// 特殊なグラフを扱う場合は、bfsやdfsなどグラフの遷移時に必要な情報は何か？を考えてグラフを定義すると良い。
// - edgeを頂点とみなすようなグラフはよくある

int main() {
    int n; cin >> n;
    vector<string> g(n);
    rep(i, n) cin >> g[i];

    vector<vector<int>> dist(n, vector<int>(n, INF));
    queue<P> que;

    // edgeを頂点とみなす
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
