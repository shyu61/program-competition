#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

void chmax(double& a, double b) { a = max(a, b); }

int main() {
    int n, t, m, k; cin >> n >> t >> m >> k;
    // dp[i][j] := iラウンド後にj回押してる状態からの勝率
    vector<vector<double>> dp(t + 1, vector<double>(k + 1));
    dp[t][k] = 1;
    for (int ti = t - 1; ti >= 0; ti--) {
        rep(ki, k + 1) {
            double res = 0;
            vector<vector<double>> dp2(m + 1, vector<double>(m + 1));
            rep(i, m) rep(j, m + 1) {
                for (int c = 1; j + c <= m; c++) {
                    chmax(dp2[i + 1][j + c], dp2[i][j] + dp[ti + 1][min(k, ki + c)]);
                }
            }
            rep(i, m + 1) {
                if (i > n) break;
                double x = dp2[i][m];
                x += dp[ti + 1][ki] * (n - i);
                chmax(res, x);
            }
            dp[ti][ki] = res / n;
        }
    }

    cout << fixed << setprecision(8) << dp[0][0] << endl;
}
