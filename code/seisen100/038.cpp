#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int q; cin >> q;
    while (q--) {
        string s, t; cin >> s >> t;
        int n = s.size(), m = t.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        rep(i, n) rep(j, m) {
            if (s[i] == t[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
        cout << dp[n][m] << '\n';
    }
}
