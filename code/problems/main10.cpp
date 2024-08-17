// E - Random Swaps of Balls
// https://atcoder.jp/contests/abc360/tasks/abc360_e
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n, k;
    std::cin >> n >> k;

    mint x = mint(n) * mint(n);

    vector<mint> dp(k + 1);
    dp[0] = 1;
    for (int i = 1; i <= k; i++) {
        mint not_move = (1 + mint(n - 1) * mint(n - 1)) / x;
        mint move_to1 = 2 / x;
        dp[i] = dp[i - 1] * not_move + (1 - dp[i - 1]) * move_to1;
    }

    mint ans = dp[k] + (1 - dp[k]) * mint(2 + n) / 2;
    cout << ans.val() << endl;
}
