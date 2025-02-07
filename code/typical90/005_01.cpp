#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int MOD = 1e9 + 7;

// ジャンル
// 桁問題, 倍数判定, 数え上げ, 数論, 桁dp

// 方針
// 値を生成できないので、各桁ごとに見ていくことを考える。
// 倍数判定なので、桁和か剰余を検討する。桁和は非常に限定的な数値の倍数判定にしか使えないので、剰余を扱う桁dpを行う
// 各桁ごとにK種類を全探索し剰余を計算する。桁が上がるたびに剰余は繰越しを行う。(これができるのはmodが割り算以外は線形性が成立するため)

// ポイント
// - Bの倍数 => mod_Bが0
// - 桁dpは剰余と相性が良い(余りを持って桁dp)

// O(nbK)
int main() {
    ll n; int b, K; cin >> n >> b >> K;
    vector<int> c(K);
    rep(i, K) cin >> c[i];

    // dp[上からi桁まで見た時][現時点でのmod_B] := 通り数
    vector<vector<int>> dp(n + 1, vector<int>(b));
    dp[0][0] = 1;
    rep(i, n) {
        rep(j, b) {
            rep(k, K) {
                int nx = (10 * j + c[k]) % b;
                dp[i + 1][nx] += dp[i][j];
                dp[i + 1][nx] %= MOD;
            }
        }
    }
    cout << dp[n][0] << endl;
}
