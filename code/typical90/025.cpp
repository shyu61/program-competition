#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// 木の彩色(二部グラフ)

// ポイント
// 木は二部グラフ
// 二部グラフの特徴
// - 奇数長の閉路を含まない
// - 最大マッチングが多項式時間で解ける

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> color(n);
    auto dfs = [&](auto dfs, int v, int p, int c) -> void {
        color[v] = c;
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v, !c);
        }
    };

    dfs(dfs, 0, -1, 0);
    int cnt = 0;
    rep(i, n) if (color[i]) cnt++;
    int tc = cnt >= n / 2 ? 1 : 0;
    int num = n / 2;
    rep(i, n) {
        if (num == 0) break;
        if (color[i] == tc) {
            cout << i + 1 << ' ';
            num--;
        }
    }
    cout << endl;
}
