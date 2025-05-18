#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n), v(n);
    rep(i, n) cin >> v[i] >> w[i];

    vector<vector<int>> dp(n + 1, vector<int>(W + 1));
    rep(i, n) {
        rep(j, W + 1) {
            if (j - w[i] >= 0) dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
            else dp[i + 1][j] = dp[i][j];
        }
    }

    cout << "ans=" << dp[n][W] << endl;

    // 復元
    vector<int> ans;
    int i = n, j = W;
    while (i > 0 && j >= 0) {
        if (dp[i][j] == dp[i - 1][j]) i--;
        else {
            i--, j -= w[i];
            ans.push_back(i);
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << "i=" << i << ", v=" << v[i] << endl;
    }
}

