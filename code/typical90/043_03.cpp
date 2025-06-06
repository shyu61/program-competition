#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// https://atcoder.jp/contests/abc132/tasks/abc132_e

// 🔷初見でどうやったら解けるか
// 最短路問題だが明らかにグラフを拡張する必要がある。グラフを拡張するときの重要な考え方は、
// グラフの頂点を「状態」と見ること。DAGはdpとみなせることからも自然な発想。
// 故に、頂点に何step目か？という情報を加えた状態を持たせれば良い。
// グラフ拡張する際は、実際にグラフを再構築せずとも遷移時の処理で対応可能なケースが多いことに留意すると、
// distを2次元にすれば十分であることがわかる。

// 🔷抑えるべき抽象論は？
// グラフ拡張
// - 重さのみの拡張で事足りるケース
//   - コスト0を導入するなど
// - グラフ自体を拡張するケース
//   - 頂点を「状態」と見る
//   - グラフの再構築は不要で、遷移時の処理で表現できるケースが多い

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
    }
    int s, t; cin >> s >> t, s--, t--;

    queue<P> que; que.emplace(s, 0);
    vector<vector<int>> dist(n, vector<int>(3, -1));
    dist[s][0] = 0;
    while (!que.empty()) {
        auto [v, d] = que.front(); que.pop();
        if (v == t && d % 3 == 0) {
            cout << d / 3 << endl;
            return 0;
        }
        for (auto u : g[v]) {
            int step = (d + 1) % 3;
            if (dist[u][step] != -1) continue;
            que.emplace(u, d + 1);
            dist[u][step] = d + 1;
        }
    }
    cout << -1 << endl;
}
