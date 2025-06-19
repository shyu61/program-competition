#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int M = 1024;

// 🔷初見でどうやったら解けるか
// xorなのでまずは全探索を考える。全パス探索はO(V!)なので無理。xorを高速に扱う方法としては、桁独立であることを利用する方法があるが、今回はそれも使えなさそう。
// 故に高速に全探索する方法を考える。
// 欲しいのはパスの経路ではなくxorなので、取りうるxorを全探索することを考える。M<=1024より、頂点倍化の拡張グラフで解ける。

// 🔷抑えるべき抽象論は？
// M以下の数同士のxorはM以下
// 全探索問題は"何を全探索するか?"を考える
// - 本問題は、遷移の全探索ではなく、取りうる値の全探索と考える
// - あり得る操作や手順だけでなく、値そのものの全探索も常に検討する
// グラフの頂点倍化テクは最短路問題だけではない
// - 全探索や到達可能性などの単純な経路探索にも適用できる。共通してるのは頂点を「状態」と見ること

int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
    }

    vector<vector<bool>> seen(n, vector<bool>(M));
    auto dfs = [&](auto dfs, int v, int xo) -> void {
        seen[v][xo] = true;
        for (auto [u, w] : g[v]) {
            int nxo = xo ^ w;
            if (!seen[u][nxo]) dfs(dfs, u, nxo);
        }
    };
    dfs(dfs, 0, 0);

    rep(i, M) {
        if (seen[n - 1][i]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
