#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    rep(i, n) rep(j, m) cin >> a[i][j];

    ll ans = 0;
    rep(i, m) rep(j, i) {
        ll sum = 0;
        rep(k, n) {
            ll res = max(a[k][i], a[k][j]);
            sum += res;
        }
        ans = max(ans, sum);
    }
    cout << ans << endl;
}
