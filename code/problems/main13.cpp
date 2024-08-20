#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using ll = long long;
using mint = atcoder::modint998244353;

struct modinv {
    int n;
    vector<mint> d;
    modinv() : n(2), d({0, 1}) {}
    mint operator()(int i) {
        while (n <= i)
            d.push_back(-d[mint::mod() % n] * (mint::mod() / n)), ++n;
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} invs;

struct modfact {
    int n;
    vector<mint> d;
    modfact() : n(2), d({1, 1}) {}
    mint operator()(int i) {
        while (n <= i) d.push_back(d.back() * n), ++n;
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} facts;

struct modfactinv {
    int n;
    vector<mint> d;
    modfactinv() : n(2), d({1, 1}) {}
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

// ========================
int main() {
    int n = 26;
    int k;
    cin >> k;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<mint> dp(k + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        vector<mint> old(k + 1);
        swap(old, dp);

        for (int j = 0; j <= k; j++) {
            for (int a = 0; a <= c[i]; a++) {
                int nj = j + a;
                // nj>jとなる場合、それ以上のjは全てnj>jとなるのでcontinueではなくbreakする
                if (nj > k) break;
                dp[nj] += old[j] * comb(nj, a);
            }
        }
    }

    mint ans = 0;
    for (int i = 0; i < k; i++) ans += dp[i + 1];
    cout << ans.val() << endl;
}
