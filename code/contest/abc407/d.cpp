#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// xorは効率的に計算しにくいのでまずは全探索を考える。
// 素直に考えるとO(3^HW)だが、遷移する3通りのうち2つは2つ減らすのでこれよりは小さいことが予想できる
// 再帰型全探索の計算量見積もりは漸化式が有効なことが多いので考えてみると、f(n)=f(n-1)+2f(n-2)。
// 3項間漸化式は特性方程式を考えればよく、解けばO(2^HW)になる。ゆえに十分高速
// - https://manabitimes.jp/math/697

// 🔷抑えるべき抽象論は？
// 計算量見積もりには、漸化式が使えることがある。
// - 再帰処理の場合は、特製方程式を使って漸化式を解く。天下り的にやってもいい。

int main() {
    int h, w; cin >> h >> w;
    vector<vector<ll>> mas(h, vector<ll>(w));
    rep(i, h) rep(j, w) cin >> mas[i][j];

    auto f = [&](const vector<vector<bool>>& msk) -> ll {
        ll res = 0;
        rep(i, h) rep(j, w) {
            if (!msk[i][j]) res ^= mas[i][j];
        }
        return res;
    };

    ll ans = 0;
    vector<vector<bool>> mask(h, vector<bool>(w));
    auto dfs = [&](auto dfs, int i, int j) -> void {
        i += j / w, j %= w;
        if (i == h) {
            ans = max(ans, f(mask));
            return;
        }

        if (mask[i][j]) dfs(dfs, i, j + 1);
        else {
            // 横に置く
            if (j < w - 1 && !mask[i][j + 1]) {
                mask[i][j] = mask[i][j + 1] = true;
                dfs(dfs, i, j + 1);
                mask[i][j] = mask[i][j + 1] = false;
            }
            // 縦に置く
            if (i < h - 1) {
                mask[i][j] = mask[i + 1][j] = true;
                dfs(dfs, i, j + 1);
                mask[i][j] = mask[i + 1][j] = false;
            }
            // 置かない
            dfs(dfs, i, j + 1);
        }
    };
    dfs(dfs, 0, 0);

    cout << ans << endl;
}
