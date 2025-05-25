#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint1000000007;

// https://torus711.hatenablog.com/entry/20150423/1429794075

int main() {
    int k; cin >> k;
    if (k % 9 != 0) {
        cout << 0 << endl;
        return 0;
    }

    // dp[i] = 桁和がiの時、の通り数
    vector<mint> dp(k + 1);
    dp[0] = 1;
    rep(i, k + 1) {
        for (int j = 1; j <= 9; j++) {
            if (i - j >= 0) dp[i] += dp[i - j];
        }
    }

    cout << dp[k].val() << endl;
}
