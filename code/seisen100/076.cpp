#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    for (int k = 1; k <= n; k++) {
        ll mx = 0;
        rep(i, n - k + 1) {
            mx = max(mx, s[i + k] - s[i]);
        }
        cout << mx << '\n';
    }
}
