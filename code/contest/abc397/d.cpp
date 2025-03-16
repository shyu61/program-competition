#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 数学的問題を扱えるか, 方程式を競プロ的に解けるか

// ポイント
// 平方数判定の方法
// → sqrtをとった後の数を2乗して確かめる
// 方程式の競プロ的な考え方
// - 競プロは基本は整数なので、範囲制約をうまく使って探索することを考える
// - 鍵は探索対象, 本問題のようにxを直接探索するのではなく置き替え後の変数を探索するなど
// 二次方程式の解き方
// - 基本は解の公式を使うで良い
// - 二次方程式に限らず、探索区間において関数が単調なら二分探索で求められる

int main() {
    ll n; cin >> n;

    for (ll t = 1; t * t * t <= n; t++) {
        ll c = t * t * t - n;
        if (c % (3 * t) != 0) continue;
        c /= 3 * t;

        ll d = t * t - 4 * c;
        ll rd = sqrt(d);
        if (rd * rd != d) continue;

        ll x = (t + rd) / 2, y = x - t;
        if (y > 0) {
            cout << x << ' ' << x - t << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}

ll qd(ll a, ll b, ll c) {
    auto check = [&](ll mid) -> bool {
        return a * mid * mid + b * mid + c <= 0;
    };

    int ok = 0, ng = 1e9;
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }

    if (a * ok * ok + b * ok + c == 0) return ok;
    return -1;
}

int main() {
    ll n; cin >> n;

    for (ll i = 1; i * i * i <= n; i++) {
        if (n % i != 0) continue;
        ll m = n / i;
        ll res = qd(3, 3 * i, i * i - m);
        if (res > 0) {
            cout << res + i << ' ' << res << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
