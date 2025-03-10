#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// dfsに戻り値を持たせる場合、再帰的に掘ったその時点より先の集計結果を手に入れることができる

const vector<int> dx = {0,1,0,-1}, dy = {1,0,-1,0};

int main() {
    int w, h; cin >> w >> h;
    vector<vector<int>> mas(h, vector<int>(w));
    rep(i, h) rep(j, w) cin >> mas[i][j];

    // 全パス探索
    auto dfs = [&](auto dfs, int i, int j) -> int {
        int d = 1;
        mas[i][j] = 0;
        rep(r, 4) {
            int ni = i + dx[r], nj = j + dy[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] != 1) continue;
            d = max(d, dfs(dfs, ni, nj) + 1);
        }
        mas[i][j] = 1;
        return d;
    };

    int ans = 0;
    rep(i, h) rep(j, w) {
        if (mas[i][j]) {
            ans = max(ans, dfs(dfs, i, j));
        }
    }
    cout << ans << endl;
}
