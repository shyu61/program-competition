#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

void chmin(int& a, int b) { a = min(a, b); }

// 想定解
// LCS + 貪欲

// 罠
// 操作は3種類あるが選択すべき操作は貪欲に決定できる点
// LCSが普通に求めたらTLEする点

bool solve_slow() {
    int k; string s, t; cin >> k >> s >> t;
    int n = s.size(), m = t.size();

    if (s == t) return true;
    if (abs(n - m) > k) return false;
    if (n < m) {
        swap(s, t);
        swap(n, m);
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
    dp[0][0] = 0;
    rep(i, n) {
        rep(j, m) {
            int c = s[i] == t[j] ? 0 : 1;
            chmin(dp[i + 1][j + 1], dp[i][j] + c);  // replace
            chmin(dp[i + 1][j], dp[i][j] + 1);  // delete
            chmin(dp[i][j + 1], dp[i][j] + 1);  // insert
        }
    }
    return dp[n][m] <= k;
}

bool solve_fast() {
    int k; string s, t; cin >> k >> s >> t;
    int n = s.size(), m = t.size();

    if (s == t) return true;
    if (abs(n - m) > k) return false;
    if (n < m) {
        swap(s, t);
        swap(n, m);
    }

    int w = k * 2;
    vector<vector<int>> dp(n + 1, vector<int>(w + 1, INF));
    dp[0][k] = 0;
    rep(i, n + 1) {
        rep(d, w + 1) {
            int j = i + d - k;
            if (j < 0) continue;
            if (j > m) break;

            if (i < n && j < m) {
                int c = s[i] == t[j] ? 0 : 1;
                chmin(dp[i + 1][d], dp[i][d] + c);  // replace
            }
            if (i < n && d > 0) chmin(dp[i + 1][d - 1], dp[i][d] + 1);  // delete
            if (d < w) chmin(dp[i][d + 1], dp[i][d] + 1);  // insert
        }
    }

    return dp[n][k + m - n] <= k;
}

int main() {
    if (solve_fast()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
