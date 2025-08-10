#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    sort(a.begin(), a.end());

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    while (q--) {
        int b; cin >> b;
        if (b > a.back()) {
            cout << -1 << endl;
            continue;
        }
        int i = lower_bound(a.begin(), a.end(), b) - a.begin();
        ll ans = s[i] + ll(b - 1) * (n - i) + 1;
        cout << ans << "\n";
    }
}
