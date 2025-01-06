#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// - 数論, 区間数え上げ, 桁問題

// 方針
// 桁問題は、(1)桁dpで解くか(2)n-1桁までの個数+n桁で何番目かに分解して法則性から立式するかの2択
// 各桁が(ほぼ)独立に扱える場合は(2)、桁同士の依存性が強く法則性を見抜くのが難しい場合は(1)で解く

ll f(ll a) {
    string s = to_string(a);
    int n = s.size();

    // dp[決定した桁数][元の数未満か][すでに4,9を含んでいるか] := 場合の数
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(2, vector<ll>(2)));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        int D = s[i] - '0';

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int d = 0; d <= (j ? 9 : D); d++) {
                    dp[i + 1][j || (d < D)][k || d == 4 || d == 9] += dp[i][j][k];
                }
            }
        }
    }

    return dp[n][0][1] + dp[n][1][1];
}

int main() {
    ll a, b; cin >> a >> b;
    cout << f(b) - f(a - 1) << endl;
}
