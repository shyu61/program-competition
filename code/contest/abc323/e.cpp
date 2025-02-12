#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint998244353;

// ジャンル
// 確率問題, 確率dp, 逐次問題

// 方針
// 逐次操作を伴う確率問題で、状態によって条件を満たす確率が異なるためdpで考える
// 条件を満たすには、時刻tが t>0 && t+T[i]<0 を満たせば良い
// つまり時刻tに至る確率が求まれば良いので、dp[t秒時点]:=曲がちょうど開始する確率として
// dp[t] = Σ(dp[t-T[i]]) * 1/n とすればよい

// 逆方向に考えて、dp[t]:=残りt行から始めて条件を満たす確率 とし、
// dp[t] = Σ(dp[t-T[i]]) * 1/n として、t<0の時にi=0なら1,その他なら0を返却する再帰を書いても良い

int main() {
    int n, x; cin >> n >> x;
    vector<int> T(n);
    rep(i, n) cin >> T[i];

    // mem[t]:=残りt秒からスタートした時に1曲目で終わる確率
    vector<mint> mem(x + 1, -1);
    mint p = mint(1) / n;
    auto rec = [&](auto rec, int t) -> mint {
        if (t < 0) return 0;
        if (mem[t] != -1) return mem[t];
        mint res = 0;
        rep(i, n) {
            if (i == 0 && t - T[i] < 0) res += 1;
            else res += rec(rec, t - T[i]);
        }
        return mem[t] = res * p;
    };

    mint ans = rec(rec, x);
    cout << ans.val() << endl;
}

int main() {
    int n, x; cin >> n >> x;
    vector<int> T(n);
    rep(i, n) cin >> T[i];

    // dp[i秒時点]:=新しい曲が再生され始める確率
    vector<mint> dp(x + 1);
    dp[0] = 1;
    mint p = mint(1) / n;
    for (int i = 1; i < x + 1; i++) {
        mint res = 0;
        rep(j, n) {
            if (i - T[j] >= 0) res += dp[i - T[j]];
        }
        dp[i] = res * p;
    }

    mint ans = 0;
    rep(i, x + 1) {
        if (i + T[0] > x) ans += dp[i] * p;
    }
    cout << ans.val() << endl;
}
