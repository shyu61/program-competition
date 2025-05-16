#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷抑えるべき抽象論は？
// 添え字とvalを入れ替えるのは、dpの典型的な高速化手法の一つ

const int VMAX = 1e5;
const ll INF = 1e12;

int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n), v(n);
    rep(i, n) cin >> w[i] >> v[i];

    // dp[i][j]:=i個目まで見て、価値をjとする時の最小重量
    vector<ll> dp(VMAX + 1, INF);
    dp[0] = 0;
    rep(i, n) {
        vector<ll> old(VMAX + 1, INF);
        swap(dp, old);
        rep(j, VMAX + 1) {
            if (j - v[i] >= 0) dp[j] = min(old[j], old[j - v[i]] + w[i]);
            else dp[j] = old[j];
        }
    }

    int ans = 0;
    rep(i, VMAX + 1) {
        if (dp[i] <= W) ans = max(ans, i);
    }
    cout << ans << endl;
}
