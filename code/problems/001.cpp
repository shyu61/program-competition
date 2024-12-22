// E - Maximum Glutton
// https://atcoder.jp/contests/abc364/tasks/abc364_e
#include<bits/stdc++.h>
using namespace std;

const int N = 80;
const int M = 1e4;
int n, A, B;
int dp[N + 1][N + 1][M + 1], a[N + 1], b[N + 1];

void solve() {
    int maxv = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= A; k++) {
                if (k - a[i] >= 0) {
                    dp[i][j][k] = min(dp[i - 1][j - 1][k - a[i]] + b[i], dp[i - 1][j][k]);
                } else {
                    dp[i][j][k] = dp[i - 1][j][k];
                }

                if (dp[i][j][k] <= B) maxv = max(maxv, j);
            }
        }
    }
    cout << min(maxv + 1, n) << endl;
}

int main() {
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; i++) dp[i][0][0] = 0;

    solve();
}
