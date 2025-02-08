#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// subseq問題

// 方針
// 位置配列では解けなさそう、かつ自分より前に"atcoder"文字列のどの部分までがいくつあるかを知っている必要があるので累積構造
// 故にdpを考える。i文字目までみた時に、"atcoder"文字列の各番目までいくつ選択肢があるかを求める。
// 遷移はs[i]の一つ手前の"atcoder"文字までの選択肢を足す

const int MOD = 1000000007;
int main() {
    int n; string s; cin >> n >> s;
    string t = "atcoder";
    int m = t.size();

    vector<int> dp(m);
    rep(i, n) {
        rep(j, m) {
            if (s[i] == t[j]) {
                if (j == 0) dp[j] += 1;
                else dp[j] += dp[j - 1];
                dp[j] %= MOD;
            }
        }
    }
    cout << dp[m - 1] % MOD << endl;
}
