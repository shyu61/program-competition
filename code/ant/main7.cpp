// ナップサック問題: p52
// 漸化式的解法
#include <bits/stdc++.h>
using namespace std;

// 貰うdpのコツ: 添字0は何も選ばないと考え、要素は添字1から格納しておく
// 配列は常にn+1個用意しておく

int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    vector<vector<int>> dp(n + 1, vector<int>(W + 1));
    for (int i = 0; i <= W; i++) dp[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) {
                dp[i][j] = max(dp[i - 1][j - w[i]] + v[i], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    cout << dp[n][W] << endl;
}
