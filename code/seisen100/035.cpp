#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n);
    rep(i, n) cin >> v[i] >> w[i];

    // dp[i番目まで見た時][重さw] := 最大価値
    // i: 漸化式部分
    // w: 決定変数
    // 最大価値: 目的変数
    vector<int> dp(W + 1);
    rep(i, n) {
        vector<int> old(W + 1);
        swap(dp, old);
        rep(j, W + 1) {
            if (j - w[i] >= 0) dp[j] = max(old[j], old[j - w[i]] + v[i]);
            else dp[j] = old[j];
        }
    }
    cout << dp[W] << endl;
}
