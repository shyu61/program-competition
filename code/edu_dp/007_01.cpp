#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 木の定義
// - 無向木: 連結で閉路がない
//   - n頂点なら辺はn-1本
//   - 任意の2点間のパスが一意に決まる
// - 有向木: 閉路が存在せず、1つの根(入次数=0)とその他頂点(入次数=1)から成る
//   - n頂点なら辺はn-1本
//   - 根と任意の1点間のパスが一意に決まる
// - 直径に関する性質は無向木のみに当てはまる

// 🔷抑えるべき抽象論は？
// dagでdpしたい時はトポロジカルソートとセットで考える
// 遷移順が不明確な場合はメモ化再帰が有効
// 木dpを検討すべきシーン
// - 各頂点でなんらかの集計値を計算したい時

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }

    vector<int> dp(n, -1);
    auto rec = [&](auto rec, int v) -> int {
        if (dp[v] != -1) return dp[v];
        int res = 0;
        for (auto u : g[v]) {
            res = max(res, rec(rec, u) + 1);
        }
        return dp[v] = res;
    };

    int ans = 0;
    rep(i, n) ans = max(ans, rec(rec, i));
    cout << ans << endl;
}
