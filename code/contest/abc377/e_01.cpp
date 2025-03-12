#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

ll pow(ll x, ll n, ll mod = 1) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n; ll k; cin >> n >> k;
    vector<int> p(n);
    rep(i, n) cin >> p[i], p[i]--;

    vector<int> ans(n, -1);
    rep(i, n) {
        if (ans[i] != -1) continue;

        vector<int> cyc;
        int cur = i;
        do {
            cyc.push_back(cur);
            cur = p[cur];
        } while (cur != i);

        int r = cyc.size();
        int step = pow(2, k, r);
        rep(j, r) {
            ans[cyc[j]] = cyc[(j + step) % r];
        }
    }

    rep(i, n) cout << ans[i] + 1 << ' ';
    cout << endl;
}
