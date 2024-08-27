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

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) dp[i][j] = max(dp[i - 1][j - w[i]] + v[i], dp[i - 1][j]);
            else dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[n][W] << endl;
}

// 添字省略パターン
// 1つ目の添字は直前の項にしか依存しないので、配列を再利用することで添字を省略できる
int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    vector<int> dp(W + 1, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> old(W + 1);
        swap(old, dp);
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) dp[j] = max(old[j - w[i]] + v[i], old[j]);
            else dp[j] = old[j];
        }
        // for (int j = W; j >= 0; j--) {
        //     if (j - w[i] < 0) continue;
        //     // 左辺のdpは一つ前のループでの状態
        //     dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
        // }
    }

    cout << dp[W] << endl;
}
