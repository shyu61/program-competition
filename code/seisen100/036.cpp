#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 重複選択が可能な場合は自己遷移を書く
// -> 既に要素iをいくつか選択した状態からの遷移なので重複が許可される

int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n);
    rep(i, n) cin >> v[i] >> w[i];

    vector<int> dp(W + 1);
    rep(i, n) {
        vector<int> old(W + 1);
        swap(dp, old);
        rep(j, W + 1) {
            dp[j] = old[j];
            if (j - w[i] >= 0) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }
    cout << dp[W] << endl;
}
