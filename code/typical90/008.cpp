#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// subseq問題

// 方針
// 位置配列では解けなさそう、かつ自分より前に"atcoder"文字列のどの部分までがいくつあるかを知っている必要があるので累積構造
// 故にdpを考える。i文字目までみた時に、"atcoder"文字列の各番目までいくつ選択肢があるかを求める。
// 遷移はs[i]の一つ手前の"atcoder"文字までの選択肢を足す

// ポイント
// subseq問題でdpを使う場合は、「何文字目まで作ったか」という状態を持つことが多い
//   - これはsubseq問題におけるまさに"部分問題"を表すため

const int MOD = 1000000007;
int main() {
    int n; string s; cin >> n >> s;
    string t = "atcoder";
    int m = t.size();

    vector<int> dp(m + 1);
    dp[0] = 1;
    rep(i, n) {
        vector<int> old(m + 1);
        swap(dp, old);
        rep(j, m + 1) {
            // s[i]を選ばない場合
            dp[j] = (dp[j] + old[j]) % MOD;
            if (j < m && s[i] == t[j]) {
                // s[i]を選ぶ場合
                dp[j + 1] = (dp[j + 1] + old[j]) % MOD;
            }
        }
    }

    cout << dp[m] % MOD << endl;
}

// mintを使う解法
#include <atcoder/modint>
using mint = atcoder::modint1000000007;
int main() {
    int n; string s; cin >> n >> s;
    string t = "atcoder";
    int m = t.size();

    vector<mint> dp(m + 1);
    dp[0] = 1;
    rep(i, n) {
        vector<mint> old(m + 1);
        swap(dp, old);
        rep(j, m + 1) {
            dp[j] += old[j];
            if (j < m && s[i] == t[j]) {
                dp[j + 1] += old[j];
            }
        }
    }

    cout << dp[m].val() << endl;
}
