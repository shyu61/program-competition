#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// dp復元は逆順に辿れば良い

int main() {
    int n, s; cin >> n >> s;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];

    // dp[i日目まで見る][j円買う]:=可否
    vector<vector<bool>> dp(n + 1, vector<bool>(s + 1));
    dp[0][0] = true;
    rep(i, n) rep(j, s + 1) {
        if (j - a[i] >= 0) dp[i + 1][j] = dp[i][j - a[i]];
        if (j - b[i] >= 0) dp[i + 1][j] = dp[i + 1][j] || dp[i][j - b[i]];
    }

    if (!dp[n][s]) {
        cout << "Impossible" << endl;
        return 0;
    }

    // 復元
    string ans = "";
    int j = s;
    for (int i = n - 1; i >= 0; i--) {
        if (j - a[i] >= 0 && dp[i][j - a[i]]) {
            ans += 'A';
            j -= a[i];
        } else {
            ans += 'B';
            j -= b[i];
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
