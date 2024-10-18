// 計算問題に対するDP(分割数): p66
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 分割数に関する漸化式: `P(n, k) = P(n, k-1) + P(n-k, k)`
// 有名問題なので覚えておくと良い

// ポイントは、場合の数や確率の問題でもDPは有力な選択肢だということ。
// 場合の数の数え上げの多くは樹形図構造であり、つまり再帰構造を持っているためDPと相性が良い

int main() {
    int n, k, M; cin >> n >> k >> M;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    dp[0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                dp[i][j] = dp[i][j - 1] + dp[i - j][j];
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    cout << dp[n][k] << endl;
}
