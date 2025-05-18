#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// LCS: longest Common Subsequence

// 🔷抑えるべき抽象論は？
// 動くものが複数ある場合は、まず遷移のパターンを列挙する
// dpの復元の一般化
// - dpテーブルを逆順に辿り、遷移条件を元に遷移元を特定しつつ復元する

int main() {
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();

    // dp[i][j]:=sをi番目まで見て、tをj番目まで見た時のLCS
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    rep(i, n) {
        rep(j, m) {
            if (s[i] == t[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
            else dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
        }
    }

    string ans = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        // (i-1,j) -> (i,j)
        if (dp[i][j] == dp[i - 1][j]) i--;
        // (i,j-1) -> (i,j)
        else if (dp[i][j] == dp[i][j - 1]) j--;
        // (i-1,j-1) -> (i,j)
        // 注意点は、dp[i][j]==dp[i-1][j-1]だからと言ってs[i-1]==t[j-1]とは限らない
        else {
            ans += s[i - 1];
            i--, j--;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
