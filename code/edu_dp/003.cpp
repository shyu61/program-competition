#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題だが、局所最適性がないので貪欲では解けそうにない
// 明らかに影響が累積的で方向があるのでdpが有力候補になる。
// まずは基本通りに設計し、遷移する上で必要な情報を添え字に加えるという方針で考えると解ける

// 🔷抑えるべき抽象論は？
// dpは、まず基本通り考える → 遷移を記述する上で必要な情報は何かを追加で考える → 高速化

int main() {
    int n; cin >> n;
    vector<vector<int>> a(3, vector<int>(n));
    rep(i, n) rep(j, 3) cin >> a[j][i];

    // dp[i][j] := i日目までで、前日にjを選んだ時の最大幸福度
    vector<int> dp(3);
    rep(i, n) {
        vector<int> old(3);
        swap(dp, old);
        rep(j, 3) rep(k, 3) {
            if (k == j) continue;
            dp[j] = max(dp[j], old[k] + a[i][j]);
        }
    }

    int ans = 0;
    rep(i, 3) ans = max(ans, dp[i]);
    cout << ans << endl;
}
