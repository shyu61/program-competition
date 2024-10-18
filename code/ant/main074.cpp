// 計算問題に対するDP(重複組み合わせ): p67
#include <bits/stdc++.h>
using namespace std;

// 複雑な組合せに関する問題なのでDPを考える
// 組合せは樹形図で表せる -> 再帰構造を持つので、再帰の遷移を定式化できればDPが実装できる

// 組合せも基本はナップサックDPで考えるのは同じ
// dp[i][j] = sigma(k=0, min(j, a[i])) dp[i - 1][j - k];
// 

// 累積和は区間和を何度も求める必要がある時に検討すべき手法だが、dpの高速化でも使えることがある。
// dpで遷移式にsigmaが含まれる時は累積和が使えないか検討する。遷移は基本ループで書くことが多いため、内部ループでsigma計算をすることになるが、
// これはいわゆる"区間和を何度も求める"という操作をしているに他ならない。区間の形が累積和を使えるかは問題による。

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i <= n; i++) cin >> a[i];
    int M; cin >> M;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j - 1 - a[i] >= 0) {
                dp[i + 1][j] = (dp[i + 1][j - 1] + dp[i][j] - dp[i][j - 1 - a[i]] + M) % M;
            } else {
                dp[i + 1][j] = (dp[i + 1][j - 1] + dp[i][j]) % M;
            }
        }
    }

    cout << dp[n][m] << endl;
}

// 直接的に累積和を使う解法
int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i <= n; i++) cin >> a[i];
    int M; cin >> M;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 0; i < n; i++) {
        // 累積和を先に計算しておく
        vector<int> s(m + 1);
        s[0] = dp[i][0];
        for (int j = 1; j <= m; j++) s[j] = s[j - 1] + dp[i][j];

        for (int j = 1; j <= m; j++) {
            if (j - 1 - a[i] >= 0) {
                dp[i + 1][j] = s[j] - s[j - 1 - a[i]];
            } else {
                dp[i + 1][j] = s[j];
            }
        }
    }

    cout << dp[n][m] << endl;
}
