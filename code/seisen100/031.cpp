#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ポイント
// 周囲長は隣接異種マスの個数に等しい
// 内陸部を無視したい場合は塗ってしまえば良い
// → 普通にやったら考慮してしまう部分を無視したい場合、前処理で属性変更するのは有効な手段

const vector<int> dh = {-1,0,1,-1,0,1};
const vector<vector<int>> dw = {{0,-1,0,1,1,1},{-1,-1,-1,0,1,0}};

int main() {
    int w, h; cin >> w >> h;
    vector<vector<int>> mas(h, vector<int>(w));
    rep(i, h) rep(j, w) cin >> mas[i][j];

    vector<vector<bool>> seen(h, vector<bool>(w));
    auto bfs = [&](int si, int sj, int val) -> int {
        queue<P> que;
        que.emplace(si, sj);
        seen[si][sj] = true;

        bool surrounded = true;
        int res = 0;
        while (!que.empty()) {
            auto [i, j] = que.front(); que.pop();
            int len = 6;
            rep(r, 6) {
                int ni = i + dh[r], nj = j + dw[i % 2][r];
                if (ni < 0 || ni >= h || nj < 0 || nj >= w) {
                    surrounded = false;
                    continue;
                };
                if (mas[ni][nj] != val) continue;
                len--;
                if (seen[ni][nj]) continue;
                que.emplace(ni, nj);
                seen[ni][nj] = true;
            }
            res += len;
        }
        if (val) return res;
        return surrounded ? res : 0;
    };

    int ans = 0;
    rep(i, h) rep(j, w) {
        if (mas[i][j] == 1 && !seen[i][j]) ans += bfs(i, j, 1);
        if (mas[i][j] == 0 && !seen[i][j]) ans -= bfs(i, j, 0);
    }

    cout << ans << endl;
}

const vector<int> dh = {-1,0,1,-1,0,1};
const vector<vector<int>> dw = {{-1,-1,-1,0,1,0},{0,-1,0,1,1,1}};  // 番兵で囲むと偶奇は逆になる

int main() {
    int w, h; cin >> w >> h;
    vector<vector<int>> mas(h + 2, vector<int>(w + 2));
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) cin >> mas[i][j];
    }

    vector<vector<bool>> seen(h + 2, vector<bool>(w + 2));
    auto dfs = [&](auto dfs, int i, int j) -> void {
        seen[i][j] = true;
        rep(r, 6) {
            int ni = i + dh[r], nj = j + dw[i % 2][r];
            if (ni < 0 || ni >= h + 2 || nj < 0 || nj >= w + 2) continue;
            if (mas[ni][nj] != 0 || seen[ni][nj]) continue;
            dfs(dfs, ni, nj);
        }
    };
    dfs(dfs, 0, 0);

    // 到達不能な点は全て1にする
    rep(i, h + 2) rep(j, w + 2) {
        if (!seen[i][j]) mas[i][j] = 1;
    }

    int ans = 0;
    rep(i, h + 2) rep(j, w + 2) {
        if (mas[i][j] == 1) {
            rep(r, 6) {
                int ni = i + dh[r], nj = j + dw[i % 2][r];
                if (mas[ni][nj] == 0) ans++;
            }
        }
    }

    cout << ans << endl;
}
