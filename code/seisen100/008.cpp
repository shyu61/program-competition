#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 絶対値(距離)の総和を最小にするのはその集合の中央値であることを利用する解法
int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int meda = a[n/2], medb = b[n/2];
    ll ans = 0;
    rep(i, n) {
        ans += abs(meda - a[i]) + (b[i] - a[i]) + abs(b[i] - medb);
    }
    cout << ans << endl;
}

// 全探索解法
int main() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];

    ll ans = numeric_limits<ll>::max();
    rep(i, n) rep(j, n) {
        int s = a[i], t = b[j];
        ll res = 0;
        rep(k, n) {
            res += abs(s - a[k]) + (b[k] - a[k]) + abs(b[k] - t);
        }
        ans = min(ans, res);
    }
    cout << ans << endl;
}
