#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

mint mpow(mint x, ll n) {
    mint res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n), c(q);
    rep(i, n) cin >> a[i];
    rep(i, q) cin >> c[i], c[i]--;
    c.push_back(0);

    vector<mint> dist(n + 1);
    rep(i, n - 1) dist[i + 1] = mpow(mint(a[i]), a[i + 1]);
    rep(i, n) dist[i + 1] += dist[i];

    int s = 0;
    mint ans = 0;
    rep(i, q + 1) {
        int t = c[i];
        if (s > t) swap(s, t);
        ans += dist[t] - dist[s];
        s = c[i];
    }
    cout << ans.val() << endl;
}
