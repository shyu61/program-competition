#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 逐次問題で遷移条件が累積的なのでdpを考える。
// 素直に立式すると dp[i番目まで見て][テンションj]:=可否 だが、これだとクエリに高速に答えられない
// 初期値が与えられた時の最終スコアが欲しいのでそれをdpに組み込むように設計し直すと、dp[テンションj]:=最終スコア で、i番目からスタートを加えて
// dp[i番目からスタート][テンションj]:=最終スコア を得る。形式はゲーム問題のdpと類似していて、後ろから計算していく必要があることがわかる。

int main() {
    int n; cin >> n;
    vector<int> p(n), a(n), b(n);
    rep(i, n) cin >> p[i] >> a[i] >> b[i];

    // dp[i番目から始めた時][テンションがj] := 最終スコア
    vector<vector<int>> dp(n + 1, vector<int>(1001));
    rep(i, 1001) dp[n][i] = i;
    for (int i = n - 1; i >= 0; i--) {
        rep(j, 1001) {
            if (j <= p[i]) dp[i][j] = dp[i + 1][j + a[i]];
            else dp[i][j] = dp[i + 1][max(0, j - b[i])];
        }
    }

    vector<int> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + b[i];

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        int ans = 0;
        if (x > 1000) {
            auto i = lower_bound(s.begin(), s.end(), x - 1000) - s.begin();
            if (i > n) ans = x - s[n];
            else ans = dp[i][x - s[i]];
        } else {
            ans = dp[0][x];
        }
        cout << ans << "\n";
    }
}
