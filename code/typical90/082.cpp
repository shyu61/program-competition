#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

int main() {
    ll l, r; cin >> l >> r;

    auto f = [&](ll x) -> mint {
        if (x == 0) return 0;
        int d = to_string(x).size();
        mint res = 0;
        ll a = 1;
        for (int i = 1; i <= d; i++) {
            ll b = i == d ? x : a * 10 - 1;
            res += mint(a + b) / 2 * (b - a + 1) * i;
            a *= 10;
        }
        return res;
    };

    cout << (f(r) - f(l - 1)).val() << endl;
}
