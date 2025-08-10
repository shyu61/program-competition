#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 「操作によって0の個数の偶奇が不変」なので、部分文字列における0の個数が偶数のものを数え上げる問題になる。
// 言い換えると区間内の0の個数の偶奇の数え上げになる。区間和になるので累積和を前提に考えてみる。
// 累積和を使っても全ペア走査自体はO(n^2)かかるが、"偶奇"だけ分かれば良いことに注目すると、区間[l,r)でのs[l]とs[r]の偶奇が等しいペアを数えれば良いことに気づく。
// これはx(x-1)/2で数えられる。

// 🔷抑えるべき抽象論は？
// パリティ問題は法則性を見抜くひらめきが要求されることが多い
// - 実験
// - 不変量や自由度の低い部分に注目
// - 状態の単純化
//   - 文字列や数値そのものではなく、特定文字の個数や位置, 桁や因数などより単純な値に注目してみる

// 累積和を使った解法
int main() {
    int n; string t; cin >> n >> t;
    vector<int> a(n);
    rep(i, n) a[i] = t[i] == '0';
    vector<int> s(n + 1);
    rep(i, n) s[i + 1] = (s[i] + a[i]) % 2;

    vector<int> cnt(2);
    rep(i, n + 1) cnt[s[i]]++;

    ll ans = 0;
    rep(i, 2) ans += ll(cnt[i]) * (cnt[i] - 1) / 2;
    cout << ans << endl;
}

// dpを使った解法
int main() {
    int n; string t; cin >> n >> t;
    vector<int> a(n);

    vector<vector<int>> dp(n + 1, vector<int>(2));
    rep(i, n) {
        if (t[i] == '0') {
            dp[i + 1][0] = dp[i][1];
            dp[i + 1][1] = dp[i][0] + 1;
        } else {
            dp[i + 1][0] = dp[i][0] + 1;
            dp[i + 1][1] = dp[i][1];
        }
    }
    ll ans = 0;
    rep(i, n + 1) ans += dp[i][0];
    cout << ans << endl;
}
