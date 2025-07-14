#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

// 🔷抑えるべき抽象論は？
// 桁が絡む問題は、桁ごとに別々に考えていけば良いケースが多い
// - 順に桁をなめながら、乗算などしつつ値を使い回せば効率的になるケースも多い
// - [l,r]がある問題で、残りを例外的に扱うのではなく、常に[s,t]が同一桁になるよう関数に渡す方法もある

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

int main() {
    ll l, r; cin >> l >> r;

    auto f = [&](ll s, ll t, int d) -> mint {
        return mint(s + t) / 2 * (t - s + 1) * d;
    };

    mint ans = 0;
    ll s = 1;
    for (int d = 1; d <= 19; d++) {
        ull t = s * 10 - 1;
        if (l <= t) {
            ans += f(max(s, l), min(t, ull(r)), d);
            if (r <= t) break;
        }
        s *= 10;
    }
    cout << ans.val() << endl;
}
