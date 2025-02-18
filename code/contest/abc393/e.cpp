#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 数論, gcd, 倍数, 組合せ最適化

// 方針
// 直接k個のgcdの最大値を求めるのは難しそう。逆から考える、つまりある数gの倍数が解になるか判定していくことを考える
// 取りうる全範囲に対して、倍数の個数を数えておき、個数がk個以上ある数gについて、gの倍数にとってgはgcdの最大値の候補の一つとなることを利用する
// なお倍数の線形スキャンは調和級数時間になることが知られていて、10^6程度なら十分間に合う

// ポイント
// - ある数nの約数dについて、dの倍数にnは必ず含まれる
//   - ある集合Aの全要素のgcdについて、gcdの倍数には集合Aの全要素が含まれる
// - 約数と倍数は対をなす概念
//   - gcdなど約数を求めるとき、直接求めるのが難しい場合は倍数を考えるのは良い考え
//     - 約数は連続じゃないので最適化を二分探索で解く方法は使えないが、倍数を考えるというアプローチはこれと似ている
//   - 倍数を考える時に約数を考えるのもまた良い考え
// - 公約数は各要素の素因数分解後の指数のminである
// - 倍数のフルスキャンは調和級数時間になりがち
// - 約数は多次元表として表現できる
//   - 素数ゼータ変換
//     - ある数の約数全体をスキャンして乗法的な値(総和や個数の総和など)を得たい時、高速に動作する
//     - 2べき,3べき,5べき...など素数ごとに次元を用意し計算することで、累積和処理で書く素数の指数を指定すれば、その位置までの約数をO(1)で全スキャンできる

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    const int M = 1e6;

    // 頻度配列
    vector<int> cnt(M + 1);
    rep(i, n) cnt[a[i]]++;

    // 倍数の個数配列
    vector<int> b(M + 1);
    for (int i = 1; i <= M; i++) {
        for (int j = i; j <= M; j += i) b[i] += cnt[j];
    }

    // b[i]>=k の時、iの全ての倍数にとって、約数であるiが解の候補になる
    vector<int> ans(M + 1);
    for (int i = 1; i <= M; i++) {
        if (b[i] < k) continue;
        for (int j = i; j <= M; j += i) ans[j] = i;
    }

    for (auto ai : a) cout << ans[ai] << '\n';
}

struct Sieve {
    int n;
    vector<int> is_pn, pn;
    Sieve(int n) : n(n), is_pn(n + 1, true) {
        is_pn[0] = is_pn[1] = false;
        for (int i = 2; i <= n; i++) {
            if (is_pn[i]) {
                pn.push_back(i);
                for (int j = i * 2; j <= n; j += i) {
                    is_pn[j] = false;
                }
            }
        }
    }
};

// 素数ゼータ変換による解法
int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // Mまでの素数を計算
    const int M = 1e6;
    Sieve sieve(M);

    // 頻度配列
    vector<int> cnt(M + 1);
    for (auto ai : a) cnt[ai]++;

    // 約数方向にゼータ変換
    for (auto p : sieve.pn) {
        for (int i = M / p; i >= 0; i--) {
            cnt[i] += cnt[i * p];  // 倍数の個数なので逆向きに累積和を取る
        }
    }

    vector<int> ans(M + 1);
    for (int i = 1; i <= M; i++) {
        if (cnt[i] >= k) ans[i] = i;
    }

    for (auto p : sieve.pn) {
        for (int i = 1; i <= M / p; i++) {
            ans[i * p] = max(ans[i * p], ans[i]);
        }
    }

    for (auto ai : a) cout << ans[ai] << '\n';
}
