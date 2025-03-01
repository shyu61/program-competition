#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 3つあるものは真ん中を固定(全探索)することを考える

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n), c(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];
    rep(i, n) cin >> c[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    ll ans = 0;
    rep(i, n) {
        int ai = lower_bound(a.begin(), a.end(), b[i]) - a.begin() - 1;
        if (ai < 0) continue;

        int ci = upper_bound(c.begin(), c.end(), b[i]) - c.begin();
        if (ci >= n) break;

        ans += ll(ai + 1) * (n - ci);
    }

    cout << ans << endl;
}
