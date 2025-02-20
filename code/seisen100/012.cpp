#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using uint = unsigned int;

// ジャンル
// グラフ理論, 最大クリーク問題

// 方針
// 最大クリーク問題はNP困難なので、基本的には全探索する

int main() {
    int n, m; cin >> n >> m;
    vector<vector<bool>> g(n, vector<bool>(n));
    rep(i, m) {
        int x, y; cin >> x >> y, x--, y--;
        g[x][y] = g[y][x] = true;
    }

    int n2 = 1 << n, ans = 0;
    rep(s, n2) {
        bool ok = true;
        rep(i, n) rep(j, i) {            
            if ((s >> i & 1) && (s >> j & 1) && !g[i][j]) ok = false;
        }
        if (ok) ans = max(ans, popcount(uint(s)));
    }
    cout << ans << endl;
}
