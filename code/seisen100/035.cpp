#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n);
    rep(i, n) cin >> v[i] >> w[i];

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
