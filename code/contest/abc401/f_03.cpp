#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595

// 🔷初見でどうやったら解けるか
// 全ての頂点について計算する必要があるので木dpだけでは解けない。故に全方位dp
// 何をdpの値として持つかだが、最も素直に考えるなら、行って帰ってくるステップ数,行きっぱなしのステップ数のどちらか。
// しかしどちらもどの経路を最後にするかを判断できない。故にこの方針だと無理だとわかる。
// dpに持たせる値からではなく、どのような経路を最後にするのが最適かを考えると、最遠点であることが分かる。
// よってdpは直径と同様に最遠点距離を持たせれば良い

// 🔷抑えるべき抽象論は？
// 全方位dpの検討シーン
// - 木で全ての頂点についてある値を求める必要がある場合
//   - 直径は全ての頂点からの最遠2点距離のうち最大のものと考えることができる
//   - 全ての頂点を走査する必要はあっても、「最適なもののみ」で良いなら木dpで済むことも多い
// グラフ問題で全頂点/全エッジが絡むシーンでは、余事象を検討する

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dp(n);
    auto dfs = [&](auto dfs, int v, int p = -1) -> int {
        for (auto u : g[v]) {
            if (u == p) continue;
            dp[v] = max(dp[v], dfs(dfs, u, v) + 1);
        }
        return dp[v];
    };
    dfs(dfs, 0);

    vector<int> ans(n);
    auto dfs2 = [&](auto dfs2, int v, int p = -1, int val = 0) -> void {
        vector<P> ch;
        ch.emplace_back(0, -1);
        for (auto u : g[v]) {
            if (u == p) ch.emplace_back(val + 1, u);
            else ch.emplace_back(dp[u] + 1, u);
        }
        sort(ch.rbegin(), ch.rend());
        ans[v] = ch[0].first;
        for (auto u : g[v]) {
            if (u == p) continue;
            int nval = u == ch[0].second ? ch[1].first : ch[0].first;
            dfs2(dfs2, u, v, nval);
        }
    };
    dfs2(dfs2, 0);

    for (auto v : ans) cout << (n - 1) * 2 - v << '\n';
}
