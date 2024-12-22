// 探索のメモ化と動的計画法(最長共通部分問題): p56
#include <bits/stdc++.h>
using namespace std;

// LCSはDPを使って解く文字列の問題の典型
// 文字列は"列"なので逐次的に見ていく処理を行う問題が多い
// LCSは2文字列の比較なのでどちらの文字を遷移させるかによって3通りの遷移があることが分かる。

int main() {
    int N; cin >> N;
    for (int q = 0; q < N; q++) {
        string s, t; cin >> s >> t;

        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        s = ' ' + s;
        t = ' ' + t;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i + 1] == t[j + 1]) dp[i + 1][j + 1] = dp[i][j] + 1;
                else dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }

        cout << dp[n][m] << endl;
    }
}
