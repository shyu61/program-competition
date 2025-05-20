#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 🔷初見でどうやったら解けるか
// 愚直にdfsするとO(n^2)になる。2点間距離の計算が複数回要求されるシーンではLCAが有効だが、全ペア走査するのにO(n^2)なので使えない
// そもそも全ペア生成が間に合わないので、数式変形や対称性利用、主客転倒を検討してみる。
// 数式は変形しようがない。対称性利用は異なるペア間で共通して含まれるエッジに注目できそう。
// 主客転倒とほぼ発想が同じなのでそれを踏まえて考えると、木dpで求められることがわかる。

// 🔷抑えるべき抽象論は？
// 主客転倒
// - 答えへの貢献度を考える方法
// - 二重シグマなどそもそも走査が間に合わないようなケースで頻出
// - 走査しつつ条件に一致するものを調べるのではなく、条件を走査しつつそれに合致する要素を見る考え方も主客転倒の一種

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dp(n, 1);
    auto dfs = [&](auto dfs, int v, int p = -1) -> int {
        for (auto u : g[v]) {
            if (u == p) continue;
            dp[v] += dfs(dfs, u, v);
        }
        return dp[v];
    };
    dfs(dfs, 0);

    ll ans = 0;
    rep(i, n) ans += ll(dp[i]) * (n - dp[i]);
    cout << ans << endl;
}
