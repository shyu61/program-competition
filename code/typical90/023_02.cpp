#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint1000000007;

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    auto is_ng = [&](int s, int i, int j) -> bool {
        if (i - 1 >= 0 && j - 1 >= 0 && s & 1) return true;
        if (i - 1 >= 0 && s >> 1 & 1) return true;
        if (i - 1 >= 0 && j + 1 < w && s >> 2 & 1) return true;
        if (j - 1 >= 0 && s >> w & 1) return true;
        return false;
    };

    int w2 = 1 << (w + 1);
    vector<vector<mint>> dp(h * w + 1, vector<mint>(w2));
    dp[0][0] = 1;
    rep(is, h * w) {
        int i = is / w, j = is % w;
        rep(s, w2) {
            int nx = s >> 1;
            if (mas[i][j] == '#' || is_ng(s, i, j)) {
                dp[is + 1][nx] += dp[is][s];
            } else {
                // 置く場合
                dp[is + 1][nx | 1 << w] += dp[is][s];
                // 置かない場合
                dp[is + 1][nx] += dp[is][s];
            }
        }
    }

    mint ans = 0;
    rep(i, w2) ans += dp[h * w][i];
    cout << ans.val() << endl;
}

// 配列を使い回す解法
// 計算量は上記と同じ
int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    auto is_ng = [&](int s, int i, int j) -> bool {
        if (i - 1 >= 0 && j - 1 >= 0 && s & 1) return true;
        if (i - 1 >= 0 && s >> 1 & 1) return true;
        if (i - 1 >= 0 && j + 1 < w && s >> 2 & 1) return true;
        if (j - 1 >= 0 && s >> w & 1) return true;
        return false;
    };

    int w2 = 1 << (w + 1);
    vector<mint> dp(w2);
    dp[0] = 1;
    rep(i, h) {
        rep(j, w) {
            vector<mint> old(w2);
            swap(dp, old);
            rep(s, w2) {
                int nx = s >> 1;
                if (mas[i][j] == '#' || is_ng(s, i, j)) {
                    dp[nx] += old[s];
                } else {
                    // 置く場合
                    dp[nx | 1 << w] += old[s];
                    // 置かない場合
                    dp[nx] += old[s];
                }
            }
        }
    }

    mint ans = 0;
    rep(i, w2) ans += dp[i];
    cout << ans.val() << endl;
}
