#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint998244353;

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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<vector<mint>> s(k + 1, vector<mint>(n + 1));
    rep(i, n) s[1][i + 1] = s[1][i] + a[i];
    for (int i = 1; i < k; i++) {
        rep(j, n + 1) s[i + 1][j] = s[i][j] * s[1][j];
    }

    vector<vector<mint>> s2(k + 1, vector<mint>(n + 1));
    for (int i = 1; i <= k; i++) {
        rep(j, n) {
            s2[i][j + 1] = s2[i][j] + s[i][j + 1];
        }
    }

    mint ans = 0;
    for (int i = 1; i <= n; i++) {
        if (k % 2 == 0) ans += n * s[k][i];
        else ans += (-n + i * 2) * s[k][i];
    }
    for (int i = 1; i <= n; i++) {
        mint res = 0;
        for (int j = 1; j < k; j++) {
            int sign = (j % 2 == 0) ? 1 : -1;
            res += sign * comb(k, j) * (s[j][i - 1] * (s2[k - j][n] - s2[k - j][i - 1]));
        }
        ans += res;
    }
    cout << ans.val() << endl;
}
