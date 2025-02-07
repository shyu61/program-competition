#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ジャンル
// 組合せ最適化問題, グラフ経路問題, 無向木

// 方針
// 直径を求めれば良い

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int a, b; cin >> a >> b; a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto dfs = [&](auto dfs, int v, int p) -> P {
        P res = {0, v};
        for (auto u : g[v]) {
            if (u == p) continue;
            auto [mx, mv] = dfs(dfs, u, v);
            res = max(res, {++mx, mv});
        }
        return res;
    };

    int v = dfs(dfs, 0, -1).second;
    cout << dfs(dfs, v, -1).first + 1 << endl;
}
