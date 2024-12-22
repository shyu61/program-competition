// 漸化式を工夫する(個数制限付き部分和問題): p62
#include <bits/stdc++.h>
using namespace std;

// 個数制限なしナップサック問題と同じなのは復元抽出という点、違う点は個数制限がある点。
// 個数制限がないなら単純にkを省略して自己遷移を書けば良かったが、この方法では何個使ったかがわからないので今回は使えない => 個数をtrackする必要がある

// dpの値をboolにする場合は大概は非効率。もっと情報を持たせて効率化できる場合が多い
// boolの代わりに個数に関する情報を持たせよう => dp[i+1][j]: i番目までを使って整数jを作る時の、iの最大の残り個数
// 遷移はdp[i]からの遷移とdp[i+1]からの遷移を考えれば良い

// O(nKm) => max 1e2 * 1e5 * (1e5 * 1e2) = 1e14
int main() {
    int n; cin >> n;
    vector<int> a(n), m(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> m[i];
    int K; cin >> K;

    vector<vector<bool>> dp(n + 1, vector<bool>(K + 1));
    dp[0][0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            for (int k = 0; k < m[i]; k++) {
                if (dp[i + 1][j]) break;
                if (j - k * a[i] < 0) dp[i + 1][j] = dp[i][j];
                else dp[i + 1][j] = dp[i][j] | dp[i][j - k * a[i]];
            }
        }
    }

    if (dp[n][K]) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    int n; cin >> n;
    vector<int> a(n), m(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> m[i];
    int K; cin >> K;

    // dp[i+1][j]: i番目までで整数jを作る時、i番目のmax(残りの個数)
    vector<vector<int>> dp(n + 1, vector<int>(K + 1, -1));
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            // jを作れない場合
            if (j - a[i] < 0 || dp[i + 1][j - a[i]] <= 0) dp[i + 1][j] = -1;
            // jを作れる場合
            if (dp[i][j] >= 0) dp[i + 1][j] = m[i];
            else dp[i + 1][j] = dp[i + 1][j - a[i]] - 1;
        }
    }

    if (dp[n][K] >= 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}

// 配列再利用パターン
int main() {
    int n; cin >> n;
    vector<int> a(n), m(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> m[i];
    int K; cin >> K;

    // dp[i+1][j]: i番目までで整数jを作る時、i番目のmax(残りの個数)
    vector<int> dp(K + 1, -1);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            // 最初のdp[j]は更新前なのでold
            if (dp[j] >= 0) dp[j] = m[i];
            else if (j - a[i] < 0 || dp[j - a[i]] <= 0) dp[j] = -1;
            else dp[j] = dp[j - a[i]] - 1;
        }
    }

    if (dp[K] >= 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}
