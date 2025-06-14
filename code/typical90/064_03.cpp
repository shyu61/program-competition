#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 類問: https://atcoder.jp/contests/joi2017ho/tasks/joi2017ho_a

int main() {
    int n, q, s, t; cin >> n >> q >> s >> t;
    vector<ll> a(n + 1);
    rep(i, n + 1) cin >> a[i];

    vector<ll> b(n + 1);
    auto f = [&](int i) -> ll {
        return b[i] >= 0 ? -b[i] * s : -b[i] * t;
    };

    ll ans = 0;
    rep(i, n) {
        b[i] = a[i + 1] - a[i];
        ans += f(i);
    }

    while (q--) {
        int l, r, x; cin >> l >> r >> x;
        ll pre = 0, now = 0;
        if (l > 0) {
            pre += f(l - 1);
            b[l - 1] += x;
            now += f(l - 1);
        }
        if (r < n) {
            pre += f(r);
            b[r] -= x;
            now += f(r);
        }
        ans += now - pre;
        cout << ans << '\n';
    }
}
