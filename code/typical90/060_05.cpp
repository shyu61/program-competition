#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/arc070/tasks/arc070_b

// 🔷初見でどうやったら解けるか
// 数え上げの問題。数え上げはある条件を満たすものを数える訳だが、この条件を定式化したり数学的な表現に直したりすることが重要。
// 本問題においては、a[i]が不必要とは、「a[i]を含む良い集合の各合計値sumが、k<=sum<k+a[i] となる集合が存在すること」と同値である。
// 全探索はできないが、k<=5000であり、取りうる値が累積的に決まるのでdpすれば良いことは容易に想像がつく。この時点でO(n^2k)
// あとはどう高速化するか。a[i]を常に使う（あるいは常に使わない）という点以外はn回ループで差異はないので、dpを事前計算しておき、a[i]のみを使わない場合を高速に求める方法を考える。
// これは両側dpすることで達成できる。

// 🔷抑えるべき抽象論は？
// dpである特定のiだけ操作を固定した値を取得したい時は、両側dpすれば良い
// 数え上げはある条件を満たすものを数える訳だが、この条件を定式化したり数学的な表現に直したりすることが重要

// O(nk)
int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    const int k2 = k * 2;
    vector<vector<bool>> dp(n + 1, vector<bool>(k2)), bk(n + 1, vector<bool>(k2));
    dp[0][0] = true;
    bk[n][0] = true;
    rep(i, n) rep(j, k2) {
        if (j - a[i] >= 0) dp[i + 1][j] = dp[i][j - a[i]];
        dp[i + 1][j] = dp[i + 1][j] || dp[i][j];
    }
    for (int i = n - 1; i >= 0; i--) {
        rep(j, k2) {
            if (j - a[i] >= 0) bk[i][j] = bk[i + 1][j - a[i]];
            bk[i][j] = bk[i][j] || bk[i + 1][j];
        }
    }

    int ans = 0;
    rep(i, n) {
        if (a[i] >= k) {
            ans++;
            continue;
        }
        vector<int> L;
        rep(j, k2) {
            if (dp[i][j]) L.push_back(j);
        }
        int m = L.size(), pos = 0;
        for (int j = k2 - 1; j >= 0; j--) {
            if (bk[i + 1][j]) {
                while (pos < m && L[pos] + j < k - a[i]) pos++;
                if (pos >= m) break;
                if (L[pos] + j < k) {
                    ans++;
                    break;
                }
            }
        }
    }
    cout << n - ans << endl;
}

const int M = 5001;

// O(n^2k)を頑張って高速化してacした解法
int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int mx = 0;
    vector<bitset<M>> dp(k * 2);
    dp[0].set(0);
    rep(i, n) {
        const int& ai = a[i];

        if (ai >= k * 2) continue;
        int nmx = min(k * 2 - 1, mx + ai);

        for (int j = nmx; j >= ai; j--) {
            if (j - ai >= 0 && dp[j - ai].any()) {
                dp[j] |= dp[j - ai];
                dp[j].set(i + 1);
            }
        }
        mx = nmx;
    }

    int ans = 0;
    rep(i, n) {
        if (a[i] >= k) continue;
        bool need = false;
        rep(j, a[i]) {
            if (dp[k + j].test(i + 1)) {
                need = true;
                break;
            }
        }
        if (!need) ans++;
    }
    cout << ans << endl;
}
