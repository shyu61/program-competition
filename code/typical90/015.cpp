#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

// ジャンル
// 数論, 組合せ論, 数え上げ

// ポイント
// 組合せ論の問題を考える上でのポイント
// - まず制約なしの基礎となるパターンを考える
// - 制約の意味を抽象化し意味を変換する
//   - 間隔や差などは、「配置」や「順序」に変換できないか考える
//   - 空白を挿入するといった考え方は典型
// - 制約下での自由度を考える
// - 制約を直接数えのが難しい場合は補集合を考える

struct ModInv {
    int n; vector<mint> d;
    ModInv() : n(2), d({0, 1}) {}
    mint operator()(int i) {
        while (n <= i) {
            d.push_back(-d[mint::mod() % n] * (mint::mod() / n)), ++n;
        }
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} invs;

struct ModFact {
    int n; vector<mint> d;
    ModFact() : n(2), d({1, 1}) {}
    mint operator()(int i) {
        while (n <= i) d.push_back(d.back() * n), ++n;
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} facts;

struct ModFactInv {
    int n; vector<mint> d;
    ModFactInv() : n(2), d({1, 1}) {}
    mint operator()(int i) {
        while (n <= i) d.push_back(d.back() * invs(n)), ++n;
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} ifacts;

mint comb(ll n, int k) {
    if (n < k || k < 0) return 0;
    return facts(n) * ifacts(k) * ifacts(n - k);
}

int main() {
    int n; cin >> n;
    for (int k = 1; k <= n; k++) {
        mint ans = 0;
        // 切り上げ除算
        for (int a = 1; a <= (n + k - 1) / k; a++) {
            // 差をk以上にするには選択するボール間に少なくともk-1個の選択しないボールを挿入する必要がある
            // ボールをa個選択する時、ボール間は(a-1)箇所あるので(a-1)(k-1)個は選べない。
            // 故にn-(a-1)(k-1)個のボールからa個を選べば良いので、(n-(a-1)(k-1))Ca を計算すれば良い
            // 選べる最大個数は⌊n/k⌋になる
            ans += comb(n - ll(k - 1) * (a - 1), a);
        }
        cout << ans.val() << '\n';
    }
}
