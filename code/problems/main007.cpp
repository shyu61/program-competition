// E - Count Arithmetic Subsequences
// https://atcoder.jp/contests/abc362/tasks/abc362_e
#include <bits/stdc++.h>
using namespace std;

const int N = 998244353;

int n, a[81], dp[81][81][81];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) dp[i][j][2] += 1;
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < n; k++) {
                int now = dp[i][j][k];
                if (now == 0) continue;
                // iより向こう側を全探索
                for (int x = i + 1; x < n; x++) {
                    if (a[x] - a[i] == a[i] - a[j]) {
                        dp[x][i][k + 1] += now;
                        dp[x][i][k + 1] %= N;
                    }
                }
            }
        }
    }

    cout << n << " ";
    long long ans;
    for (int k = 2; k <= n; k++) {
        ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                ans += dp[i][j][k];
                ans %= N;
            }
        }
        cout << ans % N << " ";
    }
    cout << endl;
}
