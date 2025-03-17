#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// サブグラフ問題,パス探索問題 → 木dp

// 障壁
// 直線グラフなら絶対Yesなので、分岐がある節での条件分岐が重要だと気づけるか
// 余りなく作れることが必要なので剰余が関連すると気づけるか
// 複雑な問題設定を正確に理解できるか

// ポイント
// パス = degが2以下

int main() {
    int n, k; cin >> n >> k;
    vector<vector<int>> g(n * k);
    rep(i, n * k - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool ok = true;
    auto dfs = [&](auto dfs, int v, int p) -> int {
        int res = 1, deg = 0;
        for (auto u : g[v]) {
            if (u == p) continue;
            int s = dfs(dfs, u, v);
            if (s > 0) deg++;
            res += s;
        }
        if (deg > 2) ok = false;
        if (deg == 2) {
            if (res % k != 0) ok = false;
        }
        return res %= k;
    };
    dfs(dfs, 0, -1);

    if (ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}
