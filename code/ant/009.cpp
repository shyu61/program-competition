// 最長共通部分列問題(LCS): p56
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    char s[n], t[m];
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= m; i++) cin >> t[i];

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    cout << dp[n][m] << endl;
}
