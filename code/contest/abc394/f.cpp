#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// グラフ理論, 無向木, サブグラフ問題, 木dp

// 方針
// 特定の条件を満たす部分木を探索する問題なので、木dpを考えつつ部分木を評価していく

// ポイント
// 木dpで重要なのは2つ
// - 何を伝播させるか
// - いつansを更新するか
// 部分木とは、今見ているノードが根になるということ。つまり根としての条件を適用する必要がある
// 場合分けは丁寧に

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int a, b; cin >> a >> b, a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int ans = -1;
    auto dfs = [&](auto dfs, int v, int p) -> int {
        vector<int> d;
        for (auto u : g[v]) {
            if (u == p) continue;
            d.push_back(dfs(dfs, u, v));
        }
        sort(d.begin(), d.end(), greater());

        int res = 1;
        if (d.size() >= 3) {
            rep(i, 3) res += d[i];
            // vを根とする部分木が解となるケース
            if (d.size() >= 4) ans = max(ans, res + d[3]);
        } else if (d.size() > 0) {
            ans = max(ans, res + d[0]);
        }
        return res;
    };

    dfs(dfs, 0, -1);
    if (ans <= 4) ans = -1;
    cout << ans << endl;
}
