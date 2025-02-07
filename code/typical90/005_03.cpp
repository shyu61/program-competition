#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ダブリングによる解法: O(B^2logN)
const int LOG = 62, MOD = 1000000007;
int main() {
    ll n; int b, K; cin >> n >> b >> K;
    vector<int> c(K);
    rep(i, K) cin >> c[i];

    vector<ll> ten(LOG, 10);
    for (int i = 1; i < LOG; i++) {
        ten[i] = (ten[i - 1] * ten[i - 1]) % b;
    }

    vector<vector<ll>> dp(LOG + 1, vector<ll>(b));
    rep(i, K) dp[0][c[i] % b] += 1;
    rep(i, LOG) {
        rep(j, b) {
            rep(k, b) {
                int nx = (j * ten[i] + k) % b;
                dp[i + 1][nx] += dp[i][j] * dp[i][k];
                dp[i + 1][nx] %= MOD;
            }
        }
    }

    vector<vector<ll>> dp2(LOG + 1, vector<ll>(b));
    dp2[0][0] = 1;
    rep(i, LOG) {
        if (n >> i & 1) {
            rep(j, b) {
                rep(k, b) {
                    int nx = (j * ten[i] + k) % b;
                    dp2[i + 1][nx] += dp2[i][j] * dp[i][k];
                    dp2[i + 1][nx] %= MOD;
                }
            }
        } else {
            rep(j, b) dp2[i + 1][j] = dp2[i][j];
        }
    }

    cout << dp2[LOG][0] << endl;
}
