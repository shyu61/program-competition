// 漸化式を工夫する(個数制限なしナップサック問題): p58
#include <bits/stdc++.h>
using namespace std;

// 復元抽出型のナップサック問題は、自己遷移を書く
// dp[i+1]への遷移ではdp[i+1]からの自己遷移を書くと、既にi番目を使っている状況から最後にiを使う遷移を表現できる => つまり復元抽出

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    int W; cin >> W;

    vector<vector<int>> dp(n + 1, vector<int>(W + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] < 0) {
                dp[i + 1][j] = dp[i][j];
            } else {
                // max(既にiを使っている状態から最後にiを使う場合, iを使わない場合)
                dp[i + 1][j] = max(dp[i + 1][j - w[i]] + v[i], dp[i][j]);
            }
        }
    }

    cout << dp[n][W] << endl;
}

// swapを使う方法
int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    int W; cin >> W;

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        vector<int> old(W + 1);
        swap(old, dp);
        for (int j = 0; j <= W; j++) {
            if (j - w[i] < 0) {
                dp[j] = old[j];
            } else {
                dp[j] = max(dp[j - w[i]] + v[i], old[j]);
            }
        }
    }

    cout << dp[W] << endl;
}

// 完全に配列を再利用する方法
int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    int W; cin >> W;

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        for (int j = W; j >= w[i]; j--) {
            // 2項間かつ自身より大きい or 小さい添字にしか依存しない場合で使える
            dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
        }
    }

    cout << dp[W] << endl;
}
