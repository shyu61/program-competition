#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=jp

// 全方位dp
// 1. 適当な点を根として木dpを行う
// 2. 1.と同じ点からdfsしつつ、木dpの結果と親からの伝搬を使って各頂点での値を求める
//   - dfs方向の部分木はdpの結果そのままなので、親側から伝播してくる値と比較して最適値を求める
//   - 子へ伝搬させる際、その最適値を取る部分木がdfsの行き先と一致したらダメなのでそこだけチェックする

// 全方位dpによる解法
int main() {
    int n; cin >> n;
    vector<vector<P>> g(n);
    rep(i, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int> dp(n);
    auto dfs = [&](auto dfs, int v, int p = -1) -> int {
        for (auto [u, w] : g[v]) {
            if (u == p) continue;
            dp[v] = max(dp[v], dfs(dfs, u, v) + w);
        }
        return dp[v];
    };
    dfs(dfs, 0);

    // 親からの伝播値をvalとして渡す
    auto dfs2 = [&](auto dfs2, int v, int p = -1, int val = 0) -> int {
        vector<P> ch;  // (値,行き先)
        ch.emplace_back(0, -1);
        for (auto [u, w] : g[v]) {
            if (u == p) ch.emplace_back(val + w, u);
            else ch.emplace_back(dp[u] + w, u);
        }
        sort(ch.rbegin(), ch.rend());
        int res = ch[0].first + ch[1].first;
        for (auto [u, w] : g[v]) {
            if (u == p) continue;
            // 最大値が次のdfsの行き先と一致する場合は2番目を使う
            int nval = u == ch[0].second ? ch[1].first : ch[0].first;
            res = max(res, dfs2(dfs2, u, v, nval));
        }
        return res;
    };

    cout << dfs2(dfs2, 0) << endl;
}

// dfs2回による解法
int main() {
    int n; cin >> n;
    vector<vector<P>> g(n);
    rep(i, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    auto dfs = [&](auto dfs, int v, int p = -1, int dep = 0) -> P {
        P res(dep, v);
        for (auto [u, w] : g[v]) {
            if (u == p) continue;
            res = max(res, dfs(dfs, u, v, dep + w));
        }
        return res;
    };
    int a = dfs(dfs, 0).second;
    auto [d, b] = dfs(dfs, a);

    cout << d << endl;
}
