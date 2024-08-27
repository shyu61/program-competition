// ナップサック問題: p52
// 漸化式的解法: 添字1つバージョン
#include <bits/stdc++.h>
using namespace std;

// 1つ目の添字は直前の項にしか依存しないので、oldで直前の状態を持つことで添字を省略できる

int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    vector<int> dp(W + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> old(W + 1);
        swap(old, dp);
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) dp[j] = max(old[j - w[i]] + v[i], old[j]);
            else dp[j] = old[j];
        }
    }

    cout << dp[W] << endl;
}
