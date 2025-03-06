// 編集距離
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E&lang=ja
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

void chmin(int& a, int b) { a = min(a, b); }

int main() {
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();

    if (s == t) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
    dp[0][0] = 0;
    rep(i, n + 1) rep(j, m + 1) {
        if (i < n && j < m) {
            int c = s[i] == t[j] ? 0 : 1;
            chmin(dp[i + 1][j + 1], dp[i][j] + c);  // replace
        }
        if (i < n) chmin(dp[i + 1][j], dp[i][j] + 1);  // delete
        if (j < m) chmin(dp[i][j + 1], dp[i][j] + 1);  // insert
    }
    cout << dp[n][m] << endl;
}
