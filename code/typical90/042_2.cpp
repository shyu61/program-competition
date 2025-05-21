#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/abc007/tasks/abc007_4
// https://torus711.hatenablog.com/entry/20150423/1429794075

// 🔷初見でどうやったら解けるか
// 桁問題なので桁dpを考える。制約条件は大小制約なので、未満フラグを導入する。(ここまではセオリー通り)
// 加えて、問題固有の条件は「4,9を含むかどうか」なのでこのフラグも加えたdpを計算すれば良い。

// 🔷抑えるべき抽象論は？
// 桁問題はまず制約を確認する。大小制約なのか桁和制約なのか。
// - 大小制約: 未満フラグで表現できる(状態数が小さい)
//   - 1: [0,9]を走査
//   - 0: [0,digit[i]]を走査, digit[i]を取る時だけ遷移先の未満フラグ0を維持する
// - 桁和制約: 添字に桁和を持つ必要がある
// 上記に加えて解を求めるための条件を添字に加える

int main() {
    ll a, b; cin >> a >> b;

    auto f = [&](ll a) -> ll {
        string s = to_string(a);
        int n = s.size();

        vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(2, vector<ll>(2)));
        dp[0][0][0] = 1;
        rep(i, n) {
            int D = s[i] - '0';
            rep(j, 2) {
                rep(k, 2) {
                    for (int d = 0; d <= (j ? 9 : D); d++) {
                        dp[i + 1][j || (d < D)][k || d == 4 || d == 9] += dp[i][j][k];
                    }
                }
            }
        }
        return dp[n][0][1] + dp[n][1][1];
    };

    cout << f(b) - f(a - 1) << endl;
}
