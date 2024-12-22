// 個数制限なしナップサック問題: p58
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] < 0) dp[i][j] = dp[i - 1][j];
            // dp[i]からの遷移があるということは、すでにi番目の要素を使っている可能性があるdpからi番目を最後に使うことを考えているので、復元抽出を行っていることになる
            // 逆に、dp[i - 1]からの遷移しかない場合は、dp[i]へは高々1回までしかi番目の要素を使うことができないということになり、非復元抽出になる
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i]] + v[i]);
        }
    }

    cout << dp[n][W] << endl;
}

// 添字省略パターン
// 復元抽出はiによる区別をする必要がない(dp[i]を考える時、i番目の要素がまだ使われていないことを保証する必要がない)
int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];

    vector<int> dp(W + 1, 0);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] < 0) continue;
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    cout << dp[W] << endl;
}
