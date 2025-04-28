#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

// 🔷抑えるべき抽象論は？
// 組合せ論はdpと非常に相性が良い。数え上げや組合せ数が絡む問題はdpも検討する
//   - 方向性を定義でき、影響が累積的であるため
// 組合せを考える時、1要素で複数個の幅を持つ場合は縮約して考えれば良い

int main() {
    int n, l; cin >> n >> l;

    vector<mint> dp(n + 1);
    dp[0] = 1;
    rep(i, n) {
        dp[i + 1] = dp[i];
        if (i - l + 1 >= 0) dp[i + 1] += dp[i - l + 1];
    }

    cout << dp[n].val() << endl;
}

// 別解
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

mint comb(int n, int k) {
    if (n < k || k < 0) return 0;
    return facts(n) * ifacts(k) * ifacts(n - k);
}

int main() {
    int n, l; cin >> n >> l;

    int r = n / l;
    mint ans = 0;
    rep(i, r + 1) {
        int x = i * l;
        ans += comb(n - x + i, i);
    }
    cout << ans.val() << endl;
}
