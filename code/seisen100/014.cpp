#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using uint = unsigned int;

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int n2 = 1 << n;
    ll ans = numeric_limits<ll>::max();
    rep(s, n2) {
        if (popcount(uint(s)) < k) continue;
        int mh = -1; ll res = 0;
        rep(i, n) {
            int h = a[i];
            if (s >> i & 1) {
                if (h <= mh) {
                    res += mh - h + 1;
                    h = mh + 1;
                }
            }
            mh = max(mh, h);
        }
        ans = min(ans, res);
    }
    cout << ans << endl;
}
