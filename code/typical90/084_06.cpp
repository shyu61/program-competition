#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/abc182/tasks/abc182_d

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    vector<ll> mx(n + 1);
    {
        ll now = 0;
        rep(i, n + 1) {
            now = max(now, s[i]);
            mx[i] = now;
        }
    }

    ll ans = 0, now = 0;
    rep(i, n + 1) {
        ans = max(ans, now + mx[i]);
        now += s[i];
    }
    cout << ans << endl;
}
