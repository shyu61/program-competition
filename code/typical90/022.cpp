#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    vector<ll> a(3);
    rep(i, 3) cin >> a[i];
    ll x = gcd(gcd(a[0], a[1]), a[2]);

    ll ans = 0;
    rep(i, 3) ans += a[i] / x - 1;
    cout << ans << endl;
}
