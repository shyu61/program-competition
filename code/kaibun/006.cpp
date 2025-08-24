#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/abc196/tasks/abc196_c

int main() {
    ll n; cin >> n;
    for (int i = 1; i <= 1e6; i++) {
        ll x = stoll(to_string(i) + to_string(i));
        if (x > n) {
            cout << i - 1 << endl;
            return 0;
        }
    }
}

int main() {
    string s; cin >> s;
    int n = s.size();
    int m = n / 2;

    auto f = [&](int d) -> pair<ll, int> {
        ll res = 0;
        int base = 1;
        rep(i, d) {
            res += base * 9;
            base *= 10;
        }
        return make_pair(res, base);
    };

    if (n % 2 == 1) {
        cout << f(m).first << endl;
        return 0;
    }

    auto [ans, base] = f(m - 1);

    int c1 = stoi(s.substr(0, m));
    int c2 = stoi(s.substr(m));

    if (c1 <= c2) ans += c1 - base + 1;
    else ans += c1 - base;
    cout << ans << endl;
}
