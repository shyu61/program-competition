#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/abc195/tasks/abc195_c

int main() {
    ll n; cin >> n;
    ll ans = 0, x = 1000;
    rep(i, 5) {
        if (n < x) break;
        ans += n - x + 1;
        x *= 1000;
    }
    cout << ans << endl;
}
