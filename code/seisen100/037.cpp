#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 5e4 + 1;

int main() {
    int n, m; cin >> n >> m;
    vector<int> c(m);
    rep(i, m) cin >> c[i];

    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    rep(i, m) {
        vector<int> old(n + 1, INF);
        swap(dp, old);
        rep(j, n + 1) {
            dp[j] = min(dp[j], old[j]);
            if (j + c[i] <= n) {
                dp[j + c[i]] = min(dp[j + c[i]], dp[j] + 1);
            }
        }
    }
    cout << dp[n] << endl;
}
