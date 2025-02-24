#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ジャンル
// グラフ理論, 無向木, サブグラフ問題, 数え上げ

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int a, b; cin >> a >> b, a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> deg(n);
    rep(i, n) deg[i] = g[i].size();

    // 木dp
    vector<P> dp(n);
    auto dfs = [&](auto dfs, int v, int p) -> void {
        dp[v].first++;
        vector<P> res;
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v);
            res.push_back(dp[u]);
        }
        sort(res.begin(), res.end(), greater<>());

        if (deg[v] == 1 || deg[v] == 4) {
            rep(i, res.size()) {
                dp[v].first += res[i].first;
                dp[v].second = dp[v].second || res[i].second;
            }
            if (deg[v] == 4) dp[v].second = true;
        } else if (deg[v] < 4) {
            if (dp[v].second) dp[v].first += res[0].first;
            else {

            }
            dp[v] += res[0];
        } else if (deg[v] > 4) {
            rep(i, 4) dp[v] += res[i];
        }
    };

    dfs(dfs, 0, -1);
    int ans = 0;
    rep(i, n) ans = max(ans, dp[i]);
    if (ans == 0) ans = -1;
    cout << ans << endl;
}
